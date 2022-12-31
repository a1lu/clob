#include "clob/clob.h"
#include "brz.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define cat_one()                                 \
	do {                                      \
		if (atoms > 1) {                  \
			--atoms;                  \
			glob *b = *--frag;        \
			glob *a = *--frag;        \
			*frag++ = glob_seq(a, b); \
			free_glob(a);             \
			free_glob(b);             \
		}                                 \
	} while (0)

#define cat_all()                                 \
	do {                                      \
		while (--atoms > 0) {             \
			glob *b = *--frag;        \
			glob *a = *--frag;        \
			*frag++ = glob_seq(a, b); \
			free_glob(a);             \
			free_glob(b);             \
		}                                 \
	} while (0)

static glob *match_glob = NULL;

static void cleanup(glob **start, glob **end)
{
	while (start != end) {
		free_glob(*start);
		++start;
	}
}

static void print_error(char const c)
{
	fprintf(stderr, "pattern error: Unexpected character '%c'\n", c);
}

static glob *handle_operator(char op, glob const *g)
{
	glob *tmp = NULL;

	switch (op) {
	case '!':
		tmp = glob_not(g);
		break;
	case '*':
		tmp = glob_star(g);
		break;
	case '+':
		tmp = glob_plus(g);
		break;
	case '@':
		tmp = glob_at(g);
		break;
	case '?':
		tmp = glob_opt(g);
		break;
	}
	assert(tmp);
	return tmp;
}

#define push_frag(f) *frag++ = f
#define pop_frag() *--frag
#define ARRAY_SIZE 100

static glob *compile(char const *pat)
{
	glob *frags[ARRAY_SIZE] = { 0 };
	glob **frag = frags;
	struct paren {
		int alter;
		int atoms;
		char op;
	} paren[ARRAY_SIZE], *pa;

	int alter = 0;
	int atoms = 0;

	pa = paren;

	assert(pat);

	for (;;) {
		unsigned char p = *pat++;
		if (!p)
			break;
		switch (p) {
		case '!':
		case '?':
		case '@':
		case '*':
		case '+':
			if (*pat != '(')
				goto character;
			if (pa >= paren + ARRAY_SIZE) {
				fprintf(stderr,
					"pattern error: to many nested globs.\n");
				goto error;
			}
			cat_one();
			*pa = (struct paren){ .alter = alter,
					      .atoms = atoms,
					      .op = p };
			pa++;
			alter = 0;
			atoms = 0;
			p = *pat++;
			break;

		case '(':
			print_error(p);
			goto error;

		case ')': {
			glob *tmp, *a;
			if (pa == paren || !atoms) {
				print_error(p);
				goto error;
			}
			--pa;
			cat_all();
			a = pop_frag();
			tmp = handle_operator(pa->op, a);
			free_glob(a);
			push_frag(tmp);

			for (; alter > 0; --alter) {
				glob *b = pop_frag();
				glob *a = pop_frag();
				if (pa->op == '!')
					push_frag(glob_and(a, b));
				else
					push_frag(glob_or(a, b));
				--atoms;
				free_glob(a);
				free_glob(b);
			}

			atoms = pa->atoms;
			alter = pa->alter;
			atoms++;
		} break;

		case '[': {
			char *strPat;
			char const *end;
			cat_one();
			end = strchr(pat, ']');
			if (!end) {
				fprintf(stderr,
					"pattern error: Mismatching brackets.\n");
				goto error;
			}
			strPat = strdup(pat);
			strPat[end - pat] = '\0';
			push_frag(glob_cset(strPat));
			++atoms;
			free(strPat);
			pat = end + 1;
			break;
		}

		case '|': {
			glob *a;
			glob *tmp;
			char op;
			if (atoms == 0 || pa == paren) {
				print_error(p);
				goto error;
			}
			cat_all();
			a = pop_frag();
			op = (pa - 1)->op;
			tmp = handle_operator(op, a);
			free_glob(a);
			push_frag(tmp);

			++alter;
		} break;

		case '\\':
			p = *pat++;
		/* FALLTHROUGH */
		default: /* literal character */
character:
			cat_one();
			push_frag(glob_char(p));
			++atoms;
		}
	}
	if (pa != paren) {
		fprintf(stderr, "pattern error: Mismatching parenthesis\n");
		goto error;
	}

	cat_all();

	return frags[0];

error:
	cleanup(frags, frag);
	return NULL;
}

int clob_compile_pattern(char const *pattern)
{
	match_glob = compile(pattern);
	return match_glob ? 1 : 0;
}

int clob_match(char const *string)
{
	return match_glob->matches(match_glob, string);
}

void clob_free_pattern()
{
	free_glob(match_glob);
}

#ifdef _CLOB_DEBUG_BRZ_

void clob_print_pattern()
{
	match_glob->print(match_glob);
}

#endif
