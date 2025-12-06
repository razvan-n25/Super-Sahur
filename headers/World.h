#ifndef OOP_WORLD_H
#define OOP_WORLD_H

#include <iostream>
#include <vector>
#include <string>

#include "Player.h"
#include "Enemy.h"
#include "Terrain.h"
#include "Coin.h"

class World {
private:
    Player player_;
    std::vector<Enemy>   enemies_;
    std::vector<Terrain> terrains_;
    std::vector<Coin>    coins_;

    void handleTerrainCollisions();
    void checkEnemies();
    void collectCoins();
    bool levelCompleted_ = false;

public:
    explicit World(const Player& p);
    World(const World& other);
    World& operator=(const World& other);
    ~World();

    void addTerrain(const Terrain& t);
    void addCoin(const Coin& c);
    void addEnemy(const Enemy& e);

    Player& player();
    [[nodiscard]] const Player& player() const;

    void update();
    [[nodiscard]] bool isGameOver() const;
    [[nodiscard]] bool isLevelCompleted() const { return levelCompleted_; }


    // GETTERS pentru Game (sprite-uri)
    std::vector<Enemy>& getEnemies() { return enemies_; }
    [[nodiscard]] const std::vector<Enemy>& getEnemies() const { return enemies_; }

    std::vector<Terrain>& getTerrains() { return terrains_; }
    [[nodiscard]] const std::vector<Terrain>& getTerrains() const { return terrains_; }

    std::vector<Coin>& getCoins() { return coins_; }
    [[nodiscard]] const std::vector<Coin>& getCoins() const { return coins_; }

    friend std::ostream& operator<<(std::ostream& os, const World& w);
};

#endif // OOP_WORLD_H
