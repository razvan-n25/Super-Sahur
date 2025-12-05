#ifndef OOP_TERRAIN_H
#define OOP_TERRAIN_H

#include <iostream>
#include "Blocuri_Inamici.h"

class Terrain {
private:
    float x;   // centrul blocului pe X (pixeli)
    float y;   // top-ul blocului (înălțime deasupra solului, 0 = sol)
    CyberBlock type;

    float width;   // dimensiunea REALĂ a sprite-ului
    float height;

public:
    Terrain(float in_x, float in_y, CyberBlock in_type);
    Terrain(const Terrain& other);
    Terrain& operator=(const Terrain& other);
    ~Terrain();

    void setSize(float w, float h); // ← apelată din TerrainSprite

    [[nodiscard]] bool isHazard() const { return type == LAVA; }
    [[nodiscard]] float getX() const { return x; }
    [[nodiscard]] float getY() const { return y; }
    [[nodiscard]] CyberBlock getType() const { return type; }

    [[nodiscard]] float getWidth() const { return width; }
    [[nodiscard]] float getHeight() const { return height; }

    friend std::ostream& operator<<(std::ostream& os, const Terrain& t);
};

#endif //OOP_TERRAIN_H
