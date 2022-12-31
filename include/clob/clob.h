#ifndef CLOB_H
#define CLOB_H

#ifdef __cplusplus
extern "C" {
#endif

int clob_compile_pattern(char const *pattern);
int clob_match(char const *string);
void clob_free_pattern();

#ifdef __cplusplus
}
#endif

#endif /* end of include guard: CLOB_H */
