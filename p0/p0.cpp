#include <iostream>
#include <set>
#include <tuple>

using Color = std::tuple<int, int, int>;

int main() {
  std::set<Color> colors;
  std::string color;
  int c, r, g, b;
  char dummy;
  while ((c = std::cin.peek()) != EOF) {
    if (c == '#') {
      std::getline(std::cin, color);
      r = std::stoi(color.substr(1, 2), nullptr, 16);
      g = std::stoi(color.substr(3, 2), nullptr, 16);
      b = std::stoi(color.substr(5, 2), nullptr, 16);
    } else {
      std::cin >> r >> dummy >> g >> dummy >> b;
      std::cin.ignore(1);
    }
    colors.emplace(r, g, b);
  }
  std::cout << "Result = " << colors.size() << '\n';
  return 0;
}
