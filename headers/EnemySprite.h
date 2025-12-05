//
// Created by razva on 30/11/2025.
//

#ifndef OOP_ENEMYSPRITE_H
#define OOP_ENEMYSPRITE_H

#include <SFML/Graphics.hpp>
#include <memory>
#include "GameObject.h"
#include "Enemy.h"

class EnemySprite : public GameObject {
private:
    Enemy& enemy;       // legătura cu logica
    sf::Sprite sprite;  // sprite-ul grafic

    static constexpr float TILE_SIZE = 64.0f;
    static constexpr float GROUND_Y  = 500.0f;

public:
    // tex = textura deja încărcată în Game (snake sau drone)
    EnemySprite(Enemy& e, const sf::Texture& tex);

    void update() override;
    void drawImpl(sf::RenderWindow& window) const override;
    Enemy& getEnemy();

    [[nodiscard]] std::unique_ptr<GameObject> clone() const override;
};

#endif //OOP_ENEMYSPRITE_H
