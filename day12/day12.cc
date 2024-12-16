#include <iostream>
#include <sstream>
#include "../helpers/grid.h"

struct square {
    char c {};
    bool counted {false};
};

std::pair<uint32_t, uint32_t> count1(grid<square>& grid, size_t x, size_t y) {
    std::pair<uint32_t, uint32_t> fence_area {0, 1};
    std::pair<uint32_t, uint32_t> returned {};
    grid(x, y).counted = true;
    for (int dx {-1}; dx <=1; dx++) {
        for (int dy {abs(dx)-1}; dy <= 1; dy+=2) {
            if (y+dy < grid.get_height() && x+dx < grid.get_width() && grid(x+dx, y+dy).c == grid(x, y).c) {
                if (!grid(x+dx, y+dy).counted) {
                    returned = count1(grid, x+dx, y+dy);
                }
            } else {
                fence_area.first++;
            }
            fence_area.first += returned.first;
            fence_area.second += returned.second;
            returned = {};
        }
    }
    return fence_area;
}

int main() {
    uint64_t sum1 {}, sum2 {};
    grid<square> grid {};
    std::string line;
    size_t y {};
    while ( std::getline(std::cin, line) ) {
        std::stringstream ss {line};
        char c {};
        while (ss >> c) {
            grid.push(square{c, false});
        }
        y++;
    }
    grid.set_height(y);


    for (size_t x {0}; x < grid.get_width(); x++) {
        for (size_t y {0}; y < grid.get_height(); y++) {
            if (!grid(x, y).counted) {
                std::pair<uint32_t, uint32_t> field = count1(grid, x, y);
                sum1 += field.first * field.second;
            }
        }
    }

    std::cout << "Part 1: " << sum1 << std::endl;
    std::cout << "Part 2: " << sum2 << std::endl;

    return 0;
}