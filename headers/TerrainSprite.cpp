#include "TerrainSprite.h"

TerrainSprite::TerrainSprite(const Terrain& t, const sf::Texture& tex)
    : GameObject(t.getType() == LAVA ? 1 : 0),    // layer 0: blocurile sub player/enemies
      terrain(t),
      sprite(tex)
{
    auto size = tex.getSize();
    // TOP-center ca să se alinieze cu t.getY()
    sprite.setOrigin(
        static_cast<float>(size.x) / 2.0f,
        0.f
    );
}

void TerrainSprite::update() {


    float screenX = terrain.getX();                // pixeli
    float screenY = GROUND_Y - terrain.getY();     // top-ul blocului

    sprite.setPosition(screenX, screenY);
}

void TerrainSprite::drawImpl(sf::RenderWindow& window) const {
    window.draw(sprite);
}

std::unique_ptr<GameObject> TerrainSprite::clone() const {
    return std::make_unique<TerrainSprite>(*this);
}
