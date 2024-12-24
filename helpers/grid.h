#include <vector>
#include <exception>
#include <sstream>
#include <iostream>

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
    bool operator==(coord const other) const {
        return x == other.x && y == other.y;
    }
    
};
std::ostream& operator<<(std::ostream& os, coord& coord_ ) {
    os << coord_.x << " " << coord_.y;
    return os;
}

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
    void set_oor_value(T oor_value) {
        default_return = oor_value;
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
    void read(std::istream& stream) {
        std::string line;
        size_t x {}, y {};
        while ( std::getline(stream, line) ) {
            std::stringstream ss {line};
            char c {};
            x = 0;
            while (ss >> c) {
                push(T(c));
                x++;
            }
            y++;
        }
        set_height(y);
    }
    T& operator()(size_t x, size_t y) {
        if (x < width && y < height) {
            return container[linear_index(x, y)];
        }
        return default_return;
    }
    T& operator()(coord pos) {
        return operator()(pos.x, pos.y);
    }
    T& at(size_t x, size_t y) {
        if (!(x < width && y < height)) {
            throw std::out_of_range(std::string{"x:" + std::to_string(x) + " y:" + std::to_string(y)});    
        }
        return container[linear_index(x, y)];
    }
    T& at(coord pos) {
        return at(pos.x, pos.y);
    }
private:
    std::vector<T> container {};
    T default_return {};
    size_t width {}, height {};
    std::size_t linear_index(size_t x, size_t y) {
        return x + width * y;
    }
};
