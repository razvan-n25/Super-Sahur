//
// Created by razva on 29/11/2025.
//

#include "Enemy.h"
Enemy::Enemy(float in_x, float in_y, HazardType in_type)
    : type(in_type), x(in_x), y(in_y), alive(true) {}

Enemy::Enemy(const Enemy& other)
    : type(other.type), x(other.x), y(other.y), alive(other.alive) {}

Enemy& Enemy::operator=(const Enemy& other) {
    if (this != &other) {
        type = other.type;
        x = other.x;
        y = other.y;
        alive = other.alive;
    }
    return *this;
}

Enemy::~Enemy() = default;

float Enemy::getX() const { return x; }
float Enemy::getY() const { return y; }
HazardType Enemy::getType() const { return type; }
bool Enemy::isAlive() const { return alive; }
void Enemy::moveX(float dx) {
    x += dx;
}

void Enemy::setX(float nx) {
    x = nx;
}
void Enemy::disable() { alive = false; }

std::ostream& operator<<(std::ostream& os, const Enemy& e) {
    os << "Enemy(type=" << (e.type == FISH ? "FISH" : "DRONE")
       << ", x=" << e.x
       << ", y=" << e.y
       << ", alive=" << (e.alive ? "true" : "false") << ")";
    return os;
}