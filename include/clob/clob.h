#ifndef CLOB_H
#define CLOB_H

#ifdef __cplusplus
extern "C" {
#endif

struct clob_pattern;

struct clob_pattern *clob_compile_pattern(char const *pattern);
int clob_match(struct clob_pattern *pattern, char const *string);
void clob_free_pattern(struct clob_pattern *pattern);

#ifdef _CLOB_DEBUG_BRZ_
void clob_print_pattern(struct clob_pattern *pattern);
#endif

#ifdef __cplusplus
}
#endif

#endif /* end of include guard: CLOB_H */
