#include "clob/clob.h"
#include <gtest/gtest.h>

TEST(ext_glob, negate_passing)
{
	char *pattern = "!(*/passing)";
	compile_pattern(pattern);
	EXPECT_FALSE(match("misc/passing"));
	EXPECT_TRUE(match("misc/failing"));
}

TEST(ext_glob, at_misc_passing)
{
	char *pattern = "@(misc)/passing";
	compile_pattern(pattern);
	EXPECT_TRUE(match("misc/passing"));
	EXPECT_FALSE(match("misc/failing"));
}

TEST(ext_glob, star_misc_plus_passing)
{
	char *pattern = "*(misc)/pa+(s)ing";
	compile_pattern(pattern);
	EXPECT_TRUE(match("misc/passing"));
	EXPECT_FALSE(match("misc/failing"));
}

TEST(ext_glob, misc_passing_or_failing_char_classes)
{
	char *pattern = "misc/[pf]a@(ss|il)ing";
	compile_pattern(pattern);
	EXPECT_TRUE(match("misc/passing"));
	EXPECT_TRUE(match("misc/failing"));
}

TEST(ext_glob, negate_failing)
{
	char *pattern = "!(*/failing|*/fail)";
	compile_pattern(pattern);
	EXPECT_TRUE(match("misc/passing"));
	EXPECT_FALSE(match("misc/failing"));
}

TEST(ext_glob, misc_qm_passing)
{
	char *pattern = "misc/?(passing)";
	compile_pattern(pattern);
	EXPECT_TRUE(match("misc/passing"));
	EXPECT_FALSE(match("misc/failing"));
}

TEST(ext_glob, misc_passing_or_failing)
{
	char *pattern = "misc/?(passing|failing)";
	compile_pattern(pattern);
	EXPECT_TRUE(match("misc/passing"));
	EXPECT_TRUE(match("misc/failing"));
}

TEST(ext_glob, misc_star_negate_passing)
{
	char *pattern = "misc/*!(passing)";
	compile_pattern(pattern);
	EXPECT_TRUE(match("misc/passing"));
	EXPECT_TRUE(match("misc/failing"));
}
