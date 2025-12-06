#include "Player.h"

Player::Player()
    : x(0.f), y(0.f),
      vx(0.f), vy(0.f),
      onGround(true),
      hearts(5), bitcoins(0),
      height(64.f)
{}

Player::Player(float px, float py, int h)
    : x(px), y(py),
      vx(0.f), vy(0.f),
      onGround(true),
      hearts(h), bitcoins(0),
      height(64.f)
{}

Player::Player(const Player& other)
    : x(other.x), y(other.y),
      vx(other.vx), vy(other.vy),
      onGround(other.onGround),
      hearts(other.hearts),
      bitcoins(other.bitcoins),
      height(other.height)
{}

Player& Player::operator=(const Player& other) {
    if (this != &other) {
        x        = other.x;
        y        = other.y;
        vx       = other.vx;
        vy       = other.vy;
        onGround = other.onGround;
        hearts   = other.hearts;
        bitcoins = other.bitcoins;
        height   = other.height;
    }
    return *this;
}

Player::~Player() = default;

void Player::moveRight() {

    vx = MOVE_SPEED;   // pixeli / secundă
}

void Player::moveLeft() {
    vx = -MOVE_SPEED;
}

void Player::stopHorizontal() {
    vx = 0.f;
}

void Player::jump() {
    if (onGround) {
        vy = JUMP_SPEED;
        onGround = false;
    }
}


void Player::update(float dt) {
    x += vx * dt;

    if (!onGround) {
        vy -= GRAVITY * dt;
        y  += vy * dt;
    } else {
        vy = 0.f;
    }
    /*if (y < 0.f) { y = 0.f;
        vy = 0.f;
        onGround = true;
    }*/
    if (x < 0.f) {
        x = 0.f;
    }
    if (y < -300.f) {
        hearts = 0;
    }
}

void Player::setOnGround(bool value) {
    onGround = value;
}

void Player::addBitcoin(int n) {
    bitcoins += n;
}

void Player::takeDamage() {
    if (hearts > 0) {
        hearts--;
        std::cout << "-lost one heart (" << hearts << " left)\n";
    }
}


float Player::getX() const { return x; }
float Player::getY() const { return y; }
float Player::getHeight() const { return height; }
int   Player::getHearts() const { return hearts; }
int   Player::getBitcoinCount() const { return bitcoins; }

std::ostream& operator<<(std::ostream& os, const Player& a) {
    os << "Player(x=" << a.x
       << ", y=" << a.y
       << ", hearts=" << a.hearts
       << ", height=" << a.height
       << ", bitcoins=" << a.bitcoins << ")";
    return os;
}
