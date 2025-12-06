#include "World.h"
#include <cmath>

namespace {

    constexpr float lava_halfwidth=32.f;
    constexpr float TILE_SIZE = 64.f;
    constexpr float BLOCK_HALF_WIDTH  = TILE_SIZE / 2.0f;
    constexpr float BLOCK_HALF_HEIGHT = TILE_SIZE / 2.0f;
    constexpr float LEVEL_END_X = 2000.f;
    constexpr float PLAYER_HALF_WIDTH  =25.f; // pe X
}


World::World(const Player& p)
    : player_(p) {}

World::World(const World& other)
    : player_(other.player_),
      enemies_(other.enemies_),
      terrains_(other.terrains_),
      coins_(other.coins_) {}

World& World::operator=(const World& other) {
    if (this != &other) {
        player_   = other.player_;
        enemies_  = other.enemies_;
        terrains_ = other.terrains_;
        coins_    = other.coins_;
    }
    return *this;
}

World::~World() = default;

void World::addTerrain(const Terrain& t) { terrains_.push_back(t); }
void World::addCoin(const Coin& c)       { coins_.push_back(c); }
void World::addEnemy(const Enemy& e)     { enemies_.push_back(e); }

Player& World::player() { return player_; }
const Player& World::player() const { return player_; }

void World::handleTerrainCollisions() {
    float feetY        = player_.y;
    float playerHeight = player_.getHeight();
    float playerTop    = feetY + playerHeight;
    float playerBottom = feetY;
    float playerCenterX = player_.x;
    float playerCenterY = (playerTop + playerBottom) / 2.0f;
    float playerHalfH   = playerHeight / 2.0f;

    bool standingOnSomething = false;

    for (const auto& t : terrains_) {
        float blockCenterX = t.getX();
        float blockTop     = t.getY();
        float blockBottom  = blockTop - (TILE_SIZE);
        float blockCenterY = (blockTop + blockBottom) / 2.0f;

        //1) LAVA
        if (t.isHazard()) {
            float dx      = std::fabs(playerCenterX - blockCenterX);
            float maxHalf = lava_halfwidth + PLAYER_HALF_WIDTH-20.f;

            bool overlapX  = dx <= maxHalf;
            bool touchLava = (playerBottom <= blockTop);

            if (overlapX && touchLava) {
                std::cout << "TOUCHED LAVA, DEAD!\n";
                while (player_.getHearts() > 0)
                    player_.takeDamage();
                return;
            }
            continue;
        }

        // 2) BLOCURILE NORMALE: AABB
        float dx = playerCenterX - blockCenterX;
        float dy = playerCenterY - blockCenterY;

        float overlapX = (BLOCK_HALF_WIDTH  + PLAYER_HALF_WIDTH) - std::fabs(dx);
        float overlapY = (BLOCK_HALF_HEIGHT + playerHalfH)      - std::fabs(dy);

        if (overlapX <= 0.f || overlapY <= 0.f)
            continue;

        if (overlapX < overlapY) {
            // perete
            if (dx > 0.f)
                player_.x += overlapX;
            else
                player_.x -= overlapX;
            player_.vx = 0.f;
        } else {
            // podea / tavan
            if (dy > 0.f) {
                if (player_.vy <= 0.f) {
                    player_.y  = blockTop;
                    player_.vy = 0.f;
                    player_.setOnGround(true);
                    standingOnSomething = true;
                }
            } else {
                if (player_.vy > 0.f) {
                    player_.y  = blockBottom - playerHeight;
                    player_.vy = 0.f;
                }
            }
        }

        feetY         = player_.y;
        playerTop     = feetY + playerHeight;
        playerBottom  = feetY;
        playerCenterX = player_.x;
        playerCenterY = (playerTop + playerBottom) / 2.0f;
    }

    if (!standingOnSomething ) {
        player_.setOnGround(false);
    }
}


void World::checkEnemies() {
    const float epsX   = 20.f;
    const float epsHead = 35.f;

    for (auto& e : enemies_) {
        if (!e.isAlive()) continue;

        if (e.getType() == FISH) {
            bool touching =
                std::fabs(player_.x - e.getX()) <= epsX &&
                std::fabs(player_.y - e.getY()) <= epsHead;
            if (touching) {
                player_.takeDamage();
                std::cout << "You touched a FISH!\n";
                e.disable();
            }
        } else {
            float headY = player_.y + player_.getHeight();
            bool nearX  =std::fabs(player_.x - e.getX()) <= epsX;
            if (nearX && std::fabs(e.getY()+32.f - headY) <= epsHead) {
                player_.takeDamage();
                std::cout << "Drone hit your HEAD!\n";
                e.disable();
            }
        }
    }
}


void World::collectCoins() {
    const float epsX = 20.f;
    for (auto& c : coins_) {
        if (c.isCollected()) continue;

        bool nearX =
            std::fabs(player_.x - c.getX()) <= epsX;

        float headY = player_.y + player_.getHeight();
        bool withinHeight =
            (c.getY() >= player_.y && c.getY() <= headY);

        if (nearX && withinHeight) {
            c.collect();
            player_.addBitcoin();
            std::cout << "+1 bitcoin collected!\n";
        }
    }
}


void World::update() {
    checkEnemies();
    collectCoins();
    handleTerrainCollisions();
    if (player_.getX() >= LEVEL_END_X) {
        levelCompleted_ = true;
    }
}

bool World::isGameOver() const {
    return player_.getHearts() <= 0;
}


std::ostream& operator<<(std::ostream& os, const World& w) {
    os << "World:\n" << w.player_ << "\n";
    for (const auto& e : w.enemies_)  os << e << "\n";
    for (const auto& t : w.terrains_) os << t << "\n";
    for (const auto& c : w.coins_)    os << c << "\n";
    return os;
}
