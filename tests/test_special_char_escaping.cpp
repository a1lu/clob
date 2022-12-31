#include "clob/clob.h"
#include <gtest/gtest.h>

TEST(special_char_escaping, unexpected_character)
{
	char *pattern = (char *)"\\!(escaped)";
	int ret = clob_compile_pattern(pattern);
	EXPECT_FALSE(ret);
}

TEST(special_char_escaping, escaped_em)
{
	char *pattern = (char *)"\\!escaped";
	int ret = clob_compile_pattern(pattern);
	EXPECT_TRUE(ret);
}
