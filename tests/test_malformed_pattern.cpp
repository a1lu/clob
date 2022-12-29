#include "clob/clob.h"
#include <gtest/gtest.h>

TEST(malformed_pattern, mismatching_parenthesis)
{
	char *pattern = (char *)"?(malformed";
	int ret = compile_pattern(pattern);
	EXPECT_FALSE(ret);
}

TEST(malformed_pattern, unexpected_parenthesis)
{
	char *pattern = (char *)"(malformed";
	int ret = compile_pattern(pattern);
	EXPECT_FALSE(ret);
}

TEST(malformed_pattern, unexpected_parenthesis_2)
{
	char *pattern = (char *)"misc/passing)";
	int ret = compile_pattern(pattern);
	EXPECT_FALSE(ret);
}

TEST(malformed_pattern, mismatching_brackets)
{
	char *pattern = (char *)"misc/[";
	int ret = compile_pattern(pattern);
	EXPECT_FALSE(ret);
}

TEST(malformed_pattern, mismatching_brackets_2)
{
	char *pattern = (char *)"misc/[a-";
	int ret = compile_pattern(pattern);
	EXPECT_FALSE(ret);
}

TEST(malformed_pattern, unexpected_character_pipe)
{
	char *pattern = (char *)"|pipe";
	int ret = compile_pattern(pattern);
	EXPECT_FALSE(ret);
}
