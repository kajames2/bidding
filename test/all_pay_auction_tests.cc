#include <gtest/gtest.h>
#include <vector>
#include "bidding/all_pay_auction.h"
#include "bidding/bid_function_ops.h"
#include "bidding/distribution.h"
#include "boost/math/distributions/uniform.hpp"

namespace gatests {

class AllPayAuctionTest : public ::testing::Test {
 public:
  AllPayAuctionTest() {}

 protected:
  virtual void SetUp() {}
  bidding::AllPayAuction auction =
      bidding::AllPayAuction(std::vector<float>{1, 1});
  float epsilon = 0.0001;
};

TEST_F(AllPayAuctionTest, NoSingularityTest) {
  auto bid_func = [](float x) { return x*x; };
  auction.AcceptStrategy(bid_func, 0);
  auction.AcceptStrategy(bid_func, 1);
  float fit = auction.GetFitness(bid_func, 1);
  EXPECT_NEAR(-1/6., fit, epsilon);
}

// TEST_F(AllPayAuctionTest, OneSingularityAtValueTest) {
//   auto bid_func = [](float x) { return x; };
//   auto bid_func2 = [](float x) { return 0; };
//   auction.AcceptStrategy(bid_func, 0);
//   auction.AcceptStrategy(bid_func2, 1);
//   float fit = auction.GetFitness(bid_func, 0);
//   float fit2 = auction.GetFitness(bid_func2, 1);
//   EXPECT_NEAR(-0.5, fit, epsilon);
//   EXPECT_NEAR(0, fit2, epsilon);
// }

// TEST_F(AllPayAuctionTest, OneSingularityAtZeroTest) {
//   auto bid_func = [](float x) { return x; };
//   auto bid_func2 = [](float x) { return 1; };
//   auction.AcceptStrategy(bid_func, 0);
//   auction.AcceptStrategy(bid_func2, 1);
//   float fit = auction.GetFitness(bid_func, 0);
//   float fit2 = auction.GetFitness(bid_func2, 1);
//   EXPECT_NEAR(0.5, fit, epsilon);
//   EXPECT_NEAR(0, fit2, epsilon);
// }

// TEST_F(AllPayAuctionTest, TwoSingularityAtZeroTest) {
//   auto bid_func = [](float x) { return 0.3; };
//   auto bid_func2 = [](float x) { return 1; };
//   auction.AcceptStrategy(bid_func, 0);
//   auction.AcceptStrategy(bid_func2, 1);
//   float fit = auction.GetFitness(bid_func, 0);
//   float fit2 = auction.GetFitness(bid_func2, 1);
//   EXPECT_NEAR(0.15, fit, epsilon);
//   EXPECT_NEAR(0.15, fit2, epsilon);
// }

// TEST_F(AllPayAuctionTest, TwoSingularityAtValueTest) {
//   auto bid_func = [](float x) { return 0.3; };
//   auto bid_func2 = [](float x) { return 0; };
//   auction.AcceptStrategy(bid_func, 0);
//   auction.AcceptStrategy(bid_func2, 1);
//   float fit = auction.GetFitness(bid_func, 0);
//   float fit2 = auction.GetFitness(bid_func2, 1);
//   EXPECT_NEAR(-0.35, fit, epsilon);
//   EXPECT_NEAR(-0.35, fit2, epsilon);
// }

// TEST_F(AllPayAuctionTest, AllSingularitiesTest) {
//   auto bid_func = [](float x) { return 0.3; };
//   auto bid_func2 = [](float x) { return 0.6; };
//   auction.AcceptStrategy(bid_func, 0);
//   auction.AcceptStrategy(bid_func2, 1);
//   float fit = auction.GetFitness(bid_func, 0);
//   float fit2 = auction.GetFitness(bid_func2, 1);
//   EXPECT_NEAR(-0.05, fit, epsilon);
//   EXPECT_NEAR(-0.05, fit2, epsilon);
// }

// TEST_F(AllPayAuctionTest, FullTest) {
//   auto bid_func = [](float x) { return 0.3 + x/2.; };
//   auto bid_func2 = [](float x) { return 0.1 + x/2.; };
//   auction.AcceptStrategy(bid_func, 0);
//   auction.AcceptStrategy(bid_func2, 1);
//   float fit = auction.GetFitness(bid_func, 0);
//   float fit2 = auction.GetFitness(bid_func2, 1);
//   EXPECT_NEAR(-0.1, fit, epsilon);
//   EXPECT_NEAR(0, fit2, epsilon);
// }

}  // namespace gatests
