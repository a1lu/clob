#ifndef CLOB_BRZ_H
#define CLOB_BRZ_H

#ifdef __cplusplus
extern "C" {
#endif

struct stc_glob;

typedef int (*match_func)(struct stc_glob const *self, char const *string);
typedef struct stc_glob *(*derive_func)(struct stc_glob const *self,
					char const chr);
typedef int (*nullable_func)(struct stc_glob const *self);
typedef struct stc_glob *(*copy_func)(struct stc_glob const *cpy);
typedef void (*printFunc)(struct stc_glob const *self);

typedef enum {
	EMPTY = 0,
	BLANK,
	CHAR,
	CHARSET,
	OR,
	AND,
	STAR,
	PLUS,
	AT,
	OPT,
	SEQ,
	NOT
} glob_type;

typedef struct stc_glob {
	glob_type type;
	match_func matches;
	derive_func derive;
	nullable_func nullable;
	copy_func copy;
#ifdef _CLOB_DEBUG_BRZ_
	printFunc print;
#endif
	union {
		char c;
		char *cset;
		struct stc_glob const *first;
		struct stc_glob const *pattern;
	};
	union {
		struct stc_glob const *second;
	};
} glob;

void free_glob(glob *tmp);

glob *glob_empty();
glob *glob_blank();
glob *glob_char(char c);
glob *glob_cset(char *c);
glob *glob_or(glob const *first, glob const *second);
glob *glob_and(glob const *first, glob const *second);
glob *glob_star(glob const *pattern);
glob *glob_plus(glob const *pattern);
glob *glob_at(glob const *pattern);
glob *glob_opt(glob const *pattern);
glob *glob_not(glob const *pattern);
glob *glob_seq(glob const *first, glob const *second);

#ifdef __cplusplus
}
#endif

#endif /* end of include guard: CLOB_BRZ_H */
