#include <iostream>
#include <set>
#include <queue>
#include "../helpers/grid.h"

enum direction {
    right,
    down,
    left,
    up
};

struct state {
    state(coord xy_, direction dir_, int score_) : xy{xy_}, dir{dir_}, score{score_} {};
    state() = default;
    coord xy {};
    direction dir {right};
    int score {};
    bool operator<(state const& other) const {
        return score > other.score;
    }
};



int main() {
    uint64_t sum1 {}, sum2 {};
    std::set<coord> part2_pos {};
    grid<char> grid {};

    auto state_comparator = [](const state& lhs, const state& rhs) {
        return lhs.xy < rhs.xy || (lhs.xy == rhs.xy && lhs.dir < rhs.dir);
    };
    std::set<state, decltype(state_comparator)> searched(state_comparator);
    std::priority_queue<state> search_queue {};

    grid.read(std::cin, [&](char c, size_t x, size_t y) {
        if (c == 'S') {
            search_queue.emplace(state{coord{x, y}, right, 0});
        }
    });
    

    while (!search_queue.empty()) { 
        state front {search_queue.top()};
        search_queue.pop();
        if (grid[front.xy] == 'E') {
            sum1 = front.score;
            break;
        } else if (searched.find(front) == searched.end()) {
            searched.emplace(front);
            switch (front.dir) {
                case direction::right:
                    if (grid[front.xy.right()] != '#') {
                        search_queue.emplace(front.xy.right(), right, front.score+1);
                    }
                    search_queue.emplace(front.xy, up, front.score+1000);
                    search_queue.emplace(front.xy, down, front.score+1000);
                break;
                case direction::down:
                    if (grid[front.xy.down()] != '#') {
                        search_queue.emplace(front.xy.down(), down, front.score+1);
                    }
                    search_queue.emplace(front.xy, left, front.score+1000);
                    search_queue.emplace(front.xy, right, front.score+1000);
                break;
                case direction::left:
                    if (grid[front.xy.left()] != '#') {
                        search_queue.emplace(front.xy.left(), left, front.score+1);
                    }
                    search_queue.emplace(front.xy, up, front.score+1000);
                    search_queue.emplace(front.xy, down, front.score+1000);
                break;
                case direction::up:
                    if (grid[front.xy.up()] != '#') {
                        search_queue.emplace(front.xy.up(), up, front.score+1);
                    }
                    search_queue.emplace(front.xy, left, front.score+1000);
                    search_queue.emplace(front.xy, right, front.score+1000);
                break;
            }
        }
    }

    std::cout << "Part 1: " << sum1 << std::endl;
    std::cout << "Part 2: " << part2_pos.size() << std::endl;

    return 0;
}