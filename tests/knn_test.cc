// ./test/knn_test.cc
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <lib/k_nearest_neighbors.h>
#include <string>
#include <vector>

TEST(MajorityVote, ExpectedCorrectValue) {
  std::vector<std::string> labels_majority = {"a", "b", "c", "a", "b"};
  EXPECT_EQ(knn::majority_vote(labels_majority), "a");
}
