// k_nearest_neighbors.h
#include "linear_algebra.h"
#include <algorithm>
#include <cstdlib>
#include <string>
#include <unordered_map>
#include <vector>

struct LabelPoint {
  Vector point;
  std::string label;
};

namespace knn {

template <typename T> T majority_vote(const std::vector<T> &labels) {
  std::unordered_map<T, size_t> vote_counts;
  for (const T &label : labels) {
    vote_counts[label]++;
  }

  auto max_vote = std::max_element(
      vote_counts.begin(), vote_counts.end(),
      [](const auto &a, const auto &b) { return a.second < b.second; });

  size_t winner_count = max_vote->second;
  size_t num_winners = std::count_if(vote_counts.begin(), vote_counts.end(),
                                     [winner_count](const auto &entry) {
                                       return entry.second == winner_count;
                                     });

  if (num_winners == 1) {
    return max_vote->first;
  } else {
    return majority_vote(std::vector<T>(labels.begin(), labels.end() - 1));
  }
}

inline std::string knn_classify(int k,
                                const std::vector<LabelPoint> &labeled_points,
                                const Vector &new_point) {
  auto by_distance = labeled_points;
  std::sort(by_distance.begin(), by_distance.end(),
            [new_point](const auto &lp1, const auto &lp2) {
              return linear_algebra::distance(lp1.point, new_point) <
                     linear_algebra::distance(lp2.point, new_point);
            });

  std::vector<std::string> k_nearest_labels;
  k_nearest_labels.reserve(k);
  for (int i = 0; i < k; ++i) {
    k_nearest_labels.push_back(by_distance[i].label);
  }

  return majority_vote(k_nearest_labels);
}

} // namespace knn
