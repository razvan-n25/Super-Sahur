//
// Created by razva on 30/11/2025.
//

#ifndef OOP_COINSPRITE_H
#define OOP_COINSPRITE_H

#include <SFML/Graphics.hpp>
#include <memory>
#include "GameObject.h"
#include "Coin.h"

class CoinSprite : public GameObject {
private:
    Coin& coin;         // legătura logică
    sf::Sprite sprite;  // sprite grafic

    float rotationSpeed; // opțional: rotație frumoasă

    static constexpr float TILE_SIZE = 64.0f;
    static constexpr float GROUND_Y  = 500.0f;

public:
    CoinSprite(Coin& c, const sf::Texture& tex);

    void update() override;
    void drawImpl(sf::RenderWindow& window) const override;

    [[nodiscard]] std::unique_ptr<GameObject> clone() const override;
};

#endif //OOP_COINSPRITE_H
