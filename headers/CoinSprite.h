#ifndef OOP_COINSPRITE_H
#define OOP_COINSPRITE_H

#include <SFML/Graphics.hpp>
#include <memory>
#include "GameObject.h"
#include "Coin.h"

class CoinSprite : public GameObject {
private:
    Coin* coin;
    sf::Sprite sprite;
    float rotationSpeed;
    static constexpr float GROUND_Y  = 500.0f;
public:
    CoinSprite(Coin* c, const sf::Texture& tex);
    void attachCoin(Coin* c) { coin = c; }
    void update() override;
    void drawImpl(sf::RenderWindow& window) const override;
    [[nodiscard]] std::unique_ptr<GameObject> clone() const override;
};
#endif //OOP_COINSPRITE_H
