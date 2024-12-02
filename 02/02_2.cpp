#include <fstream>
#include <iostream>
#include <sstream>
#include <unordered_set>
#include <vector>

bool is_unsafe(int idx1, int idx2, bool inc) {
  std::unordered_set<int> allowed_diffs = {1, 2, 3};
  return (idx1 < idx2 != inc || !allowed_diffs.contains(std::abs(idx1 - idx2)));
}

int check_safety(std::vector<int> vec) {
  for (size_t i = 0; i < vec.size() - 1; ++i) {
    if (is_unsafe(vec[i], vec[i + 1], vec[0] < vec[1]))
      return i;
  }
  return -1;
}

std::vector<int> remove_idx(std::vector<int> vec, int idx) {
  idx = idx < 0 ? 0 : idx;
  std::vector<int> res;
  for (int i = 0; i < vec.size(); ++i) {
    if (i != idx)
      res.push_back(vec[i]);
  }
  return res;
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
    bool safe = true;
    for (size_t idx = 0; idx < vec.size() - 1; idx++) {
      if (is_unsafe(vec[idx], vec[idx + 1], vec[0] < vec[1])) {
        std::vector<int> low = remove_idx(vec, idx - 1);
        std::vector<int> mid = remove_idx(vec, idx);
        std::vector<int> high = remove_idx(vec, idx + 1);
        safe = check_safety(low) == -1 || check_safety(mid) == -1 ||
               check_safety(high) == -1;
        break;
      }
    }
    res += safe;
  }
  std::cout << res << std::endl;
  return 0;
}