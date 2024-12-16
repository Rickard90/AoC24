#include <vector>

struct coord {
    size_t x {}, y {};
    coord up() const {
        return coord{x, y-1};
    };
    coord down() const {
        return coord{x, y+1};
    };
    coord left() const {
        return coord{x-1, y};
    };
    coord right() const {
        return coord{x+1, y};
    };
    coord up_left() const {
        return coord{x-1, y-1};
    };
    coord down_right() const {
        return coord{x+1, y+1};
    };
    coord down_left() const {
        return coord{x-1, y+1};
    };
    coord up_right() const {
        return coord{x+1, y-1};
    };
    bool operator<(coord const other) const {
        return x < other.x || (x == other.x && y < other.y);
    }
};

template <typename T>
struct grid {
    bool contains(coord pos) {
        return pos.x < width && pos.y < height;
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
        return container[linear_index(pos.x, pos.y)];
    }
private:
    std::vector<T> container {};
    size_t width {}, height {};
    std::size_t linear_index(size_t x, size_t y) {
        return x + width * y;
    }
};
