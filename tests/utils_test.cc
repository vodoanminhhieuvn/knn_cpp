// ./test/utils_test.c
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <lib/utils.h>
#include <numeric>
#include <vector>

TEST(SplitDataTest, ExpectedCorrectValue) {
  std::vector<int> data(1000);
  std::iota(data.begin(), data.end(), 0);

  auto [train, test] = split_data(data, 0.75);

  EXPECT_EQ(train.size(), 750);
  EXPECT_EQ(test.size(), 250);

  std::vector<int> combined_data(train.begin(), train.end());
  combined_data.insert(combined_data.end(), test.begin(), test.end());
  std::sort(combined_data.begin(), combined_data.end());

  for (size_t i = 0; i < combined_data.size(); ++i) {
    EXPECT_EQ(combined_data[i], static_cast<int>(i));
  }
}
