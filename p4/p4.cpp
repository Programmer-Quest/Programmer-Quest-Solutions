#include <iostream>
#include <vector>
#include <array>

template <uint8_t n>
uint64_t shoppingSpree(const std::vector<uint8_t>& items) {
  std::array<uint64_t, n + 1> counts{0};

  for (auto item : items)
    counts[item]++;

  for (uint8_t i = 0; i <= n; i++) {
    for (auto item : items)
      if (i >= item)
        counts[i] += counts[i - item];
  }
  
  return counts[n];
}

int main() {
  std::vector<uint8_t> items{1, 3, 15, 23};
  std::cout << "Result = " << shoppingSpree<100>(items) << '\n';
  return 0;
}
