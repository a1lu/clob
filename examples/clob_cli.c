#include <stdio.h>
#include "clob/clob.h"

int main(int argc, char *argv[])
{
	if (argc < 3) {
		printf("usage: %s \"pattern\" \"string\"\n", argv[0]);
		return 1;
	}
	printf("argv: %s\n", argv[1]);
	struct clob_pattern *pattern = clob_compile_pattern(argv[1]);
	if (pattern) {
		printf("matched: %d\n", clob_match(pattern, argv[2]));
		clob_free_pattern(pattern);
		return 0;
	}
	return 1;
}
