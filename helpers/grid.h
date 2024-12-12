#include <iostream>
#include <vector>
#include <set>
#include <sstream>

using coord = std::pair<size_t, size_t>;

template <typename T>
struct grid {
    bool contains(coord pos) {
        return pos.first < width && pos.second < height;
    }
    void set_width(size_t w) {
        width=w;
        height = container.size()/width;
    }
    void set_height(size_t h) {
        height = h;
        width = container.size()/height;
    }
    size_t get_height() {
        return height;
    }
    size_t get_width() {
        return width;
    }
    void push(T value) {
        container.push_back(value);
    }
    T& operator()(size_t x, size_t y) {
        return container[linear_index(x, y)];
    }
    T& operator()(coord pos) {
        return container[linear_index(pos.first, pos.second)];
    }
    T& get_nw(coord pos) {
        return container[linear_index(pos.first-1, pos.second-1)];
    }
    T& get_sw(coord pos) {
        return container[linear_index(pos.first-1, pos.second+1)];
    }
    T& get_ne(coord pos) {
        return container[linear_index(pos.first+1, pos.second-1)];
    }
    T& get_se(coord pos) {
        return container[linear_index(pos.first+1, pos.second+1)];
    }
private:
    std::vector<T> container {};
    size_t width {}, height {};
    std::size_t linear_index(size_t x, size_t y) {
        return x + width * y;
    }
};
