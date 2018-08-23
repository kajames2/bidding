#ifndef _BIDDING_ALL_PAY_AUCTION_H_
#define _BIDDING_ALL_PAY_AUCTION_H_

#include <boost/math/quadrature/gauss_kronrod.hpp>
#include "bidding/distribution.h"
#include "bidding/piecewise_linear_function.h"

namespace bidding {

class AllPayAuction {
 public:
  AllPayAuction(std::vector<float> values);
  float GetValue(float bid, float value) const;
  void AcceptStrategy(std::function<float(float)> cdf, int id);
  float GetFitness(const std::function<float(float)>& cdf, int id) const;

 private:
  float GetIntegrand(const std::function<float(float)>& cdf, int id,
                      float bid) const;
  std::vector<std::function<float(float)>> bid_cdf_funcs_;
  std::vector<std::function<float(float)>> bid_pdf_funcs_;
  std::vector<float> values_;
  int n_players_;
};

}  // namespace bidding

#endif  // _BIDDING_ALL_PAY_AUCTION_H_
