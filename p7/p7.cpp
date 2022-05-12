#include <iostream>
#include <vector>

struct Item {
  unsigned damage;
  unsigned value;
  bool operator<(const Item& other) const {
    return damage / static_cast<double>(value) < other.damage / static_cast<double>(other.value);
  }
};

static unsigned pickItems(const std::vector<Item>& items, unsigned maxValue) {
  std::vector<std::vector<unsigned>> values(items.size() + 1, std::vector<unsigned>(maxValue + 1, 0));

  for (unsigned i = 0; i < items.size(); i++) {
    for (unsigned v = 0; v <= maxValue; v++) {
      auto [damage, value] = items[i];
      values[i + 1][v] = value > v ? values[i][v] : std::max(values[i][v], values[i][v - value] + damage);
    }
  }

  return values[items.size()][maxValue];
}

int main() {
  std::string dummy;
  uint16_t damage, value;
  std::vector<Item> items;
  while (std::cin >> dummy >> dummy >> dummy >> dummy >> damage >> dummy >> dummy >> value) {
    items.emplace_back(damage, value);
  }
  std::cout << "Result = " << +pickItems(items, 200) << '\n';
  return 0;
}
