// ./test/la_test.cc
#include <gtest/gtest.h>
#include <lib/linear_algebra.h>

TEST(VectorSubtractTest, ExpectCorrectValue) {
  Vector v{5, 7, 9};
  Vector w{4, 5, 6};

  Vector result = linear_algebra::subtract(v, w);

  EXPECT_EQ(result, Vector({1, 2, 3}));
}

TEST(VectorDotTest, ExpectCorrectValue) {
  Vector v{1, 2, 3};
  Vector w{4, 5, 6};

  double result = linear_algebra::dot(v, w);

  EXPECT_EQ(result, 32);
}

TEST(SumOfSquaresTest, ExpectCorrectValue) {
  Vector v{1, 2, 3};

  double result = linear_algebra::sum_of_squares(v);

  EXPECT_EQ(result, 14);
}

TEST(MagnitudeTest, ExpectCorrectValue) {
  Vector v{3, 4};

  double result = linear_algebra::magnitude(v);

  EXPECT_EQ(result, 5);
}
