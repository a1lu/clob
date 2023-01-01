#include "clob/clob.h"
#include <gtest/gtest.h>

TEST(malformed_pattern, mismatching_parenthesis)
{
	struct clob_pattern *pattern = clob_compile_pattern("?(malformed");
	EXPECT_EQ(pattern, nullptr);
}

TEST(malformed_pattern, unexpected_parenthesis)
{
	struct clob_pattern *pattern = clob_compile_pattern("(malformed");
	EXPECT_EQ(pattern, nullptr);
}

TEST(malformed_pattern, unexpected_parenthesis_2)
{
	struct clob_pattern *pattern = clob_compile_pattern("misc/passing)");
	EXPECT_EQ(pattern, nullptr);
}

TEST(malformed_pattern, mismatching_brackets)
{
	struct clob_pattern *pattern = clob_compile_pattern("misc/[");
	EXPECT_EQ(pattern, nullptr);
}

TEST(malformed_pattern, mismatching_brackets_2)
{
	struct clob_pattern *pattern = clob_compile_pattern("misc/[a-");
	EXPECT_EQ(pattern, nullptr);
}

TEST(malformed_pattern, unexpected_character_pipe)
{
	struct clob_pattern *pattern = clob_compile_pattern("|pipe");
	EXPECT_EQ(pattern, nullptr);
}
