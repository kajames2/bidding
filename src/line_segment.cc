#include "bidding/line_segment.h"

#include <cstddef>

#include <boost/container_hash/hash.hpp>

#include "bidding/range.h"

namespace bidding {

LineSegment::LineSegment(Range xrange, Range yrange)
    : xrange_(xrange),
      yrange_(yrange),
      inv_interval_(1 / (xrange.max - xrange.min)) {}

double LineSegment::GetY(double x) const {
  double alpha = (x - xrange_.min) * inv_interval_;
  return alpha * yrange_.max + (1 - alpha) * yrange_.min;
}

bool operator==(const LineSegment& g1, const LineSegment& g2) {
  return g1.xrange_ == g2.xrange_ && g1.yrange_ == g2.yrange_;
}

std::size_t hash_value(const LineSegment& s) {
  std::size_t seed = 0;
  boost::hash_combine(seed, s.xrange_);
  boost::hash_combine(seed, s.yrange_);
  
  return seed;
}

}  // namespace bidding
