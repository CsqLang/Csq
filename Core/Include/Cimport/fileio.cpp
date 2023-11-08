#include <Csq/Core/Runtime/memory.h>
#include <Csq/Core/Runtime/core.h>
#include <bits/stdc++.h>
// Function to read the contents of a text file
auto readFile=[&](Cell filename) {
    std::ifstream file(*(filename.stringVal));
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file: " + *(filename.stringVal));
    }

    std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    file.close();

    return Cell(content);
};

auto writeFile=[&](Cell filename, Cell content) {
    std::ofstream file(*(filename.stringVal));
    if (!file.is_open()) {
        throw std::runtime_error("Failed to create or open file: " + *(filename.stringVal));
    }

    file << *(content.stringVal);
    file.close();
};
// Function to read lines from a text file into a vector of strings
auto readLines=[&](Cell filename) {
    Cell lines;
    vector<Cell> lines_;
    std::ifstream file(*(filename.stringVal));
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file: " + *(filename.stringVal));
    }

    std::string line;
    while (std::getline(file, line)) {
        lines_.push_back(Cell(line));
    }
    lines.vectorVal = new vector<Cell>(lines_);
    file.close();

    return lines;
};