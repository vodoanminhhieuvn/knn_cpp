// utils.h
#include <algorithm>
#include <cstddef>
#include <random>
#include <vector>

template <typename T>
std::pair<std::vector<T>, std::vector<T>> split_data(const std::vector<T> &data,
                                                     double prob) {
  std::random_device rd;
  std::mt19937 g(rd());

  std::vector<T> shuffled_data = data;
  std::shuffle(shuffled_data.begin(), shuffled_data.end(), g);

  auto cut = static_cast<size_t>(data.size() * prob);

  std::vector<T> train(shuffled_data.begin(), shuffled_data.begin() + cut);
  std::vector<T> test(shuffled_data.begin() + cut, shuffled_data.end());

  return std::make_pair(train, test);
}

struct TupleHash {
  template <class T1, class T2>
  std::size_t operator()(const std::tuple<T1, T2> &p) const {
    auto hash1 = std::hash<T1>{}(std::get<0>(p));
    auto hash2 = std::hash<T2>{}(std::get<1>(p));
    return hash1 ^ hash2;
  }
};
