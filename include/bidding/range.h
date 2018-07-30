#ifndef _BIDDING_RANGE_H_
#define _BIDDING_RANGE_H_

#include <cstddef>

namespace bidding {

struct Range {
  double min;
  double max;
};

bool InRange(Range range, double val);
bool operator==(const Range& g1, const Range& g2);
std::size_t hash_value(const Range& s);

}  // namespace bidding

#endif  // _BIDDING_RANGE_H_
