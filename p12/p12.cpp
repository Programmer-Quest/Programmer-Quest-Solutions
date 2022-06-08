#include <iostream>
#include <vector>
#include <map>
#include <set>


struct Move {
  std::vector<std::string> sequence{};
  std::set<std::string> possibleCounters{};

  void pruneCounters() {
    if (sequence.size() > 1 && sequence[sequence.size() - 1] == sequence[sequence.size() - 2]) {
      possibleCounters.clear();
      possibleCounters.insert(sequence.back());
      return;
    }

    for (uint8_t i = 0; i < sequence.size() - 1; i++)
      possibleCounters.erase(sequence[i]);
  }

  void fillCounters(const std::map<std::string, Move>& moves) {
    for (auto& [moveId, _] : moves)
      possibleCounters.insert(moveId);
  }

  void eliminateCounter(const std::string& counter) {
    possibleCounters.erase(counter);
  }

  bool foundCounter() const {
    return possibleCounters.size() == 1;
  }

  const std::string& getCounter() const {
    return *possibleCounters.begin();
  }
};

class Moves {
private:
  friend std::istream& operator>>(std::istream& is, Moves& moves);

  std::map<std::string, Move> moves;

public:
  void analyze() {
    for (auto& [_, move] : moves) {
      move.fillCounters(moves);
      move.pruneCounters();
    }

    std::set<std::string> found;
    while (found.size() != moves.size()) {
      for (auto& [moveId1, move1] : moves) {
        if (move1.foundCounter() && !found.count(moveId1)) {
          found.insert(moveId1);
          for (auto& [moveId2, move2] : moves)
            if (moveId1 != moveId2)
              move2.eliminateCounter(move1.getCounter());
        }
      }
    }
  }

  std::string result() const {
    std::string result = "";
    for (const auto& [moveId, move] : moves)
      result += moveId + move.getCounter();
    return result;
  }
};

std::istream& operator>>(std::istream& is, Moves& moves) {
  std::string move, counter;
  auto& map = moves.moves;
  while (is >> move >> counter) {
    if (auto m = map.find(move); m == map.end()) {
      map[move] = {{counter}};
    } else {
      m->second.sequence.push_back(counter);
    }
  }
  return is;
}


int main() {
  Moves moves;
  std::cin >> moves;

  moves.analyze();
  std::cout << "Result = " << moves.result() << '\n';

  return 0;
}
