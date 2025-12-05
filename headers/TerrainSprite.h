#ifndef OOP_TERRAINSPRITE_H
#define OOP_TERRAINSPRITE_H

#include <SFML/Graphics.hpp>
#include <memory>
#include "GameObject.h"
#include "Terrain.h"

class TerrainSprite : public GameObject {
private:
    const Terrain& terrain;
    sf::Sprite sprite;

    static constexpr float GROUND_Y = 500.0f;

public:
    TerrainSprite(const Terrain& t, const sf::Texture& tex);

    void update() override;
    void drawImpl(sf::RenderWindow& window) const override;

    [[nodiscard]] std::unique_ptr<GameObject> clone() const override;
};

#endif //OOP_TERRAINSPRITE_H
