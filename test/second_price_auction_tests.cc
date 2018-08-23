#include <gtest/gtest.h>
#include <vector>
#include "bidding/bid_function_ops.h"
#include "bidding/distribution.h"
#include "bidding/second_price_auction.h"
#include "boost/math/distributions/uniform.hpp"

namespace gatests {

class SecondPriceAuctionTest : public ::testing::Test {
 public:
  SecondPriceAuctionTest() {}

 protected:
  virtual void SetUp() {}
  bidding::SecondPriceAuction auction =
      bidding::SecondPriceAuction(std::vector<bidding::Distribution>{
          boost::math::uniform_distribution<>(0, 1),
          boost::math::uniform_distribution<>(0, 1)});
  float epsilon = 0.001;
};

TEST_F(SecondPriceAuctionTest, AlwaysWinTest) {
  auto func1 = [](float x) { return 0; };
  auto func2 = [](float x) { return 1; };
  auction.AcceptStrategy(func1, 0);
  auction.AcceptStrategy(func2, 1);
  float fit = auction.GetFitness(func2, 1);
  EXPECT_NEAR(0.5, fit, epsilon);
}

TEST_F(SecondPriceAuctionTest, WinHalfTest) {
  auto bid_func = [](float x) { return x; };
  auction.AcceptStrategy(bid_func, 0);
  auction.AcceptStrategy(bid_func, 1);
  float fit = auction.GetFitness([](float x) { return x; }, 1);
  EXPECT_NEAR(.166666, fit, epsilon);
}

TEST_F(SecondPriceAuctionTest, DecreasingBidsTest) {
  auto bid_func = [](float x) { return 1 - x; };
  auto bid_func2 = [](float x) { return x; };
  auction.AcceptStrategy(bid_func, 0);
  auction.AcceptStrategy(bid_func2, 1);
  float fit = auction.GetFitness(bid_func2, 1);
  EXPECT_NEAR(.166666, fit, epsilon);
}

TEST_F(SecondPriceAuctionTest, DecreasingBids2Test) {
  auto bid_func = [](float x) { return x; };
  auto bid_func2 = [](float x) { return 1 - x; };
  auction.AcceptStrategy(bid_func, 0);
  auction.AcceptStrategy(bid_func2, 1);
  float fit = auction.GetFitness(bid_func2, 1);
  EXPECT_NEAR(0, fit, epsilon);
}

TEST_F(SecondPriceAuctionTest, NoIntersectDistsTest) {
  auction = bidding::SecondPriceAuction(std::vector<bidding::Distribution>{
      boost::math::uniform_distribution<>(20, 40),
      boost::math::uniform_distribution<>(40, 60)});
  epsilon = 0.015;
  auto bid_func = [](float x) { return 20; };
  auto bid_func2 = [](float x) { return 21; };
  auction.AcceptStrategy(bid_func, 0);
  auction.AcceptStrategy(bid_func2, 1);
  float fit = auction.GetFitness(bid_func, 0);
  EXPECT_NEAR(0, fit, epsilon);
  float fit2 = auction.GetFitness(bid_func2, 1);
  EXPECT_NEAR(30, fit2, epsilon);
}

}  // namespace gatests
