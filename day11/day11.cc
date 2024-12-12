#include <iostream>
#include <map>
#include <cmath>
#include <sstream>

std::map<std::pair<uint64_t, uint64_t>, uint64_t> stored {};

std::pair<uint64_t, uint64_t> split_number(uint64_t number, uint64_t nr_digits) {
    uint64_t first (number/(pow(10,nr_digits/2)));
    uint64_t second (number-(first*pow(10, nr_digits/2)));
    return std::pair<uint64_t, uint64_t>(first, second);
}

uint64_t number_of_digits(uint64_t n) {
    for (uint64_t i {1}; ; i++) {
        if (n < pow(10, i)) {
            return i;
        }
    }
}

uint64_t count1(uint64_t number, uint64_t depth) {
    if (depth > 0) {
        if (stored.find(std::pair<uint64_t, uint64_t>(number, depth)) != stored.end()) {
            return stored[std::pair<uint64_t, uint64_t>(number, depth)];
        } else {
            uint64_t sum {};
            if (number == 0) {
                sum += count1(number+1, depth-1);
            } else {
                uint64_t digits {number_of_digits(number)};
                if (digits % 2 == 0) {
                    std::pair<uint64_t, uint64_t> split = split_number(number, digits);
                    sum += count1(split.first, depth-1);
                    sum += count1(split.second, depth-1);
                } else {
                    sum += count1(number*2024, depth-1);
                }
            }
            stored[std::pair<uint64_t, uint64_t>(number, depth)] = sum;
            return sum;
        }
    } else {
        return 1;
    }
}

int main() {
    uint64_t sum1 {}, sum2 {};
    std::string line;
    std::getline(std::cin, line);
    std::stringstream ss {line};
    int number {};
    while (ss >> number) {
        sum1 += count1(number, 25);
        sum2 += count1(number, 75);
    }

    std::cout << "Part 1: " << sum1 << std::endl;
    std::cout << "Part 2: " << sum2 << std::endl;

    return 0;
}