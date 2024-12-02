#include <fstream>
#include <iostream>
#include <sstream>
#include <unordered_set>

int main(int argc, char **argv) {
  std::ifstream f(argv[1]);

  std::string line;
  std::unordered_set<int> allowed_diffs = {1, 2, 3};
  unsigned res = 0;
  while (std::getline(f, line)) {
    std::istringstream iss(line);
    std::vector<int> vec;
    int number;
    while (iss >> number) {
      vec.push_back(number);
    }
    bool inc = vec[0] < vec[1];
    bool safe = true;
    for (size_t i = 0; i < vec.size() - 1; ++i) {
      if (vec[i] < vec[i + 1] != inc ||
          !allowed_diffs.contains(std::abs(vec[i] - vec[i + 1]))) {
        safe = false;
        break;
      }
    }
    res += safe;
  }
  std::cout << res << std::endl;
  return 0;
}