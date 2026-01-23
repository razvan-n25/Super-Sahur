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
    Enemy& enemy;
    sf::Sprite sprite;
    void drawImpl(sf::RenderWindow& window) const override;
    static constexpr float GROUND_Y  = 500.0f;

public:
    EnemySprite(Enemy& e, const sf::Texture& tex);

    void update() override;
    Enemy& getEnemy();
    [[nodiscard]] std::unique_ptr<GameObject> clone() const override;
};
#endif //OOP_ENEMYSPRITE_H
