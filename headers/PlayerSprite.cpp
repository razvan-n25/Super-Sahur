#include "PlayerSprite.h"

PlayerSprite::PlayerSprite(Player& p, const sf::Texture& tex)
    : GameObject(2),   // layer 1: player / inamici
      player(p),
      sprite(tex)
{
    auto size = tex.getSize();
    // picioarele la baza sprite-ului
    sprite.setOrigin(
        static_cast<float>(size.x) / 2.0f,
        static_cast<float>(size.y)
    );
}

void PlayerSprite::update() {


    float screenX = player.getX();                 // x deja în pixeli
    float screenY = GROUND_Y - player.getY();      // y = înălțimea deasupra solului

    sprite.setPosition(screenX, screenY);
}

void PlayerSprite::drawImpl(sf::RenderWindow& window) const {
    window.draw(sprite);
}

std::unique_ptr<GameObject> PlayerSprite::clone() const {
    return std::make_unique<PlayerSprite>(*this);
}
