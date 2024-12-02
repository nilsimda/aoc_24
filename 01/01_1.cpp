#include <algorithm>
#include <fstream>
#include <iostream>

int main(int argc, char **argv) {
  std::ifstream f("input.txt");

  std::string line;
  std::vector<int> vec1;
  std::vector<int> vec2;

  while (std::getline(f, line)) {
    size_t idx = line.find(' ');
    vec1.push_back(std::stoi(line.substr(0, idx)));
    vec2.push_back(std::stoi(line.substr(idx + 1, line.size())));
  }

  std::sort(vec1.begin(), vec1.end());
  std::sort(vec2.begin(), vec2.end());

  int acc = 0;
  for (size_t i = 0; i < vec1.size() && i < vec2.size(); i++) {
    acc += std::abs(vec1[i] - vec2[i]);
  }
  std::cout << acc << std::endl;
  return 0;
}
