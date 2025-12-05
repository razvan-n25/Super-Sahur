//
// Created by razva on 29/11/2025.
//

#ifndef OOP_ENEMY_H
#define OOP_ENEMY_H
#include <iostream>
#include "Blocuri_Inamici.h"

class Enemy {
private:
    HazardType type;
    float x, y;
    bool alive;

public:
    Enemy(float in_x, float in_y, HazardType in_type);
    Enemy(const Enemy& other);
    Enemy& operator=(const Enemy& other);
    ~Enemy();

    [[nodiscard]] float getX() const;
    [[nodiscard]] float getY() const;
    [[nodiscard]] HazardType getType() const;
    [[nodiscard]] bool isAlive() const;
    void moveX(float dx);   // deplasare relativă
    void setX(float nx);    // setare absolută (pt. limitare)
    void disable();

    friend std::ostream& operator<<(std::ostream& os, const Enemy& e);
};


#endif //OOP_ENEMY_H