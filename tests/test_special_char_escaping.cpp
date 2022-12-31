#include "clob/clob.h"
#include <gtest/gtest.h>

TEST(special_char_escaping, unexpected_character)
{
	struct clob_pattern *pattern = clob_compile_pattern("\\!(escaped)");
	EXPECT_EQ(pattern, nullptr);
}

TEST(special_char_escaping, escaped_em)
{
	struct clob_pattern *pattern = clob_compile_pattern("\\!escaped");
	EXPECT_NE(pattern, nullptr);
}
