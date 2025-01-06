#include <vector>
#include <exception>
#include <sstream>
#include <iostream>
#include <functional>

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
std::ostream& operator<<(std::ostream& os, const coord& coord_ ) {
    os << coord_.x << " " << coord_.y;
    return os;
}

template <typename T>
class grid {
public:
    bool contains(coord pos) {
        return pos.x < width && pos.y < height;
    }
    bool is_equal(size_t x1, size_t y1, size_t x2, size_t y2) {
        if ((x1 >= width || y1 >= height) && (x2 >= width || y2 >= height)) {
            return true;
        } else if (x1 >= width || y1 >= height || x2 >= width || y2 >= height) {
            return false;
        }
        return at(x1, y1) == at(x2, y2);
    }
    bool is_equal(coord pos1, coord pos2) {
        return is_equal(pos1.x, pos1.y, pos2.x, pos2.y);
    }
    void set_width(size_t w) {
        if (w == 0) {
            throw std::invalid_argument("Width cannot be zero.");
        }
        width = w;
        height = container.size() / width;
    }
    void set_height(size_t h) {
        if (h == 0) {
            throw std::invalid_argument("Height cannot be zero.");
        }
        height = h;
        width = container.size()/height;
    }
    size_t get_height() const {
        return height;
    }
    size_t get_width() const {
        return width;
    }
    void push(T value) {
        container.push_back(value);
    }
    template <typename func = std::function<void(char, size_t, size_t)>>
    void read(std::istream& stream, func f = [](char, size_t, size_t){}) {
        std::string line;
        size_t x {}, y {};
        while ( std::getline(stream, line) ) {
            std::stringstream ss {line};
            char c {};
            x = 0;
            while (ss >> c) {
                push(T(c));
                f(c, x, y);
                x++;
            }
            y++;
        }
        set_height(y);
    }
    T& operator[](coord pos) {
        return container[linear_index(pos.x, pos.y)];
    }
    T& at(size_t x, size_t y) {
        if (x < width && y < height) {
            return container[linear_index(x, y)];
        }
        throw std::out_of_range(std::string{"x:" + std::to_string(x) + " y:" + std::to_string(y)});    
    }
    T& at(coord pos) {
        return at(pos.x, pos.y);
    }
private:
    std::vector<T> container {};
    size_t width {}, height {};
    std::size_t linear_index(size_t x, size_t y) {
        return x + width * y;
    }
};
