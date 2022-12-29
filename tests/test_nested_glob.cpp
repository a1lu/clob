#include "clob/clob.h"
#include <gtest/gtest.h>

TEST(nested_glob, at_plus_nested)
{
	char *pattern = "@(+(nest)ed)";
	compile_pattern(pattern);
	EXPECT_FALSE(match("misc/passing"));
	EXPECT_FALSE(match("misc/failing"));
	EXPECT_TRUE(match("nested"));
	EXPECT_TRUE(match("nestnested"));
	EXPECT_FALSE(match(""));
}

TEST(nested_glob, qm_star_a_or_b)
{
	char *pattern = "?(*(a|b))";
	compile_pattern(pattern);
	EXPECT_FALSE(match("misc/passing"));
	EXPECT_FALSE(match("misc/failing"));
	EXPECT_TRUE(match("aa"));
	EXPECT_TRUE(match("bb"));
	EXPECT_FALSE(match("ab"));
	EXPECT_TRUE(match(""));
}

TEST(nested_glob, star_passing_at_star)
{
	char *pattern = "misc/pa@(s|*(s))ing";
	compile_pattern(pattern);
	EXPECT_TRUE(match("misc/paing"));
	EXPECT_TRUE(match("misc/pasing"));
	EXPECT_TRUE(match("misc/passing"));
	EXPECT_TRUE(match("misc/passsing"));
	EXPECT_FALSE(match("misc/failing"));
}
