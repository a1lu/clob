#include "clob/clob.h"
#include <gtest/gtest.h>

TEST(simple_glob, star_passing)
{
	struct pattern *pattern = clob_compile_pattern("*/passing");
	EXPECT_TRUE(clob_match(pattern, "misc/passing"));
	EXPECT_FALSE(clob_match(pattern, "misc/failing"));
	clob_free_pattern(pattern);
}

TEST(simple_glob, qm_passing)
{
	struct pattern *pattern = clob_compile_pattern("*/pa?sing");
	EXPECT_TRUE(clob_match(pattern, "misc/passing"));
	EXPECT_FALSE(clob_match(pattern, "misc/failing"));
	clob_free_pattern(pattern);
}

TEST(simple_glob, misc_passing_qm)
{
	char *pattern = "misc/passing?";
	clob_compile_pattern(pattern);
	EXPECT_TRUE(clob_match("misc/passing"));
	EXPECT_FALSE(clob_match("misc/failing"));
}

TEST(simple_glob, misc_star)
{
	char *pattern = "misc/*";
	clob_compile_pattern(pattern);
	EXPECT_TRUE(clob_match("misc/passing"));
	EXPECT_TRUE(clob_match("misc/failing"));
}
