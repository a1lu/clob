#include "clob/clob.h"
#include <gtest/gtest.h>

TEST(character_classes, misc_choice)
{
	char *pattern = "misc/[pf]assing";
	clob_compile_pattern(pattern);
	EXPECT_TRUE(clob_match("misc/passing"));
	EXPECT_FALSE(clob_match("misc/failing"));
}

TEST(character_classes, misc_range)
{
	char *pattern = "misc/[p-s]assing";
	clob_compile_pattern(pattern);
	EXPECT_TRUE(clob_match("misc/passing"));
	EXPECT_FALSE(clob_match("misc/failing"));
}

TEST(character_classes, misc_negate_choice_failing)
{
	char *pattern = "misc/[!f]ailing";
	clob_compile_pattern(pattern);
	EXPECT_FALSE(clob_match("misc/passing"));
	EXPECT_FALSE(clob_match("misc/failing"));
}

TEST(character_classes, misc_choice_failing)
{
	char *pattern = "misc/[p-f]ailing";
	clob_compile_pattern(pattern);
	EXPECT_FALSE(clob_match("misc/passing"));
	EXPECT_TRUE(clob_match("misc/failing"));
}

TEST(character_classes, misc_negate_choice_passing)
{
	char *pattern = "misc/[!azerty]assing";
	clob_compile_pattern(pattern);
	EXPECT_TRUE(clob_match("misc/passing"));
	EXPECT_FALSE(clob_match("misc/failing"));
}
