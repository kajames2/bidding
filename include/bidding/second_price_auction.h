#ifndef _BIDDING_SECOND_PRICE_AUCTION_H_
#define _BIDDING_SECOND_PRICE_AUCTION_H_

#include <boost/math/quadrature/gauss_kronrod.hpp>
#include <functional>
#include "bidding/distribution.h"
#include "bidding/piecewise_linear_function.h"

namespace bidding {

class SecondPriceAuction {
 public:
  SecondPriceAuction(std::vector<Distribution> value_dists);
  void AcceptStrategy(std::function<float(float)> bid, int id);
  float GetFitness(const std::function<float(float)>& bid_func,
                    int id) const;

 private:
  double GetIntegrand(const std::function<float(float)>& bid_func, int id,
                      float value) const;
  void Precalculate() const;
  std::vector<std::function<float(float)>> bid_funcs_;
  mutable std::vector<std::function<float(float)>> order_stat_funcs_;
  mutable std::vector<std::function<float(float)>> exp_value_funcs_;
  std::vector<Distribution> value_dists_;
  int n_players_;
  mutable bool pre_calculated_;
};

}  // namespace bidding

#endif  // _BIDDING_SECOND_PRICE_AUCTION_H_
