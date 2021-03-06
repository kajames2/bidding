#ifndef _BIDDING_FIRST_PRICE_AUCTION_H_
#define _BIDDING_FIRST_PRICE_AUCTION_H_

#include <boost/math/quadrature/gauss_kronrod.hpp>
#include <functional>
#include "bidding/distribution.h"
#include "bidding/piecewise_linear_function.h"

namespace bidding {

class FirstPriceAuction {
 public:
  FirstPriceAuction(std::vector<Distribution> value_dists);
  float GetValue(float value, float bid) const;
  void AcceptStrategy(std::function<float(float)> bid, int id);
  float GetFitness(const std::function<float(float)>& bid_func,
                    int id) const;

 private:
  float GetIntegrand(const std::function<float(float)>& bid_func, int id,
                      float value) const;
  std::vector<std::function<float(float)>> bid_funcs_;
  std::vector<std::function<float(float)>> bid_cdfs_;
  std::vector<Distribution> value_dists_;
  int n_players_;
};

}  // namespace bidding

#endif  // _BIDDING_FIRST_PRICE_AUCTION_H_
