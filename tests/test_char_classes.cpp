#include "clob/clob.h"
#include <gtest/gtest.h>

TEST(character_classes, misc_choice)
{
	char *pattern = "misc/[pf]assing";
	compile_pattern(pattern);
	EXPECT_TRUE(match("misc/passing"));
	EXPECT_FALSE(match("misc/failing"));
}

TEST(character_classes, misc_range)
{
	char *pattern = "misc/[p-s]assing";
	compile_pattern(pattern);
	EXPECT_TRUE(match("misc/passing"));
	EXPECT_FALSE(match("misc/failing"));
}

TEST(character_classes, misc_negate_choice_failing)
{
	char *pattern = "misc/[!f]ailing";
	compile_pattern(pattern);
	EXPECT_FALSE(match("misc/passing"));
	EXPECT_FALSE(match("misc/failing"));
}

TEST(character_classes, misc_choice_failing)
{
	char *pattern = "misc/[p-f]ailing";
	compile_pattern(pattern);
	EXPECT_FALSE(match("misc/passing"));
	EXPECT_TRUE(match("misc/failing"));
}

TEST(character_classes, misc_negate_choice_passing)
{
	char *pattern = "misc/[!azerty]assing";
	compile_pattern(pattern);
	EXPECT_TRUE(match("misc/passing"));
	EXPECT_FALSE(match("misc/failing"));
}
