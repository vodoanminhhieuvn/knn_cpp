// linear_algebra.h
#include <cassert>
#include <vector>

typedef std::vector<double> Vector;

namespace linear_algebra {

inline Vector subtract(const Vector &v, const Vector &w) {
  assert(v.size() == w.size() && "vectors must be the same length");
  Vector result(v.size());
  for (size_t i = 0; i < v.size(); ++i) {
    result[i] = v[i] - w[i];
  }
  return result;
}

inline double dot(const Vector &v, const Vector &w) {
  assert(v.size() == w.size() && "vectors must be the same length");
  double result = 0.0;
  for (size_t i = 0; i < v.size(); ++i) {
    result += v[i] * w[i];
  }
  return result;
}

inline double sum_of_squares(const Vector &v) { return dot(v, v); }

inline double magnitude(const Vector &v) { return sqrt(sum_of_squares(v)); }

inline double distance(const Vector &v, const Vector &w) {
  return magnitude(subtract(v, w));
}

} // namespace linear_algebra
