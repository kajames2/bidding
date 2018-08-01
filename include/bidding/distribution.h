#ifndef _BIDDING_DISTRIBUTION_H_
#define _BIDDING_DISTRIBUTION_H_

#include <boost/math/distributions.hpp>
#include <memory>

namespace bidding {

// Code adapted from Sean Parent's talk on runtime polymorphism.
// Is an example of type erasure intend to wrap boosts distributions so that I
// can put different distributions into a vector and use any combination of
// value distributions in auctions.
class Distribution {
 public:
  template <typename T>
  Distribution(T x) : self_(std::make_shared<model<T>>(std::move(x))) {}

  friend double cdf(const Distribution& dist, double x) {
    return dist.self_->cdf_(x);
  }
  friend double pdf(const Distribution& dist, double x) {
    return dist.self_->pdf_(x);
  }
  friend double lower(const Distribution& dist) { return dist.self_->lower_(); }
  friend double upper(const Distribution& dist) { return dist.self_->upper_(); }

 private:
  struct DistributionConcept {
    virtual ~DistributionConcept() = default;
    virtual double cdf_(double x) const = 0;
    virtual double pdf_(double x) const = 0;
    virtual double lower_() const = 0;
    virtual double upper_() const = 0;
  };
  template <typename T>
  struct model final : DistributionConcept {
    model(T x) : dist_(std::move(x)) {}
    double cdf_(double x) const override { return boost::math::cdf(dist_, x); }
    double pdf_(double x) const override { return boost::math::pdf(dist_, x); }
    double lower_() const override {
      return boost::math::quantile(dist_, 0.000001);
    }
    double upper_() const override {
      return boost::math::quantile(dist_, 0.999999);
    }
    T dist_;
  };

  std::shared_ptr<const DistributionConcept> self_;
};

}  // namespace bidding

#endif  // _BIDDING_DISTRIBUTION_H_
