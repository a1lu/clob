#include "clob/clob.h"
#include <gtest/gtest.h>

TEST(ext_glob, negate_passing)
{
	struct clob_pattern *pattern = clob_compile_pattern("!(*/passing)");
	EXPECT_FALSE(clob_match(pattern, "misc/passing"));
	EXPECT_TRUE(clob_match(pattern, "misc/failing"));
	clob_free_pattern(pattern);
}

TEST(ext_glob, at_misc_passing)
{
	struct clob_pattern *pattern = clob_compile_pattern("@(misc)/passing");
	EXPECT_TRUE(clob_match(pattern, "misc/passing"));
	EXPECT_FALSE(clob_match(pattern, "misc/failing"));
	clob_free_pattern(pattern);
}

TEST(ext_glob, star_misc_plus_passing)
{
	struct clob_pattern *pattern =
		clob_compile_pattern("*(misc)/pa+(s)ing");
	EXPECT_TRUE(clob_match(pattern, "misc/passing"));
	EXPECT_FALSE(clob_match(pattern, "misc/failing"));
	clob_free_pattern(pattern);
}

TEST(ext_glob, misc_passing_or_failing_char_classes)
{
	struct clob_pattern *pattern =
		clob_compile_pattern("misc/[pf]a@(ss|il)ing");
	EXPECT_TRUE(clob_match(pattern, "misc/passing"));
	EXPECT_TRUE(clob_match(pattern, "misc/failing"));
	clob_free_pattern(pattern);
}

TEST(ext_glob, negate_failing)
{
	struct clob_pattern *pattern =
		clob_compile_pattern("!(*/failing|*/fail)");
	EXPECT_TRUE(clob_match(pattern, "misc/passing"));
	EXPECT_FALSE(clob_match(pattern, "misc/failing"));
	clob_free_pattern(pattern);
}

TEST(ext_glob, misc_qm_passing)
{
	struct clob_pattern *pattern = clob_compile_pattern("misc/?(passing)");
	EXPECT_TRUE(clob_match(pattern, "misc/passing"));
	EXPECT_FALSE(clob_match(pattern, "misc/failing"));
	clob_free_pattern(pattern);
}

TEST(ext_glob, misc_passing_or_failing)
{
	struct clob_pattern *pattern =
		clob_compile_pattern("misc/?(passing|failing)");
	EXPECT_TRUE(clob_match(pattern, "misc/passing"));
	EXPECT_TRUE(clob_match(pattern, "misc/failing"));
	clob_free_pattern(pattern);
}

TEST(ext_glob, misc_star_negate_passing)
{
	struct clob_pattern *pattern = clob_compile_pattern("misc/*!(passing)");
	EXPECT_TRUE(clob_match(pattern, "misc/passing"));
	EXPECT_TRUE(clob_match(pattern, "misc/failing"));
	clob_free_pattern(pattern);
}
