#include "Coin.h"

Coin::Coin(float in_x, float in_y)
    : x(in_x), y(in_y), collected(false) {}

Coin::Coin(const Coin& other)
    : x(other.x), y(other.y), collected(other.collected) {}

Coin& Coin::operator=(const Coin& other) {
    if (this != &other) {
        x = other.x;
        y = other.y;
        collected = other.collected;
    }
    return *this;
}

Coin::~Coin() = default;

void Coin::collect() { collected = true; }
bool Coin::isCollected() const { return collected; }
float Coin::getX() const { return x; }
float Coin::getY() const { return y; }

std::ostream& operator<<(std::ostream& os, const Coin& c) {
    os << "Coin(x=" << c.x
       << ", y=" << c.y
       << ", collected=" << (c.collected ? "true" : "false") << ")";
    return os;
}
