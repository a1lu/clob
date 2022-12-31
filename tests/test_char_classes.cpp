#include "clob/clob.h"
#include <gtest/gtest.h>

TEST(character_classes, misc_choice)
{
	struct clob_pattern *pattern = clob_compile_pattern("misc/[pf]assing");
	EXPECT_TRUE(clob_match(pattern, "misc/passing"));
	EXPECT_FALSE(clob_match(pattern, "misc/failing"));
	clob_free_pattern(pattern);
}

TEST(character_classes, misc_range)
{
	struct clob_pattern *pattern = clob_compile_pattern("misc/[p-s]assing");
	EXPECT_TRUE(clob_match(pattern, "misc/passing"));
	EXPECT_FALSE(clob_match(pattern, "misc/failing"));
	clob_free_pattern(pattern);
}

TEST(character_classes, misc_negate_choice_failing)
{
	struct clob_pattern *pattern = clob_compile_pattern("misc/[!f]ailing");
	EXPECT_FALSE(clob_match(pattern, "misc/passing"));
	EXPECT_FALSE(clob_match(pattern, "misc/failing"));
	clob_free_pattern(pattern);
}

TEST(character_classes, misc_choice_failing)
{
	struct clob_pattern *pattern = clob_compile_pattern("misc/[p-f]ailing");
	EXPECT_FALSE(clob_match(pattern, "misc/passing"));
	EXPECT_TRUE(clob_match(pattern, "misc/failing"));
	clob_free_pattern(pattern);
}

TEST(character_classes, misc_negate_choice_passing)
{
	struct clob_pattern *pattern =
		clob_compile_pattern("misc/[!azerty]assing");
	EXPECT_TRUE(clob_match(pattern, "misc/passing"));
	EXPECT_FALSE(clob_match(pattern, "misc/failing"));
	clob_free_pattern(pattern);
}
