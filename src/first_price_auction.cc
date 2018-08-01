#include "bidding/first_price_auction.h"

#include <boost/math/distributions/uniform.hpp>
#include <boost/math/quadrature/gauss_kronrod.hpp>

using namespace boost::math;
namespace bidding {

FirstPriceAuction::FirstPriceAuction(
    std::vector<Distribution> value_dists)
    : bid_funcs_(value_dists.size()),
      inv_bid_funcs_(value_dists.size()),
      value_dists_(value_dists),
      n_players_(value_dists.size()) {}
double FirstPriceAuction::GetValue(double bid, double value) const {
  return value - bid;
}
void FirstPriceAuction::AcceptStrategy(PiecewiseLinearFunction bid, int id) {
  bid_funcs_[id] = bid;
  inv_bid_funcs_[id] = bid.GetInverseFunction();
}
double FirstPriceAuction::GetFitness(const PiecewiseLinearFunction& bid_func,
                                     int id) const {
  return quadrature::gauss_kronrod<double, 61>::integrate(
      [this, bid_func, id](double value) {
        return GetIntegrand(bid_func, id, value);
      },
      lower(value_dists_[id]), upper(value_dists_[id]), 0, 0);
}

double FirstPriceAuction::GetIntegrand(const PiecewiseLinearFunction& bid_func,
                                       int id, double value) const {
  double bid = bid_func.GetBid(value);
  double integrand = GetValue(bid, value);
  integrand *= pdf(value_dists_[id], value);
  for (int j = 0; j < n_players_; ++j) {
    if (j != id) {
      integrand *= cdf(value_dists_[j], inv_bid_funcs_[j].GetBid(bid));
    }
  }
  return integrand;
}

}  // namespace bidding
