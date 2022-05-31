#include <iostream>

char decipherTapCode(uint8_t row, uint8_t col) {
  // Skip 'k'
  if (row >= 3) {
    col++;
    if (col > 5) {
      col = 1;
      row++;
    }
  }

  return 'a' + (row - 1) * 5 + col - 1;
}

std::string decipherTapCode(const std::string& cipher) {
  std::string result;

  for (size_t i = 0; i < cipher.size();) {
    if (cipher[i] == ' ') {
      result += ' ';
      i++;
    } else {
      result += decipherTapCode(cipher[i] - '0', cipher[i + 1] - '0');
      i += 2;
    }
  }

  return result;
}

int main() {
  std::string cipher = "442315 12151142 2443 443434 3534521542214531 4434 1215 24331311351113244411441514 1254 11 432433223115 44421135";
  std::cout << "Result = " << decipherTapCode(cipher) << '\n';
  return 0;
}
