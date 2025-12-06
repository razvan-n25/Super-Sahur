#ifndef OOP_PLAYER_H
#define OOP_PLAYER_H

#include <iostream>


class Player {
    friend class World;
    friend class Game;
private:
    float x;
    float y;

    float vx;
    float vy;

    bool onGround;

    int hearts;
    int bitcoins;
    float height;

    // constante de fizică (ajustează după gust)
    static constexpr float MOVE_SPEED = 200.0f;
    static constexpr float JUMP_SPEED = 450.0f;
    static constexpr float GRAVITY    = 900.0f;

    void moveRight();
    void moveLeft();
    void stopHorizontal();
    void jump();

    void update(float dt);

    void addBitcoin(int n = 1);
    void takeDamage();

    void setOnGround(bool value);


public:
    Player();
    Player(float px, float py, int h);
    Player(const Player& other);
    Player& operator=(const Player& other);
    ~Player();

    [[nodiscard]] float getX() const;
    [[nodiscard]] float getY() const;
    [[nodiscard]] float getHeight() const;
    [[nodiscard]] int   getHearts() const;
    [[nodiscard]] int   getBitcoinCount() const;

    friend std::ostream& operator<<(std::ostream& os, const Player& a);
};

#endif // OOP_PLAYER_H
