#include "CoinSprite.h"

CoinSprite::CoinSprite(Coin& c, const sf::Texture& tex)
    : GameObject(2),     // layer 1 (ca player/enemies, deasupra terenului)
      coin(c),
      sprite(tex),
      rotationSpeed(90.0f)  // grade / secundă
{
    auto size = tex.getSize();
    sprite.setOrigin(
        static_cast<float>(size.x) / 2.0f,
        static_cast<float>(size.y) / 2.0f
    );
}

void CoinSprite::update() {
    // dacă ai varianta cu dt: void CoinSprite::update(float dt)
    // (void)dt;

    if (coin.isCollected())
        return;

    // coin.getX() / getY() sunt în PIXELI
    float screenX = coin.getX();              // FĂRĂ * TILE_SIZE
    float screenY = GROUND_Y - coin.getY();   // pixeli deasupra solului

    sprite.setPosition(screenX, screenY);

    // animație simplă – aici 0.016 e ~dt pentru 60FPS; poți să o lași așa
    sprite.rotate(rotationSpeed * 0.016f);
}


void CoinSprite::drawImpl(sf::RenderWindow& window) const {
    if (coin.isCollected())
        return;
    window.draw(sprite);
}

std::unique_ptr<GameObject> CoinSprite::clone() const {
    return std::make_unique<CoinSprite>(*this);
}
