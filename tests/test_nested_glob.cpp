#include "clob/clob.h"
#include <gtest/gtest.h>

TEST(nested_glob, at_plus_nested)
{
	char *pattern = "@(+(nest)ed)";
	clob_compile_pattern(pattern);
	EXPECT_FALSE(clob_match("misc/passing"));
	EXPECT_FALSE(clob_match("misc/failing"));
	EXPECT_TRUE(clob_match("nested"));
	EXPECT_TRUE(clob_match("nestnested"));
	EXPECT_FALSE(clob_match(""));
}

TEST(nested_glob, qm_star_a_or_b)
{
	char *pattern = "?(*(a|b))";
	clob_compile_pattern(pattern);
	EXPECT_FALSE(clob_match("misc/passing"));
	EXPECT_FALSE(clob_match("misc/failing"));
	EXPECT_TRUE(clob_match("aa"));
	EXPECT_TRUE(clob_match("bb"));
	EXPECT_FALSE(clob_match("ab"));
	EXPECT_TRUE(clob_match(""));
}

TEST(nested_glob, star_passing_at_star)
{
	char *pattern = "misc/pa@(s|*(s))ing";
	clob_compile_pattern(pattern);
	EXPECT_TRUE(clob_match("misc/paing"));
	EXPECT_TRUE(clob_match("misc/pasing"));
	EXPECT_TRUE(clob_match("misc/passing"));
	EXPECT_TRUE(clob_match("misc/passsing"));
	EXPECT_FALSE(clob_match("misc/failing"));
}
