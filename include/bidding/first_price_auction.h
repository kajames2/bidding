#ifndef _BIDDING_FIRST_PRICE_AUCTION_H_
#define _BIDDING_FIRST_PRICE_AUCTION_H_

#include <boost/math/quadrature/gauss_kronrod.hpp>
#include "bidding/piecewise_linear_function.h"
#include "bidding/distribution.h"

namespace bidding {

class FirstPriceAuction {
 public:
  FirstPriceAuction(
      std::vector<Distribution> value_dists);
  double GetValue(double bid, double value) const;
  void AcceptStrategy(PiecewiseLinearFunction bid, int id);
  double GetFitness(const PiecewiseLinearFunction& bid_func, int id) const;

 private:
  double GetIntegrand(const PiecewiseLinearFunction& bid_func, int id,
                      double value) const;
  std::vector<PiecewiseLinearFunction> bid_funcs_;
  std::vector<PiecewiseLinearFunction> inv_bid_funcs_;
  std::vector<Distribution> value_dists_;
  int n_players_;
};

}  // namespace bidding

#endif  // _BIDDING_FIRST_PRICE_AUCTION_H_
