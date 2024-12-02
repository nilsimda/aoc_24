#include <fstream>
#include <iostream>
#include <unordered_map>

int main(int argc, char **argv) {
  std::ifstream f("input.txt");

  std::string line;
  std::vector<int> vec1;
  std::unordered_map<int, int> lookup;

  while (std::getline(f, line)) {
    size_t idx = line.find(' ');
    vec1.push_back(std::stoi(line.substr(0, idx)));
    int n1 = std::stoi(line.substr(idx + 1, line.size()));
    if (lookup.find(n1) == lookup.end()) {
      lookup[n1] = 1;
    } else {
      lookup[n1] += 1;
    }
  }

  int acc = 0;
  for (size_t i = 0; i < vec1.size(); i++) {
    if (lookup.find(vec1[i]) != lookup.end()) {
      acc += vec1[i] * lookup[vec1[i]];
    }
  }
  std::cout << acc << std::endl;
  return 0;
}
