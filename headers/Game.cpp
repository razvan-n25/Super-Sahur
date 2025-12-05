#include "Game.h"
#include <iostream>
#include "GameExcepsions.h"


namespace {
    constexpr float TILE_b_e_c = 64.f;
    constexpr float TILE_p=128.f;
    constexpr float TILE_lava=64.f;
    constexpr float TILE_bg=64.f;


}

// ----------------- CONSTRUCTOR -----------------

Game::Game()
    : window(sf::VideoMode(1280, 720), "Cyber Platform"),
      world(Player(TILE_p / 2.f, 0.f, 5))   // player la x = mijlocul primului bloc, pe sol (y=0)
{
    window.setFramerateLimit(180);

    initWorld();     // punem blocuri, inamici, coins în World (în PIXELI)
    initTextures();  // încărcăm texturile
    initSprites();   // facem sprite-uri pentru tot ce e în World
}

// ----------------- INIT WORLD (LOGICĂ NIVEL, TOTUL ÎN PIXELI) -----------------

void Game::initWorld() {
    // Ground: o bandă de CEMENT la y=0, de la x = 0...10 tile-uri
    bool hasGround=false;
    for (int i = 0; i <= 7; ++i) {
        float centerX = i * TILE_bg + TILE_bg / 2.f;   // centrul blocului
        if (i<=3)
        world.addTerrain(Terrain(centerX, 0.f, CEMENT)),hasGround=true; // top-ul blocului = 0px deasupra solului
        else
        world.addTerrain(Terrain(centerX, -64.f, CEMENT));
    }

    // O platformă suspendată la 2 tile-uri deasupra solului
    {
        float yTop = 2.f * TILE_b_e_c;  // top-ul platformei la 2 tile-uri peste sol
        float x4 = 4 * TILE_b_e_c + TILE_b_e_c / 2.f;
        float x5 = 5 * TILE_b_e_c + TILE_b_e_c / 2.f;
        float x6 = 6 * TILE_b_e_c + TILE_b_e_c / 2.f;

        world.addTerrain(Terrain(x4, yTop, PLATFORM));
        world.addTerrain(Terrain(x5, yTop, PLATFORM));
        world.addTerrain(Terrain(x6, yTop, PLATFORM));

    }

    // Două jump boxes la 1 tile deasupra solului
    {
        float yTop = 1.f * TILE_b_e_c;
        float x2 = 2 * TILE_b_e_c + TILE_b_e_c / 2.f;
        float x8 = 8 * TILE_b_e_c + TILE_b_e_c / 2.f;

        world.addTerrain(Terrain(x2, yTop, JUMP_BOX_LOW));
        world.addTerrain(Terrain(x8, yTop, JUMP_BOX_HIGH));
    }

    // Un „lac” de LAVA
    {
        float yTop = 0.f;
        float x12 = 9 * TILE_lava + TILE_lava / 2.f;
        float x13 = 10 * TILE_lava + TILE_lava / 2.f;
        float x14 = 11 * TILE_lava + TILE_lava / 2.f;

        world.addTerrain(Terrain(x12, yTop, LAVA));
        world.addTerrain(Terrain(x13, yTop, LAVA));
        world.addTerrain(Terrain(x14, yTop, LAVA));
    }

    // Inamici (coordonate în pixeli, y = înălțime deasupra solului)
    world.addEnemy(Enemy(3 * TILE_b_e_c + TILE_b_e_c / 2.f, 0.f, FISH));        // șarpe pe sol
    world.addEnemy(Enemy(7 * TILE_b_e_c + TILE_b_e_c / 2.f, 2.5f * TILE_b_e_c, DRONE));   // dronă deasupra

    // Monede
    world.addCoin(Coin(1 * TILE_b_e_c + TILE_b_e_c / 2.f, TILE_b_e_c));        // la 1 tile de sol
    world.addCoin(Coin(5 * TILE_b_e_c + TILE_b_e_c / 2.f, 3.5 * TILE_b_e_c));    // sus pe platformă
    world.addCoin(Coin(9 * TILE_b_e_c + TILE_b_e_c / 2.f, 2 * TILE_b_e_c));    // între jump boxes
    if (!hasGround)
        throw LevelConfigException("World has no ground tiles.");
}

// ----------------- INIT TEXTURES -----------------

void Game::initTextures() {
    // trebuie să ai folderul assets/ în directorul de lucru

    if (!playerTex.loadFromFile("assets/character_yellow_duck.png"))
        throw AssetLoadException("assets/character_yellow_duck.png", "player texture");

    if (!fishTex.loadFromFile("assets/fish_blue_swim_b.png"))
        throw AssetLoadException("assets/fish_blue_swim_b.png", "fish texture");

    if (!droneTex.loadFromFile("assets/saw_rest.png"))
        throw AssetLoadException("assets/saw_rest.png", "drone texture");

    if (!coinTex.loadFromFile("assets/coin64.png"))
        throw AssetLoadException("assets/coin64.png", "coin texture");

    if (!cementTex.loadFromFile("assets/ABCDE64.png"))
        throw AssetLoadException("assets/ABCDE64.png", "cement texture");

    if (!platformTex.loadFromFile("assets/conveyor.png"))
        throw AssetLoadException("assets/conveyor.png", "platform texture");

    if (!jumpLowTex.loadFromFile("assets/block_empty.png"))
        throw AssetLoadException("assets/block_empty.png", "jump_low texture");

    if (!jumpHighTex.loadFromFile("assets/block_empty.png"))
        throw AssetLoadException("assets/block_empty.png", "jump_high texture");

    if (!lavaTex.loadFromFile("assets/lava64.jpg"))
        throw AssetLoadException("assets/lava64.jpg", "lava texture");

    // background opțional: dacă nu se încarcă, nu aruncăm excepție
    if (backgroundTex.loadFromFile("assets/backgroundcyber.png")) {
        hasBackground = true;
        backgroundSprite.setTexture(backgroundTex);
        backgroundSprite.setPosition(0.f, 0.f);
    } else {
        hasBackground = false;
    }
}


// ----------------- INIT SPRITES -----------------

void Game::initSprites() {
    // PLAYER sprite
    objects.push_back(std::make_unique<PlayerSprite>(world.player(), playerTex));

    // ENEMY sprite-uri
    for (auto& e : world.getEnemies()) {
        const sf::Texture& tex = (e.getType() == FISH ? fishTex : droneTex);
        objects.push_back(std::make_unique<EnemySprite>(e, tex));
    }

    // TERRAIN sprite-uri
    for (auto& t : world.getTerrains()) {
        const sf::Texture* tex=nullptr;
        switch (t.getType()) {
            case CEMENT:        tex = &cementTex;     break;
            case PLATFORM:      tex = &platformTex;   break;
            case JUMP_BOX_LOW:  tex = &jumpLowTex;    break;
            case JUMP_BOX_HIGH: tex = &jumpHighTex;   break;
            case LAVA:          tex = &lavaTex;       break;
            default:
                // Dacă apare un tip necunoscut -> excepție clară
                throw AssetLoadException("unknown block type", "TerrainSprite creation");
        }
        objects.push_back(std::make_unique<TerrainSprite>(t, *tex));
    }

    // COIN sprite-uri
    for (auto& c : world.getCoins()) {
        objects.push_back(std::make_unique<CoinSprite>(c, coinTex));
    }

    // Dacă vrei să respecți „layer”-ul, poți sorta vectorul aici după getLayer().
    std::sort(objects.begin(), objects.end(),
              [](const std::unique_ptr<GameObject>& a,
                 const std::unique_ptr<GameObject>& b) {
                  return a->getLayer() < b->getLayer();
              });
}

// ----------------- INPUT -----------------

void Game::handleInput() {


    Player& p = world.player();

    bool left  = sf::Keyboard::isKeyPressed(sf::Keyboard::A);
    bool right = sf::Keyboard::isKeyPressed(sf::Keyboard::D);
    bool jump  = sf::Keyboard::isKeyPressed(sf::Keyboard::Space);

    if (left && !right) {
        p.moveLeft();         // setează vx negativ
    } else if (right && !left) {
        p.moveRight();        // setează vx pozitiv
    } else {
        p.stopHorizontal();     // vx = 0 => mers oprit, sărituri verticale
    }

    if (jump) {
        p.jump();               // sare DOAR dacă onGround == true
    }
}

// ----------------- RUN (GAME LOOP) -----------------

void Game::run() {
    while (window.isOpen()) {
        // evenimente SFML (ieșire, etc.)
        sf::Event event{};
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        float dt = clock.restart().asSeconds();

        // 1) input
        handleInput();

        // 2) update logic player (fizică în pixeli)
        world.player().update(dt);

        // 3) update world (inamici, monede, blocuri, lava)
        world.update();

        // 4) update sprite-uri (poziții / animații grafice)
        for (auto& o : objects)
            o->update();
        // ) animatie specială pentru DRONE folosind dynamic_cast
        for (auto& obj : objects) {
            // downcast de la GameObject* la EnemySprite*
            if (auto* enemySprite = dynamic_cast<EnemySprite*>(obj.get())) {
                Enemy& e = enemySprite->getEnemy();

                if (e.getType() == DRONE) {
                    // parametri de mișcare
                    const float speed   = 120.f;      // pixeli / secundă
                    const float leftLim = 384.f;   // limite aproximative
                    const float rightLim= 640.f;  // alege ce vrei tu

                    // direcția o ținem static (o singură dronă)
                     static float dir = 1.f;  // 1 = dreapta, -1 = stânga

                    // deplasare
                    e.moveX(dir * speed * dt);

                    // întoarcere la capete
                    if (e.getX() < leftLim) {
                        e.setX(leftLim);
                        dir = 1.f;
                    }
                    if (e.getX() > rightLim) {
                        e.setX(rightLim);
                        dir = -1.f;
                    }
                }
            }
        }


        // 5) desen
        window.clear(sf::Color::Black);

        if (hasBackground)
            window.draw(backgroundSprite);   // background înainte de toate

        for (auto& o : objects)
            o->draw(window);

        window.display();

        // (opțional) verificare game over
        if (world.isGameOver()) {
            std::cout << "Game Over!\n";
            window.close();
            return;
        }
    }
}
int Game::getCoinCount() const {
    return world.player().getBitcoinCount();
}
