#include <iostream>
#include <set>
#include <map>

using Input = std::pair<std::string, std::string>;
using Rules = std::map<Input, std::string>;

static std::string fullCycle(const Rules& rules, uint8_t totalFish) {
  for (const auto& [input, output] : rules) {
    auto current = input;
    std::set<std::string> fishes;
    std::set<Input> inputs;
    while (!inputs.count(current)) {
      auto next = rules.at(current);
      fishes.insert(next);
      inputs.insert(current);
      current = {current.second, next};
    }
    if (const auto& [in1, in2] = input; fishes.size() == totalFish)
      return in1 + ',' + in2;
  }

  return "";
}

int main() {
  std::string input, output, dummy;
  Rules rules;
  std::set<std::string> fishes;

  while (std::cin >> input >> dummy >> output) {
    auto delim = input.find(',');
    rules[{input.substr(0, delim), input.substr(delim + 1)}] = output;
    fishes.insert(output);
  }

  std::cout << "Result = " << fullCycle(rules, fishes.size()) << '\n';
  return 0;
}
