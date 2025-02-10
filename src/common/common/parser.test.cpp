#include <common/parser.hpp>
#include <gtest/gtest.h>

#include <string>

using namespace parser;

TEST(test_modify_str, parser_test) {

  std::string text = "6522349";
  modify_str(text);

  ASSERT_EQ(text, "9KB5KB3KBKB");
}

TEST(test_total_sum_of_nums, parser_test) {

  std::string result = total_sum_of_nums("9KB5KB3KBKB");

  ASSERT_EQ(result, "17");
}

TEST(test_analyze_message, parser_test) {

  bool result = analyze_message("128");
  bool result2 = analyze_message("35");

  ASSERT_EQ(result, true);
  ASSERT_EQ(result2, false);
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}