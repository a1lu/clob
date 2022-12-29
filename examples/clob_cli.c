#include <stdio.h>
#include "clob/clob.h"

int main(int argc, char *argv[])
{
	if (argc < 3) {
		printf("usage: %s \"pattern\" \"string\"\n", argv[0]);
		return 1;
	}
	printf("argv: %s\n", argv[1]);
	if (compile_pattern(argv[1])) {
		print_pattern();
		puts("");
		puts("");
		printf("matched: %d\n", match(argv[2]));
		free_pattern();
		return 0;
	}
	return 1;
}
