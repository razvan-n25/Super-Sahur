#ifndef OOP_PLAYERSPRITE_H
#define OOP_PLAYERSPRITE_H

#include <SFML/Graphics.hpp>
#include <memory>
#include "GameObject.h"
#include "Player.h"

class PlayerSprite : public GameObject {
private:
    Player& player;
    sf::Sprite sprite;

    static constexpr float GROUND_Y = 500.0f; // poziția solului pe ecran (pixeli)

public:
    PlayerSprite(Player& p, const sf::Texture& tex);

    void update() override;
    void drawImpl(sf::RenderWindow& window) const override;

    std::unique_ptr<GameObject> clone() const override;
};

#endif //OOP_PLAYERSPRITE_H
