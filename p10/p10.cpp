#include <iostream>
#include <vector>
#include <list>
#include <array>

struct Tile {
  char c;
  bool visited = false;
};

struct Pos {
  int row, col;

  Pos operator+(const Pos& other) const {
    return Pos{row + other.row, col + other.col};
  }
};

class Grid {
private:
  inline static constexpr std::array<Pos, 4> OFFSETS = {Pos{-1, 0}, Pos{1, 0}, Pos{0, -1}, Pos{0, 1}};

  std::vector<std::vector<Tile>> grid;

  bool inside(const Pos& p) const {
    return p.row >= 0 && static_cast<size_t>(p.row) < grid.size() && p.col >= 0 && static_cast<size_t>(p.col) < grid[p.row].size();
  }

  Tile& get(const Pos& p) {
    return grid[p.row][p.col];
  }

public:
  void read() {
    std::string line;
    while (std::getline(std::cin, line)) {
      grid.push_back(std::vector<Tile>{});
      for (char c : line)
        grid.back().emplace_back(c);
    }
  }

  auto reachableTraps() {
    unsigned count = 0;

    std::list<Pos> list;
    list.emplace_back(0, 0);
    grid[0][0].visited = true;

    while (!list.empty()) {
      auto p = list.front();
      list.pop_front();

      if (get(p).c == 'O')
        count++;

      for (const Pos& offset : OFFSETS)
        if (auto neighbor = p + offset; inside(neighbor) && get(neighbor).c != 'T' && !get(neighbor).visited) {
          list.push_back(neighbor);
          get(neighbor).visited = true;
        }
    }

    return count;
  }
};

int main() {
  Grid grid;

  grid.read();
  std::cout << "Result = " << grid.reachableTraps() << '\n';
  
  return 0;
}
