#include "CoinSprite.h"

CoinSprite::CoinSprite(Coin* c, const sf::Texture& tex)
    : GameObject(2),
      coin(c),
      sprite(tex),
      rotationSpeed(90.0f)
{
    auto size = tex.getSize();
    sprite.setOrigin(
        static_cast<float>(size.x) / 2.0f,
        static_cast<float>(size.y) / 2.0f
    );
}

void CoinSprite::update() {
    if (!coin)
        return;

    if (coin->isCollected())
        return;
    float screenX = coin->getX();
    float screenY = GROUND_Y - coin->getY();
    sprite.setPosition(screenX, screenY);
    sprite.rotate(rotationSpeed * 0.016f);
}
void CoinSprite::drawImpl(sf::RenderWindow& window) const {
    if (!coin)
        return;
    if (coin->isCollected())
        return;
    window.draw(sprite);
}
std::unique_ptr<GameObject> CoinSprite::clone() const {
    return std::make_unique<CoinSprite>(*this);
}
