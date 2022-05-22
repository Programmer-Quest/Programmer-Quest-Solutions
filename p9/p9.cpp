#include <iostream>
#include <map>
#include <vector>

struct Pos {
  int x, y;

  auto operator<=>(const Pos& other) const = default;

  Pos& operator+=(const Pos& other) {
    x += other.x;
    y += other.y;
    return *this;
  }

  Pos operator-(const Pos& other) const {
    return Pos{x - other.x, y - other.y};
  }

  Pos signum() const {
    auto signum = [](int value) {
      return value < -1 ? -1 : (value > 1 ? 1 : 0);
    };
    return Pos{signum(x), signum(y)};
  }

  std::vector<Pos> createPath(const Pos& other) const {
    std::vector<Pos> path;

    auto pos = *this;
    auto direction = (other - pos).signum();
    while (pos != other) {
      path.push_back(pos);
      pos += direction;
    }
    path.push_back(other);

    return path;
  }
};

std::ostream& operator<<(std::ostream& os, const Pos& pos) {
  os << pos.x << ',' << pos.y;
  return os;
}

int main() {
  std::map<Pos, uint16_t> positions;
  Pos start, end;
  char dummy;

  while (std::cin >> dummy >> start.x >> dummy >> start.y >> dummy >> dummy >> dummy >> end.x >> dummy >> end.y >> dummy)
    for (auto& p : start.createPath(end))
      positions[p]++;

  std::cout << "Result = " << std::max_element(positions.begin(), positions.end(), [](const auto& e1, const auto& e2) { return e1.second < e2.second; })->first << '\n';

  return 0;
}
