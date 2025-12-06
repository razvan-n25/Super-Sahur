#include "EnemySprite.h"

EnemySprite::EnemySprite(Enemy& e, const sf::Texture& tex)
    : GameObject(2),
      enemy(e),
      sprite(tex)
{
    auto size = tex.getSize();
    sprite.setOrigin(
        static_cast<float>(size.x) / 2.0f,
        static_cast<float>(size.y)
    );
}

void EnemySprite::update() {
    float screenX = enemy.getX();
    float screenY = GROUND_Y - enemy.getY();
    sprite.setPosition(screenX, screenY);
}

void EnemySprite::drawImpl(sf::RenderWindow& window) const {
    if (!enemy.isAlive())
        return;
    window.draw(sprite);
}

std::unique_ptr<GameObject> EnemySprite::clone() const {
    return std::make_unique<EnemySprite>(*this);
}

Enemy& EnemySprite::getEnemy() {
    return enemy;
}
