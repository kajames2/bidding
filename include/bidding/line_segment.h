#ifndef _BIDDING_LINE_SEGMENT_H_
#define _BIDDING_LINE_SEGMENT_H_

#include <cstddef>

#include "bidding/range.h"

namespace bidding {

class LineSegment {
 public:
  LineSegment(Range xrange, Range yrange);
  double GetY(double x) const;
  Range GetRange() const { return xrange_; }
  double GetMin() const { return yrange_.min; }
  double GetMax() const { return yrange_.max; }
  LineSegment GetInverseLineSegment() const {
    return LineSegment(yrange_, xrange_);
  }
  bool IsInRange(double x) const { return InRange(xrange_, x); }
  friend std::size_t hash_value(const LineSegment& s);
  friend bool operator==(const LineSegment& g1, const LineSegment& g2);

 private:
  Range xrange_;
  Range yrange_;
  double inv_interval_;
};

bool operator==(const LineSegment& g1, const LineSegment& g2);
std::size_t hash_value(const LineSegment& s);

}  // namespace bidding

#endif  // _BIDDING_LINE_SEGMENT_H_
