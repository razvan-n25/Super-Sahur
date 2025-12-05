#ifndef OOP_GAME_H
#define OOP_GAME_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>

#include "World.h"
#include "GameObject.h"
#include "PlayerSprite.h"
#include "EnemySprite.h"
#include "TerrainSprite.h"
#include "CoinSprite.h"

class Game {
private:
    sf::RenderWindow window;
    sf::Clock clock;

    World world;

    // toate obiectele desenabile (player, inamici, blocuri, monede)
    std::vector<std::unique_ptr<GameObject>> objects;

    // texturi
    sf::Texture playerTex;
    sf::Texture fishTex;
    sf::Texture droneTex;
    sf::Texture coinTex;
    sf::Texture cementTex;
    sf::Texture platformTex;
    sf::Texture jumpLowTex;
    sf::Texture jumpHighTex;
    sf::Texture lavaTex;

    // opțional: background
    sf::Texture backgroundTex;
    sf::Sprite  backgroundSprite;
    bool        hasBackground = false;

    void handleInput();
    void initWorld();     // poziționează blocuri, inamici, monede (în PIXELI)
    void initTextures();  // încarcă texturile din fișiere
    void initSprites();   // creează sprite-urile pe baza lui world + texturi

public:
    Game();
    void run();
    int getCoinCount() const;

};

#endif // OOP_GAME_H
