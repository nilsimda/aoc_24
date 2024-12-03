#include <fstream>
#include <iostream>
#include <regex>
#include <sstream>

using namespace std;

int process_string(string str) {
  int res = 0;
  regex mul_regex("mul\\(([0-9]+),([0-9]+)\\)");
  sregex_iterator begin = sregex_iterator(str.begin(), str.end(), mul_regex);
  sregex_iterator end = sregex_iterator();
  for (sregex_iterator i = begin; i != end; ++i) {
    smatch match = *i;
    res += stoi(match[1]) * stoi(match[2]);
  }
  return res;
}

int part1(string program) { return process_string(program); }

int part2(string program) {
  int res = 0;
  bool enabled = true;
  size_t start_pos = 0;
  size_t end_pos = 0;
  while (end_pos != string::npos) {
    string pattern = enabled ? "don't()" : "do()";
    end_pos = program.find(pattern, start_pos);
    if (enabled) {
      res += process_string(program.substr(start_pos, end_pos - start_pos));
    }
    start_pos = end_pos + pattern.size();
    enabled = !enabled;
  }
  return res;
}

int main(int argc, char **argv) {
  ifstream f(argv[1]);
  stringstream program;
  program << f.rdbuf();
  cout << "Part 1: " << part1(program.str()) << endl;
  cout << "Part 2: " << part2(program.str()) << endl;
  return 0;
}