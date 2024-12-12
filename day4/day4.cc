#include <iostream>
#include <vector>
#include <set>
#include <sstream>
#include "../helpers/grid.h"

int count1(grid<char>& grid, const coord& pos, const std::string& word) {
    int count {};
    for (int x {-1}; x <= 1; x++) {
        for (int y {-1}; y <= 1; y++) {
            bool wrong = false;
            coord next_pos = pos;
            for (char const c : word) {
                if (!grid.contains(next_pos) || grid(next_pos) != c) {
                    wrong = true;
                    break;
                }
                next_pos.first += x;
                next_pos.second += y;
            }
            count += !wrong;
        }
    }
    return count;
}

int count2(grid<char>& grid, const coord& pos) {
    if (pos.first > 0 && pos.first < grid.get_width()-1 &&
            pos.second > 0 && pos.second < grid.get_height()-1 &&
            grid.get_ne(pos) + grid.get_sw(pos) + 100 * (grid.get_se(pos) + grid.get_nw(pos)) ==
            'M' + 'S' + 100*('M' + 'S')) {
        return 1;
    }
    return 0;
}


int main() {
    int sum1 {}, sum2 {};
    std::string line;
    size_t x {}, y {};
    grid<char> grid {};
    std::set<coord> pos_with_x {}, pos_with_a {};
    while ( std::getline(std::cin, line) ) {
        std::stringstream ss {line};
        char c {};
        size_t x {};
        while (ss >> c) {
            grid.push(c);
            if (c =='X')
                pos_with_x.insert(coord{x, y});
            else if (c == 'A')
                pos_with_a.insert(coord{x, y});
            x++;
        }
        y++;
    }
    grid.set_height(y);
    
    std::string word {"XMAS"}; 
    for (coord pos : pos_with_x) {
        sum1 += count1(grid, pos, word);
    }
    for (coord pos : pos_with_a) {
        sum2 += count2(grid, pos);
    }

    std::cout << "Part 1: " << sum1 << std::endl;
    std::cout << "Part 2: " << sum2 << std::endl;

    return 0;
}