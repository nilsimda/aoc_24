#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int count_line(string line) {
    unsigned occurrences = 0;
    size_t pos = 0;
    while ((pos = line.find("XMAS", pos)) != string::npos) {
        occurrences++;
        pos += 4;
    }
    reverse(line.begin(), line.end());
    pos = 0;
    while ((pos = line.find("XMAS", pos)) != string::npos) {
        occurrences++;
        pos += 4;
    }
    return occurrences;
}

int part1(vector<vector<char>> puzzle) {
    unsigned res = 0;
    const unsigned n_rows = puzzle.size();
    const unsigned n_cols = puzzle[0].size();
    // horizontal
    for (size_t i = 0; i < n_rows; ++i) {
        string horizontal = string(puzzle[i].begin(), puzzle[i].end());
        res += count_line(horizontal);
    }

    // vertical
    for (size_t i = 0; i < n_cols; ++i) {
        string line(n_rows, ' ');
        for (size_t j = 0; j < n_rows; ++j) { line[j] = puzzle[j][i]; }
        res += count_line(line);
    }

    int col_idx;
    int row_idx;

    // diag forwards
    for (size_t i = 0; i < n_cols; ++i) {
        string line(n_cols, ' ');
        col_idx = 0;
        row_idx = 0;
        while (col_idx + i < n_cols && row_idx < n_rows) {
            line[row_idx] = puzzle[row_idx][i + col_idx];
            row_idx++;
            col_idx++;
        }
        res += count_line(line);
    }

    for (size_t i = 0; i < n_rows; ++i) {
        string line(n_rows, ' ');
        col_idx = 0;
        row_idx = 1;
        while (col_idx < n_cols && row_idx + i < n_rows) {
            line[row_idx] = puzzle[row_idx + i][col_idx];
            row_idx++;
            col_idx++;
        }
        res += count_line(line);
    }

    //diag backwards
    for (int i = 0; i < n_rows; i++) {
        string line(n_rows, ' ');
        col_idx = 0;
        row_idx = static_cast<signed>(n_rows - 1);
        while (col_idx < n_cols && row_idx - i >= 0) {
            line[row_idx] = puzzle[row_idx - i][col_idx];
            row_idx--;
            col_idx++;
        }
        res += count_line(line);
    }

    for (size_t i = 0; i < n_rows; i++) {
        string line(n_rows, ' ');
        col_idx = 1;
        row_idx = n_rows - 1;
        while (col_idx + i < n_cols && row_idx >= 0) {
            line[row_idx] = puzzle[row_idx][col_idx + i];
            row_idx--;
            col_idx++;
        }
        res += count_line(line);
    }

    return res;
}

bool is_xmas(string s1, string s2) { return (s1 == "MAS" || s1 == "SAM") && (s2 == "MAS" || s2 == "SAM"); }

int part2(vector<vector<char>> puzzle) {
    unsigned res = 0;
    for (int i = 0; i < puzzle.size() - 2; ++i) {
        for (int j = 0; j < puzzle[0].size() - 2; ++j) {
            vector<char> dia1(3, ' ');
            vector<char> dia2(3, ' ');
            for (int k = 0; k < 3; ++k) {
                dia1[k] = puzzle[i + k][j + k];
                dia2[k] = puzzle[i + 2 - k][j + k];
            }
            string s1(dia1.begin(), dia1.end());
            string s2(dia2.begin(), dia2.end());
            res += is_xmas(s1, s2);
        }
    }
    return res;
}
int main(int argc, char **argv) {
    ifstream f(argv[1]);
    vector<vector<char>> puzzle;
    string line;
    while (getline(f, line)) {
        vector<char> d(line.begin(), line.end());
        puzzle.push_back(d);
    }
    cout << part1(puzzle) << endl;
    cout << part2(puzzle) << endl;
    return 0;
}
