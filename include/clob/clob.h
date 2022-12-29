#ifndef CLOB_H
#define CLOB_H

#ifdef __cplusplus
extern "C" {
#endif

int compile_pattern(char const *pattern);
int match(char const *string);
void free_pattern();

#ifdef __cplusplus
}
#endif

#endif /* end of include guard: CLOB_H */
