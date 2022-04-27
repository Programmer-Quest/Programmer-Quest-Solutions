#include <iostream>

uint16_t fibonacci(uint64_t start, uint64_t fishes) {
  uint64_t a = 1;
  uint64_t b = 1;
  uint64_t sum = start;
  uint16_t count = 0;

  for (count = 0; sum < fishes; count++) {
    sum += a;
    uint64_t c = a + b;
    a = b;
    b = c;
  }

  return count;
}

int main() {
  std::cout << "Result = " << fibonacci(20, 1'000'000'000'000'000'000ull) << '\n';
  return 0;
}
