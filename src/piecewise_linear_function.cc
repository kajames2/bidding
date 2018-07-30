#include "bidding/piecewise_linear_function.h"

#include <boost/container_hash/hash.hpp>
#include <cstddef>

#include "bidding/line_segment.h"
#include "bidding/range.h"

namespace bidding {

PiecewiseLinearFunction::PiecewiseLinearFunction(std::vector<float> ys,
                                                 Range range)
    : range_(range) {
  int n_lines = ys.size() - 1;
  double interval_size = (range.max - range.min) / n_lines;
  std::vector<double> xs;
  xs.reserve(n_lines + 1);
  for (int i = 0; i <= n_lines; ++i) {
    xs.emplace_back(i * interval_size + range.min);
  }
  segments_.reserve(n_lines);
  for (int i = 0; i < n_lines; ++i) {
    segments_.emplace_back(Range{xs[i], xs[i + 1]}, Range{ys[i], ys[i + 1]});
  }
}

LineSegment PiecewiseLinearFunction::GetLine(double x) const {
  return *std::find_if(
      segments_.begin(), segments_.end(),
      [x](const LineSegment& line) { return line.IsInRange(x); });
}

LineSegment PiecewiseLinearFunction::GetLineCache(double x) const {
  if (segments_[cache_ind_].IsInRange(x)) {
    return segments_[cache_ind_];
  } else {
    auto el = std::find_if(
        segments_.begin(), segments_.end(),
        [x](const LineSegment& line) { return line.IsInRange(x); });
    cache_ind_ = std::distance(segments_.begin(), el);
    return *el;
  }
}

PiecewiseLinearFunction PiecewiseLinearFunction::GetInverseFunction() const {
  std::vector<LineSegment> inv_segments;
  inv_segments.reserve(segments_.size());
  for (const auto segment : segments_) {
    inv_segments.emplace_back(segment.GetInverseLineSegment());
  }
  return PiecewiseLinearFunction(inv_segments);
}

double PiecewiseLinearFunction::GetBid(double x) const {
  if (x <= range_.min) {
    return segments_[0].GetMin();
  } else if (x >= range_.max) {
    return segments_[segments_.size() - 1].GetMax();
  }
  auto line = GetLineCache(x);
  return line.GetY(x);
}
PiecewiseLinearFunction::PiecewiseLinearFunction(
    std::vector<LineSegment> segments)
    : segments_(segments) {
  double min =
      std::min_element(segments.begin(), segments.end(),
                       [](const LineSegment& l1, const LineSegment& l2) {
                         return l1.GetRange().min < l2.GetRange().min;
                       })
          ->GetRange()
          .min;
  double max =
      std::max_element(segments.begin(), segments.end(),
                       [](const LineSegment& l1, const LineSegment& l2) {
                         return l1.GetRange().max < l2.GetRange().max;
                       })
          ->GetRange()
          .max;
  range_ = Range{min, max};
}

bool operator==(const PiecewiseLinearFunction& g1,
                const PiecewiseLinearFunction& g2) {
  return g1.segments_ == g2.segments_;
}

std::size_t hash_value(const PiecewiseLinearFunction& s) {
  boost::hash<std::vector<LineSegment>> hasher;
  return hasher(s.segments_);
}

}  // namespace bidding
