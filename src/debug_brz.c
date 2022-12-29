#include "debug_brz.h"
#include <stdio.h>

void print_empty(glob const *self)
{
	(void)(self);
	printf("Empty");
}

void print_blank(glob const *self)
{
	(void)(self);
	printf("Blank");
}
void print_char(glob const *self)
{
	printf("%c", self->c);
}

void print_cset(glob const *self)
{
	printf("[%s]", self->cset);
}

void print_or(glob const *self)
{
	glob const *first = self->first;
	glob const *sec = self->second;

	printf("(");
	print_glob(first);
	printf(" | ");
	print_glob(sec);
	printf(")");
}

void print_and(glob const *self)
{
	glob const *first = self->first;
	glob const *sec = self->second;

	printf("(");
	print_glob(first);
	printf(" & ");
	print_glob(sec);
	printf(")");
}

void print_seq(glob const *self)
{
	glob const *first = self->first;
	glob const *sec = self->second;

	print_glob(first);
	printf(" . ");
	print_glob(sec);
}

void print_star(glob const *self)
{
	glob const *first = self->first;

	printf("*(");
	print_glob(first);
	printf(")");
}
void print_plus(glob const *self)
{
	glob const *first = self->first;

	printf("+(");
	print_glob(first);
	printf(")");
}
void print_at(glob const *self)
{
	glob const *first = self->first;

	printf("@(");
	print_glob(first);
	printf(")");
}
void print_opt(glob const *self)
{
	glob const *first = self->first;

	printf("?(");
	print_glob(first);
	printf(")");
}
void print_not(glob const *self)
{
	glob const *first = self->first;

	printf("!(");
	print_glob(first);
	printf(")");
}
