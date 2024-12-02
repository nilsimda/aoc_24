#include <fstream>
#include <iostream>
#include <sstream>
#include <unordered_set>
#include <vector>

bool is_unsafe(int idx1, int idx2, bool inc) {
  std::unordered_set<int> allowed_diffs = {1, 2, 3};
  return (idx1 < idx2 != inc || !allowed_diffs.contains(std::abs(idx1 - idx2)));
}

bool check_safety(std::vector<int> vec) {
  for (size_t i = 0; i < vec.size() - 1; ++i) {
    if (is_unsafe(vec[i], vec[i + 1], vec[0] < vec[1]))
      return false;
  }
  return true;
}

int main(int argc, char **argv) {
  std::ifstream f(argv[1]);

  std::string line;
  unsigned res = 0;
  while (std::getline(f, line)) {
    std::istringstream iss(line);
    std::vector<int> vec;
    int number;
    while (iss >> number) {
      vec.push_back(number);
    }
    res += check_safety(vec);
  }
  std::cout << res << std::endl;
  return 0;
}