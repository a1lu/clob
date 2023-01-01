#include "clob/clob.h"
#include <gtest/gtest.h>

TEST(nested_glob, at_plus_nested)
{
	struct clob_pattern *pattern = clob_compile_pattern("@(+(nest)ed)");
	EXPECT_FALSE(clob_match(pattern, "misc/passing"));
	EXPECT_FALSE(clob_match(pattern, "misc/failing"));
	EXPECT_TRUE(clob_match(pattern, "nested"));
	EXPECT_TRUE(clob_match(pattern, "nestnested"));
	EXPECT_FALSE(clob_match(pattern, ""));
	clob_free_pattern(pattern);
}

TEST(nested_glob, qm_star_a_or_b)
{
	struct clob_pattern *pattern = clob_compile_pattern("?(*(a|b))");
	EXPECT_FALSE(clob_match(pattern, "misc/passing"));
	EXPECT_FALSE(clob_match(pattern, "misc/failing"));
	EXPECT_TRUE(clob_match(pattern, "aa"));
	EXPECT_TRUE(clob_match(pattern, "bb"));
	EXPECT_FALSE(clob_match(pattern, "ab"));
	EXPECT_TRUE(clob_match(pattern, ""));
	clob_free_pattern(pattern);
}

TEST(nested_glob, star_passing_at_star)
{
	struct clob_pattern *pattern =
		clob_compile_pattern("misc/pa@(s|*(s))ing");
	EXPECT_TRUE(clob_match(pattern, "misc/paing"));
	EXPECT_TRUE(clob_match(pattern, "misc/pasing"));
	EXPECT_TRUE(clob_match(pattern, "misc/passing"));
	EXPECT_TRUE(clob_match(pattern, "misc/passsing"));
	EXPECT_FALSE(clob_match(pattern, "misc/failing"));
	clob_free_pattern(pattern);
}
