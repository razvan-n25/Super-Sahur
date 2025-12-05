//
// Created by razva on 29/11/2025.
//

#ifndef OOP_COIN_H
#define OOP_COIN_H
#include <iostream>

class Coin {
private:
    float x, y;
    bool collected;

public:
    Coin(float in_x, float in_y);
    Coin(const Coin& other);
    Coin& operator=(const Coin& other);
    ~Coin();

    void collect();
    [[nodiscard]] bool isCollected() const;
    [[nodiscard]] float getX() const;
    [[nodiscard]] float getY() const;

    friend std::ostream& operator<<(std::ostream& os, const Coin& c);
};


#endif //OOP_COIN_H