#include <iostream>
#include <vector>

using Point = std::pair<int, int>;

struct SpawnPoint {
  Point position; // The x,y position of the spawn point
  int interval; // The time interval between a boar spawning
  int spawnTime; // The timestamp of the next time a boar is spawning

  SpawnPoint(Point position, int interval) : position(position), interval(interval), spawnTime(interval) { }

  Point manhattan(const SpawnPoint& other) const {
    return {std::abs(position.first - other.position.first), std::abs(position.second - other.position.second)};
  }

  bool operator<(const SpawnPoint& other) const {
    return spawnTime < other.spawnTime;
  }
};

static Point totalDistanceTraveled(std::vector<SpawnPoint>& spawns, uint16_t count) {
  auto position = *std::min_element(spawns.begin(), spawns.end());
  Point distanceTravelled = {0, 0};

  for (uint16_t i = 0; i < count; i++) {
    auto& next = *std::min_element(spawns.begin(), spawns.end());
    auto distance = position.manhattan(next);
    distanceTravelled = {distanceTravelled.first + distance.first, distanceTravelled.second + distance.second};
    position = next;
    next.spawnTime += next.interval;
  }

  return distanceTravelled;
}

int main() {
  std::vector<SpawnPoint> spawns;
  int x, y, interval;
  char dummy;
  while (std::cin >> x >> dummy >> y >> dummy >> interval) {
    spawns.emplace_back(Point{x, y}, interval);
  }

  auto [dx, dy] = totalDistanceTraveled(spawns, 1000);
  std::cout << "Result = " << dx << ',' << dy << '\n';
  return 0;
}
