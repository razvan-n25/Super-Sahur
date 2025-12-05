#include "GameObject.h"

GameObject::GameObject(int layer_)
    : layer(layer_) {}

GameObject::~GameObject() = default;

void GameObject::draw(sf::RenderWindow& window) const {
    drawImpl(window);
}