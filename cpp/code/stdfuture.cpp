#include <algorithm>
#include <future>
#include <iostream>
#include <random>
#include <unordered_set>

std::unordered_set<int> make_sorted_random(const std::size_t num_elems) {
  std::unordered_set<int> ret{};
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dis(0, num_elems - 1);
  std::generate_n(std::inserter(ret, ret.end()), num_elems,
                  [&]() { return dis(gen); });
  return ret;
}

int main() {
  // this takes around 0.7s
  //   std::cout << make_sorted_random(1000000).size() << ' '
  // << make_sorted_random(1000000).size() << '\n';

  // this also takes around 0.7s
  //   std::cout << std::async(make_sorted_random, 1000000).get().size() << ' '
  // << std::async(make_sorted_random, 1000000).get().size() << '\n';

  // this takes 0.4s
  // https://en.cppreference.com/w/cpp/thread/async: f might be executed in
  // another thread or it might be run synchronously when the resulting
  // std::future is queried for a value
  auto f1 = std::async(std::launch::async, make_sorted_random, 1000000);
  auto f2 = std::async(std::launch::async, make_sorted_random, 1000000);
  std::cout << f1.get().size() << ' ' << f2.get().size() << '\n';

  return 0;
}
