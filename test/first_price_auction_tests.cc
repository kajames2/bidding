#include <gtest/gtest.h>
#include <vector>
#include "bidding/bid_function_ops.h"
#include "bidding/distribution.h"
#include "bidding/first_price_auction.h"
#include "boost/math/distributions/uniform.hpp"

namespace gatests {

class FirstPriceAuctionTest : public ::testing::Test {
 public:
  FirstPriceAuctionTest() {}

 protected:
  virtual void SetUp() {}
  bidding::FirstPriceAuction auction =
      bidding::FirstPriceAuction(std::vector<bidding::Distribution>{
          boost::math::uniform_distribution<>(0, 1),
          boost::math::uniform_distribution<>(0, 1)});
  float epsilon = 0.0001;
};

TEST_F(FirstPriceAuctionTest, AlwaysWinTest) {
  auction.AcceptStrategy([](float x) { return 0; }, 0);
  float fit = auction.GetFitness([](float x) { return 0.01; }, 1);
  EXPECT_NEAR(0.49, fit, epsilon);
}

TEST_F(FirstPriceAuctionTest, WinHalfTest) {
  auto bid_func = [](float x) { return x / 2; };
  auction.AcceptStrategy(bid_func, 0);
  float fit = auction.GetFitness([](float x) { return x / 2; }, 1);
  EXPECT_NEAR(.166666, fit, epsilon);
}


TEST_F(FirstPriceAuctionTest, DecreasingBidsTest) {
  auto bid_func = [](float x) { return 0.5 - x / 2; };
  auction.AcceptStrategy(bid_func, 0);
  float fit = auction.GetFitness([](float x) { return x / 2; }, 1);
  EXPECT_NEAR(.166666, fit, epsilon);
}

TEST_F(FirstPriceAuctionTest, DecreasingBids2Test) {
  auto bid_func = [](float x) { return x / 2; };
  auction.AcceptStrategy(bid_func, 0);
  float fit = auction.GetFitness([](float x) { return 0.5 - 0.5*x; }, 1);
  EXPECT_NEAR(0, fit, epsilon);
}

TEST_F(FirstPriceAuctionTest, NoIntersectDistsTest) {
  auction = bidding::FirstPriceAuction(std::vector<bidding::Distribution>{
      boost::math::uniform_distribution<>(20, 40),
      boost::math::uniform_distribution<>(40, 60)});
  float epsilon = 0.001;
  auto bid_func = [](float x) { return 20; };
  auction.AcceptStrategy(bid_func, 0);
  auto bid_func2 = [](float x) { return 20.2; };
  auction.AcceptStrategy(bid_func2, 1);
  float fit = auction.GetFitness(bid_func, 0);
  EXPECT_NEAR(0, fit, epsilon);
  float fit2 = auction.GetFitness(bid_func2, 1);
  EXPECT_NEAR(29.8, fit2, epsilon);
}

}  // namespace gatests
