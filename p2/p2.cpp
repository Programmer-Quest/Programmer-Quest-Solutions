#include <iostream>

static void shift(std::string& cipher) {
  for (auto& c : cipher) {
    if (c == ' ')
      continue;
    c++;
    if (c == 'z' + 1)
      c = 'a';
  }
}

int main() {
  std::string cipher = "mubsecu je fhewhqccuh gkuij";
  for (uint8_t i = 0; i < 'z' - 'a'; i++) {
    shift(cipher);
    std::cout << cipher << '\n';
  }
  return 0;
}
