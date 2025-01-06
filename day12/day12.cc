#include <iostream>
#include "../helpers/grid.h"

struct square {
    square(char c_) {c = c_;};
    square() = default;
    char c {};
    bool counted {false};
    bool operator==(square const other) const {
        return c == other.c;
    }
};

std::pair<uint32_t, uint32_t> count1(grid<square>& grid, size_t x, size_t y) {
    std::pair<uint32_t, uint32_t> fence_area {0, 1};
    std::pair<uint32_t, uint32_t> returned {};
    grid.at(x, y).counted = true;
    for (int dx {-1}; dx <=1; dx++) {
        for (int dy {abs(dx)-1}; dy <= 1; dy+=2) {
            if (y+dy < grid.get_height() && x+dx < grid.get_width() && grid.is_equal(x+dx, y+dy, x, y)) {
                if (!grid.at(x+dx, y+dy).counted) {
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

std::pair<uint32_t, uint32_t> count2(grid<square>& grid, size_t x, size_t y, char start_c) {
    std::pair<uint32_t, uint32_t> corners_area {}, returned {};
    if (y < grid.get_height() && x < grid.get_width() && !grid.at(x, y).counted && grid.at(x, y).c == start_c) {
        grid.at(x, y).counted = true;
        corners_area.second++;
        for (int dx {-1}; dx <= 1; dx+=2) {
            for (int dy {-1}; dy <= 1; dy+=2) {
                if (!grid.is_equal(coord{x + dx, y + dy}, coord{x, y}) && 
                    grid.is_equal(coord{x + dx, y}, coord{x, y}) && 
                    grid.is_equal(coord{x, y + dy}, coord{x, y})) {
                    corners_area.first++;
                } else if (!grid.is_equal(coord{x + dx, y}, coord{x, y}) && 
                           !grid.is_equal(coord{x, y + dy}, coord{x, y})) {
                    corners_area.first++;
                }
            }
        }
        for (int dx {-1}; dx <=1; dx++) {
            for (int dy {abs(dx)-1}; dy <= 1; dy+=2) {
                returned = count2(grid, x+dx, y+dy, start_c);
                corners_area.first += returned.first;
                corners_area.second += returned.second;
            }
        }
    }
    return corners_area;
}


int main() {    
    uint64_t sum1 {}, sum2 {};
    grid<square> grid {};
    grid.read(std::cin);

    for (size_t x {0}; x < grid.get_width(); x++) {
        for (size_t y {0}; y < grid.get_height(); y++) {
            if (!grid.at(x, y).counted) {
                std::pair<uint32_t, uint32_t> field = count1(grid, x, y);
                sum1 += field.first * field.second;
            }
        }
    }

    for (size_t x {0}; x < grid.get_width(); x++) {
        for (size_t y {0}; y < grid.get_height(); y++) {
            grid.at(x, y).counted = false;
        }
    }

    for (size_t x {0}; x < grid.get_width(); x++) {
        for (size_t y {0}; y < grid.get_height(); y++) {
            if (!grid.at(x, y).counted) {
                std::pair<uint32_t, uint32_t> field = count2(grid, x, y, grid.at(x, y).c);
                sum2 += field.first * field.second;
            }
        }
    }
    std::cout << "Part 1: " << sum1 << std::endl;
    std::cout << "Part 2: " << sum2 << std::endl;

    return 0;
}