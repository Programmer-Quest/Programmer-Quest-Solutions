#include <iostream>
#include <cctype>

static auto isValidName(const std::string& name) {
  if (std::islower(static_cast<unsigned char>(name.front())))
    return false;

  if (name.find(' ') != std::string::npos)
    return false;

  for (uint8_t i = 0; i < name.size() - 2; i++)
    if (name[i] == name[i + 1] && name[i] == name[i + 2])
      return false;

  return true;
}

int main() {
  std::string name;
  uint16_t validCount = 0;
  while (std::getline(std::cin, name))
    validCount += isValidName(name);
  
  std::cout << "Result = " << validCount << '\n';
  return 0;
}
