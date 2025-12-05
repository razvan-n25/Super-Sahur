//
// Created by razva on 30/11/2025.
//

#ifndef OOP_GAMEOBJECT_H
#define OOP_GAMEOBJECT_H
#include <memory>
#include <SFML/Graphics.hpp>

class GameObject {
private:
    int layer;   // strat de desen

public:
    explicit GameObject(int layer_ = 0);
    virtual ~GameObject();

    [[nodiscard]] int getLayer() const { return layer; }

    // funcție virtuală pură – fiecare sprite o implementează diferit
    virtual void update() = 0;

    // interfață NON-virtuală
    void draw(sf::RenderWindow& window) const;

    // constructor virtual (clone)
    [[nodiscard]] virtual std::unique_ptr<GameObject> clone() const = 0;

    // funcție virtuală pentru desen (acum PUBLIC)
    virtual void drawImpl(sf::RenderWindow& window) const = 0;
};
#endif //OOP_GAMEOBJECT_H