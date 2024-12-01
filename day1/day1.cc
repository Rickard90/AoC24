#include <iostream>
#include <vector>
#include <map>
#include <sstream>
#include <algorithm>


int main() {
    int sum {};
    std::string line;
    std::vector<int> lv, rv;
    std::map<int, int> rm;
    while (std::getline(std::cin, line)) {
        std::stringstream ss {line};
        int a {};
        ss >> a;
        int b {};
        ss >> b;
        lv.push_back(a);
        rv.push_back(b);
    }
    std::sort(lv.begin(), lv.end());
    std::sort(rv.begin(), rv.end());
    for (int i = 0; i < rv.size(); i++) {
        sum += std::abs( lv[i] - rv[i] );
    }
    std::cout << "Part1: " << sum << std::endl;

    sum = 0;
    for (int a : rv) {
        rm[a]++;
    }
    for (int a : lv) {
        sum += a * rm[a];
    }
    std::cout << "Part1: " << sum << std::endl;

    return 0;
}