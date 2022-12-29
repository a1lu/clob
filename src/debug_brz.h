#ifndef CLOB_DEBUG_BRZ_H
#define CLOB_DEBUG_BRZ_H

#ifdef __cplusplus
extern "C" {
#endif

#include "brz.h"

#define print_glob_v(g)                  \
	do {                             \
		printf(#g " ");          \
		(g)->print(g), puts(""); \
	} while (0)

#define print_glob(g)          \
	do {                   \
		(g)->print(g); \
	} while (0)

void print_empty(glob const *self);
void print_blank(glob const *self);
void print_char(glob const *self);
void print_cset(glob const *self);
void print_or(glob const *self);
void print_and(glob const *self);
void print_star(glob const *self);
void print_plus(glob const *self);
void print_at(glob const *self);
void print_opt(glob const *self);
void print_seq(glob const *self);
void print_not(glob const *self);
void print_pattern(void);

#ifdef __cplusplus
}
#endif

#endif /* end of include guard: CLOB_DEBUG_BRZ_H */
