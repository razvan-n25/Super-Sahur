#ifndef OOP_PLAYER_H
#define OOP_PLAYER_H

#include <iostream>

class World;

class Player {
    friend class World;
    friend class Game;
private:
    // coordonate logice (în PIXELI)
    float x;   // poziție pe axa X
    float y;   // înălțimea picioarelor deasupra solului

    // viteze (pixeli / secundă)
    float vx;
    float vy;

    bool onGround;   // true = stă pe sol / bloc, false = în aer

    int hearts;
    int bitcoins;
    float height;    // înălțimea player-ului în pixeli (pt coliziuni, cap, etc.)

    // constante de fizică (ajustează după gust)
    static constexpr float MOVE_SPEED = 200.0f;  // pixeli / s pe orizontală
    static constexpr float JUMP_SPEED = 450.0f;  // viteză inițială în sus
    static constexpr float GRAVITY    = 900.0f;  // accelerație în jos (px/s^2)

    // control din input (apelate din Game::handleInput)
    void moveRight();
    void moveLeft();
    void stopHorizontal();
    void jump();

    // update logic (fizică: gravitație + mișcare)
    void update(float dt);

    // gameplay
    void addBitcoin(int n = 1);
    void takeDamage();

    // sol / bloc
    void setOnGround(bool value);
    [[nodiscard]] bool isOnGround() const;

public:
    Player();
    Player(float px, float py, int h);
    Player(const Player& other);
    Player& operator=(const Player& other);
    ~Player();

    // getteri
    [[nodiscard]] float getX() const;
    [[nodiscard]] float getY() const;
    [[nodiscard]] float getHeight() const;
    [[nodiscard]] int   getHearts() const;
    [[nodiscard]] int   getBitcoinCount() const;

    friend std::ostream& operator<<(std::ostream& os, const Player& a);
};

#endif // OOP_PLAYER_H
