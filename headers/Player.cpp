#include "Player.h"

// ----------------- CONSTRUCTORI -----------------

Player::Player()
    : x(0.f), y(0.f),
      vx(0.f), vy(0.f),
      onGround(true),
      hearts(5), bitcoins(0),
      height(64.f)    // ~80px înălțime, ajustezi după sprite
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

// ----------------- CONTROL INPUT -----------------

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
    // poți sări doar dacă ești pe ceva (sol / bloc)
    if (onGround) {
        vy = JUMP_SPEED;    // impuls în sus (y măsoară înălțimea deasupra solului)
        onGround = false;
    }
}

// ----------------- FIZICĂ -----------------

void Player::update(float dt) {
    // 1) mișcare orizontală
    x += vx * dt;

    // 2) gravitație DOAR când e în aer
    if (!onGround) {
        vy -= GRAVITY * dt;   // accelerație în jos
        y  += vy * dt;        // actualizare poziție verticală
    } else {
        vy = 0.f;             // pe sol / bloc: nu acumulăm viteză verticală
    }
    /*if (y < 0.f) { y = 0.f;
        vy = 0.f;
        onGround = true;
    }*/
    if (x < 0.f) {
        x = 0.f;
    }
    if (y < -300.f) {
        hearts = 0; // instant death sau player_.takeDamage()
    }
}


// ----------------- SOL / BLOC -----------------

void Player::setOnGround(bool value) {
    onGround = value;
}

bool Player::isOnGround() const {
    return onGround;
}

// ----------------- GAMEPLAY -----------------

void Player::addBitcoin(int n) {
    bitcoins += n;
}

void Player::takeDamage() {
    if (hearts > 0) {
        hearts--;
        std::cout << "-lost one heart (" << hearts << " left)\n";
    }
}

// ----------------- GETTERI -----------------

float Player::getX() const { return x; }
float Player::getY() const { return y; }
float Player::getHeight() const { return height; }
int   Player::getHearts() const { return hearts; }
int   Player::getBitcoinCount() const { return bitcoins; }

// ----------------- PRINT -----------------

std::ostream& operator<<(std::ostream& os, const Player& a) {
    os << "Player(x=" << a.x
       << ", y=" << a.y
       << ", hearts=" << a.hearts
       << ", height=" << a.height
       << ", bitcoins=" << a.bitcoins << ")";
    return os;
}
