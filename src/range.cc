#include "bidding/range.h"

#include <cstddef>

#include <boost/container_hash/hash.hpp>

namespace bidding {

bool InRange(Range range, double val) {
  return val >= range.min && val < range.max;
}

bool operator==(const Range& g1, const Range& g2) {
  return g1.min == g2.min && g1.max == g2.max;
}

std::size_t hash_value(const Range& s) {
  std::size_t seed = 0;
  boost::hash_combine(seed, s.min);
  boost::hash_combine(seed, s.max);

  return seed;
}

}  // namespace bidding
