#include <stdio.h>
#include "clob/clob.h"

int main(int argc, char *argv[])
{
	if (argc < 3) {
		printf("usage: %s \"pattern\" \"string\"\n", argv[0]);
		return 1;
	}
	printf("argv: %s\n", argv[1]);
	if (clob_compile_pattern(argv[1])) {
		clob_print_pattern();
		puts("");
		puts("");
		printf("matched: %d\n", clob_match(argv[2]));
		clob_free_pattern();
		return 0;
	}
	return 1;
}
