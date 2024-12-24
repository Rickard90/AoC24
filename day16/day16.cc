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
    state(coord xy_, direction dir_) : xy{xy_}, dir{dir_} {};
    state() = default;
    coord xy {};
    direction dir {right};
    bool operator<(state const other) const {
        return xy < other.xy || (xy == other.xy && dir < other.dir);
    }
};

struct search_node {
    search_node(state pos_, int score) : pos{pos_}, score{score} {};
    search_node(coord coord_, direction dir_, int score) : pos{coord_, dir_}, score{score} {};
    state pos {};
    int score {};
    bool operator<(search_node const other) const {
        return score > other.score;
    }
};


int main() {
    uint64_t sum1 {}, sum2 {};
    grid<char> grid {};
    std::set<state> searched {};
    std::priority_queue<search_node> search_queue {};
    coord end_pos {};
    std::string line;
    size_t x {}, y {};
    while ( std::getline(std::cin, line) ) {
        std::stringstream ss {line};
        char c {};
        x = 0;
        while (ss >> c) {
            grid.push(c);
            if (c == 'S') {
                search_queue.emplace(state{coord{x, y}, right}, 0);
            }
            x++;
        }
        y++;
    }
    grid.set_height(y);
    grid.set_oor_value(' ');
    
    bool found {false};
    while (!found && search_queue.size() > 0) { 
        search_node front {search_queue.top()};
        search_queue.pop();
        if (grid(front.pos.xy) == 'E') {
            found = true;
            sum1 = front.score;
        } else if (searched.find(front.pos) == searched.end()) {
            searched.emplace(front.pos);
            switch (front.pos.dir) {
                case direction::right:
                    if (grid(front.pos.xy.right()) != '#') {
                        search_queue.emplace(front.pos.xy.right(), right, front.score+1);
                    }
                    search_queue.emplace(front.pos.xy, up, front.score+1000);
                    search_queue.emplace(front.pos.xy, down, front.score+1000);
                break;
                case direction::down:
                    if (grid(front.pos.xy.down()) != '#') {
                        search_queue.emplace(front.pos.xy.down(), down, front.score+1);
                    }
                    search_queue.emplace(front.pos.xy, left, front.score+1000);
                    search_queue.emplace(front.pos.xy, right, front.score+1000);
                break;
                case direction::left:
                    if (grid(front.pos.xy.left()) != '#') {
                        search_queue.emplace(front.pos.xy.left(), left, front.score+1);
                    }
                    search_queue.emplace(front.pos.xy, up, front.score+1000);
                    search_queue.emplace(front.pos.xy, down, front.score+1000);
                break;
                case direction::up:
                    if (grid(front.pos.xy.up()) != '#') {
                        search_queue.emplace(front.pos.xy.up(), up, front.score+1);
                    }
                    search_queue.emplace(front.pos.xy, left, front.score+1000);
                    search_queue.emplace(front.pos.xy, right, front.score+1000);
                break;
            }
        }
    }

    std::cout << "Part 1: " << sum1 << std::endl;
    std::cout << "Part 2: " << sum2 << std::endl;

    return 0;
}