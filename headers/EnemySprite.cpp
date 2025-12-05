#include "EnemySprite.h"

EnemySprite::EnemySprite(Enemy& e, const sf::Texture& tex)
    : GameObject(2),   // layer 1: la fel ca PlayerSprite (player + inamici)
      enemy(e),
      sprite(tex)
{
    // setăm originea jos-centru, ca la PlayerSprite
    auto size = tex.getSize();
    sprite.setOrigin(
        static_cast<float>(size.x) / 2.0f,
        static_cast<float>(size.y)
    );
}

void EnemySprite::update() {
    // (void)dt;  // dacă ai versiunea cu dt, pune asta sus și semnătura: void update(float dt)

    // enemy.getX() / getY() SUNT DEJA ÎN PIXELI
    float screenX = enemy.getX();              // FĂRĂ * TILE_SIZE
    float screenY = GROUND_Y - enemy.getY();   // tot pixeli deasupra solului

    sprite.setPosition(screenX, screenY);
}


void EnemySprite::drawImpl(sf::RenderWindow& window) const {
    // dacă vrei ca inamicii morți să dispară complet:
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
