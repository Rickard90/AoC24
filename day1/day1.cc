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
        int a {}, b {};
        ss >> a >> b;
        lv.push_back(a);
        rv.push_back(b);
        rm[b]++;
    }
    std::sort(lv.begin(), lv.end());
    std::sort(rv.begin(), rv.end());
    for (int i = 0; i < rv.size(); i++) {
        sum += std::abs( lv[i] - rv[i] );
    }
    std::cout << "Part1: " << sum << std::endl;

    sum = 0;
    for (int a : lv) {
        sum += a * rm[a];
    }
    std::cout << "Part2: " << sum << std::endl;

    return 0;
}
