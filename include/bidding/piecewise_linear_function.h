#ifndef _BIDDING_PIECEWISE_LINEAR_FUNCTION_
#define _BIDDING_PIECEWISE_LINEAR_FUNCTION_

#include <vector>

#include "bidding/line_segment.h"
#include "bidding/range.h"

namespace bidding {

class PiecewiseLinearFunction {
 public:
  PiecewiseLinearFunction() {}

  PiecewiseLinearFunction(std::vector<float> ys, Range range);
  LineSegment GetLine(double x) const;
  LineSegment GetLineCache(double x) const;
  PiecewiseLinearFunction GetInverseFunction() const;
  double GetBid(double x) const;
  friend std::size_t hash_value(const PiecewiseLinearFunction& s);
  friend bool operator==(const PiecewiseLinearFunction& g1,
                         const PiecewiseLinearFunction& g2);

 private:
  PiecewiseLinearFunction(std::vector<LineSegment> segments);
  std::vector<LineSegment> segments_;
  Range range_;
  mutable int cache_ind_ = 0;
};

bool operator==(const PiecewiseLinearFunction& g1,
                const PiecewiseLinearFunction& g2);
std::size_t hash_value(const PiecewiseLinearFunction& s);

}  // namespace bidding

#endif  // _BIDDING_PIECEWISE_LINEAR_FUNCTION_
