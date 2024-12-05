#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <unordered_map>
#include <unordered_set>

using namespace std;

int main(int argc, char **argv) {
    unordered_map<int, unordered_set<int>> rules;
    freopen(argv[1], "r", stdin);
    int a, b;
    char c;
    while (cin >> a >> c >> b) { rules[a].insert(b); }
    ifstream f(argv[2]);
    string line;
    vector<vector<int>> output;
    while (getline(f, line)) {
        vector<int> nums;
        stringstream ss(line);
        string num;
        while (getline(ss, num, ',')) { nums.push_back(stoi(num)); }
        output.push_back(nums);
    }

    unsigned part1 = 0;
    unsigned part2 = 0;
    auto comp = [&rules](int a, int b) { return rules[a].contains(b); };
    for (auto v : output) {
        if (is_sorted(v.begin(), v.end(), comp)) {
            part1 += v[(v.size() - 1) / 2];
        } else {
            sort(v.begin(), v.end(), comp);
            part2 += v[(v.size() - 1) / 2];
        }
    }

    cout << part1 << endl;
    cout << part2 << endl;

    return 0;
}