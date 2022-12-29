#include "clob/clob.h"
#include <gtest/gtest.h>

TEST(simple_glob, star_passing)
{
	char *pattern = "*/passing";
	compile_pattern(pattern);
	EXPECT_TRUE(match("misc/passing"));
	EXPECT_FALSE(match("misc/failing"));
}

TEST(simple_glob, qm_passing)
{
	char *pattern = "*/pa?sing";
	compile_pattern(pattern);
	EXPECT_TRUE(match("misc/passing"));
	EXPECT_FALSE(match("misc/failing"));
}

TEST(simple_glob, misc_passing_qm)
{
	char *pattern = "misc/passing?";
	compile_pattern(pattern);
	EXPECT_TRUE(match("misc/passing"));
	EXPECT_FALSE(match("misc/failing"));
}

TEST(simple_glob, misc_star)
{
	char *pattern = "misc/*";
	compile_pattern(pattern);
	EXPECT_TRUE(match("misc/passing"));
	EXPECT_TRUE(match("misc/failing"));
}
