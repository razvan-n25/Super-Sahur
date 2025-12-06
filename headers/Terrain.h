#ifndef OOP_TERRAIN_H
#define OOP_TERRAIN_H

#include <iostream>
#include "Blocuri_Inamici.h"

class Terrain {
private:
    float x;
    float y;
    CyberBlock type;

    float width;
    float height;

public:
    Terrain(float in_x, float in_y, CyberBlock in_type);
    Terrain(const Terrain& other);
    Terrain& operator=(const Terrain& other);
    ~Terrain();



    [[nodiscard]] bool isHazard() const { return type == LAVA; }
    [[nodiscard]] float getX() const { return x; }
    [[nodiscard]] float getY() const { return y; }
    [[nodiscard]] CyberBlock getType() const { return type; }
    [[nodiscard]] float getHeight() const { return height; }

    friend std::ostream& operator<<(std::ostream& os, const Terrain& t);
};

#endif //OOP_TERRAIN_H
