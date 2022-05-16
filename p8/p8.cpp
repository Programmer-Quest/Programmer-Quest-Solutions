#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <map>
#include <array>

struct Node;

using Pos = std::pair<int, int>;
using Nodes = std::map<Pos, Node>;
using Id = uint8_t;

static constexpr uint8_t INVALID_COST = 10;

struct Edge {
  uint8_t cost = INVALID_COST;
  Node* node = nullptr;
};

struct Node {
  Id id;
  uint8_t bestCost = 10;
  std::vector<Edge> edges;

  Node() = default;

  Node(Id id) : id(id) {}

  bool operator<(const Node& other) const {
    return bestCost >= other.bestCost;
  }
};

class Grid {
private:
  std::vector<std::vector<char>> grid;

  char get(const Pos& pos) const {
    return grid[pos.first][pos.second];
  }

  bool isInside(const Pos& pos) const {
    auto [row, col] = pos;
    return row >= 0 && static_cast<size_t>(row) < grid.size() && col >= 0 && static_cast<size_t>(col) < grid[row].size();
  }

  auto findNeighbors(const Pos& pos) const {
    std::vector<Pos> neighbors;

    for (const auto& [offsetRow, offsetCol] : std::array<Pos, 4>{Pos{1, 0}, Pos{-1, 0}, Pos{0, 1}, Pos{0, -1}})
      if (auto neighbor = Pos{pos.first + offsetRow, pos.second + offsetCol}; isInside(neighbor))
        neighbors.push_back(neighbor);

    return neighbors;
  }

  auto findEdge(Nodes& nodes, Pos pos, Pos prev) const {
    uint8_t cost = 0;

    for (char c; (c = get(pos)) != 'x';) {
      if (c >= '1' && c <= '9')
        cost = c - '0';
      for (const auto& neighbor : findNeighbors(pos)) {
        if (get(neighbor) != ' ' && neighbor != prev) {
          prev = pos;
          pos = neighbor;
          break;
        }
      }
    }

    return Edge{cost, &nodes[pos]};
  }

public:
  void parse() {
    std::string row;
    while (std::getline(std::cin, row)) {
      grid.push_back(std::vector<char>{});
      for (char c : row)
        grid.back().push_back(c);
    }
  }

  auto buildGraph() const {
    Nodes nodes;

    for (size_t row = 0; row < grid.size(); row++) {
      for (size_t col = 0; col < grid[row].size(); col++) {
        if (grid[row][col] == 'x') {
          nodes[{row, col}] = Node(nodes.size());
        }
      }
    }

    for (auto& [pos, node] : nodes) {
      for (const auto& neighbor : findNeighbors(pos)) {
        if (get(neighbor) == ' ')
          continue;
        node.edges.push_back(findEdge(nodes, neighbor, pos));
      }
    }

    return nodes;
  }
};

auto minimumSpanningTree(Nodes& nodes) {
  std::priority_queue<Node> queue;
  std::set<Id> tree;
  uint16_t result = 0;

  for (auto& [_, node] : nodes)
    queue.push(node);

  while (tree.size() != nodes.size()) {
    Node top;
    do {
      top = queue.top();
      queue.pop();
    } while (tree.count(top.id));

    tree.insert(top.id);
    if (top.bestCost != INVALID_COST)
      result += top.bestCost;

    for (auto [cost, node] : top.edges) {
      if (!tree.count(node->id) && cost < node->bestCost) {
        node->bestCost = cost;
        queue.push(*node);
      }
    }
  }

  return result;
}


int main() {
  Grid grid;
  grid.parse();
  Nodes nodes = grid.buildGraph();
  std::cout << "Result = " << minimumSpanningTree(nodes) << '\n';

  return 0;
}
