#include <iostream>
#include <vector>
#include <sstream>

bool check_line(std::vector<int>& line, int skip = -1) {
    int prev {-1};
    bool inc {false}, dec {false};
    for (size_t i{}; i < line.size(); i++) {
        if (i != skip) {
            int latest = line[i];
            if (prev != -1) {
                if (latest < prev) {
                    if (inc) {
                        return false;
                    }
                    dec = true;
                } else if (latest > prev){
                    if (dec) {
                        return false;
                    }
                    inc = true;
                }
                if (abs(prev-latest) > 3 || abs(prev-latest) < 1) {
                    return false;
                }
            }
            prev = latest;
        }
    }
    return true;
}


int main() {
    int sum1 {}, sum2 {};
    std::string line;

    while ( std::getline(std::cin, line) ) {
        std::stringstream ss {line};
        std::vector<int> numbers {};
        int number {};
        bool safe {true};
        while (ss >> number) {
            numbers.push_back(number);
        }

        if (check_line(numbers))
            sum1++;
        
        
        for (int skip{-1}; skip < static_cast<int>(numbers.size()); skip++) {
            if (check_line(numbers, skip)) {                
                sum2++;
                break;
            }
        }
    }
    std::cout << "Part 1: " << sum1 << std::endl;
    std::cout << "Part 2: " << sum2 << std::endl;

    return 0;
}