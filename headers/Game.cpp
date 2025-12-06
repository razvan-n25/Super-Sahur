#include "Game.h"
#include <iostream>
#include "GameExcepsions.h"

Game::Game()
    : window(sf::VideoMode(1280, 720), "Cyber Platform"),
      world(Player(32.f, 0.f, 5))
{
    window.setFramerateLimit(180);
    view = window.getDefaultView();
    initWorld();
    initTextures();
    initSprites();
}

void Game::initWorld() {
    int hasGround = 0;

    for (int i = 0; i < 7; ++i) {
        float x = 32.f + i * 64.f;
        Terrain t(x, 0.f, CEMENT);
        world.addTerrain(t);
        hasGround++;
    }

    world.addTerrain(Terrain(160.f, 32.f, JUMP_BOX_LOW));
    world.addCoin(Coin(160.f, 120.f));
    world.addEnemy(Enemy(230.f, 0.f, FISH));

    for (int i = 0; i < 5; ++i) {
        float x = 32.f + (7 + i) * 64.f;
        Terrain t(x, -64.f, CEMENT);
        world.addTerrain(t);
        hasGround++;
    }

    for (int i = 0; i < 4; ++i) {
        float x = 32.f + (8 + i) * 64.f;
        world.addTerrain(Terrain(x, 192.f, CEMENT));
    }

    {
        float baseX = 380.f;
        float baseY = 64.f;
        world.addTerrain(Terrain(baseX - 64.f, baseY, JUMP_BOX_LOW));
        world.addTerrain(Terrain(baseX,baseY, JUMP_BOX_LOW));
        world.addTerrain(Terrain(baseX + 64.f, baseY, JUMP_BOX_LOW));
        world.addTerrain(Terrain(baseX - 32.f, baseY + 64.f, JUMP_BOX_LOW));
        world.addTerrain(Terrain(baseX + 32.f, baseY + 64.f, JUMP_BOX_LOW));
        world.addTerrain(Terrain(baseX, baseY + 128.f, JUMP_BOX_LOW));

    }

    for (int i = 0; i < 3; ++i) {
        float x = 32.f + (12 + i) * 64.f;
        Terrain t(x, 0.f, CEMENT);
        world.addTerrain(t);
        hasGround++;
    }

    world.addTerrain(Terrain(900.f, 0.f, LAVA));
    for (int i = 0; i < 7; ++i) {
        world.addTerrain(Terrain(928.f + i * 64.f, 0.f, LAVA));
    }

    world.addTerrain(Terrain(820.f,  64.f, PLATFORM));
    world.addTerrain(Terrain(980.f, 128.f, PLATFORM));
    world.addTerrain(Terrain(1140.f,128.f, PLATFORM));
    world.addTerrain(Terrain(1312.f,64.f,  PLATFORM));

    world.addEnemy(Enemy(760.f, 0.f, FISH));   // în stânga lava
    world.addEnemy(Enemy(1360.f, 0.f, FISH));  // după lava

    world.addCoin(Coin(980.f, 180.f));
    world.addCoin(Coin(1140.f, 180.f));
    world.addCoin(Coin(1300.f, 120.f));

    for (int i = 0; i < 5; ++i) {
        float x = 1312.f + i * 64.f;
        Terrain t(x, 0.f, CEMENT);
        world.addTerrain(t);
        hasGround++;
    }

    world.addTerrain(Terrain(1450.f,  64.f, PLATFORM));
    world.addTerrain(Terrain(1520.f, 128.f, PLATFORM));
    world.addTerrain(Terrain(1590.f, 192.f, PLATFORM));
    world.addTerrain(Terrain(1660.f, 256.f, PLATFORM));

    world.addEnemy(Enemy(1660.f, 300.f, DRONE));

    world.addCoin(Coin(1450.f, 110.f));
    world.addCoin(Coin(1520.f, 170.f));
    world.addCoin(Coin(1590.f, 230.f));
    world.addCoin(Coin(1660.f, 290.f));

    for (float x = 1750.f; x <= 1950.f; x += 64.f) {
        Terrain t(x, 0.f, CEMENT);
        world.addTerrain(t);
        hasGround++;
    }

    world.addTerrain(Terrain(1780.f, 192.f, CEMENT));
    world.addTerrain(Terrain(1844.f, 192.f, CEMENT));
    world.addTerrain(Terrain(1908.f, 192.f, CEMENT));

    world.addTerrain(Terrain(1760.f, 64.f,  JUMP_BOX_LOW));
    world.addTerrain(Terrain(1840.f, 64.f,  JUMP_BOX_HIGH));
    world.addTerrain(Terrain(1920.f, 128.f, JUMP_BOX_HIGH));

    world.addEnemy(Enemy(1720.f, 0.f, FISH));
    world.addEnemy(Enemy(1800.f, 0.f, FISH));
    world.addEnemy(Enemy(1880.f, 0.f, FISH));

    world.addEnemy(Enemy(1908.f, 270.f, DRONE));

    if (hasGround == 0)
        throw LevelConfigException("World has no CEMENT ground tiles.");
}

void Game::initTextures() {

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

    if (backgroundTex.loadFromFile("assets/backgroundcyber.png")) {
        hasBackground = true;
        backgroundSprite.setTexture(backgroundTex);
        backgroundSprite.setPosition(0.f, 0.f);
    } else {
        hasBackground = false;
    }
}

void Game::initSprites() {
    objects.push_back(std::make_unique<PlayerSprite>(world.player(), playerTex));

    for (auto& e : world.getEnemies()) {
        const sf::Texture& tex = (e.getType() == FISH ? fishTex : droneTex);
        objects.push_back(std::make_unique<EnemySprite>(e, tex));
    }

    for (auto& t : world.getTerrains()) {
        const sf::Texture* tex=nullptr;
        switch (t.getType()) {
            case CEMENT:        tex = &cementTex;     break;
            case PLATFORM:      tex = &platformTex;   break;
            case JUMP_BOX_LOW:  tex = &jumpLowTex;    break;
            case JUMP_BOX_HIGH: tex = &jumpHighTex;   break;
            case LAVA:          tex = &lavaTex;       break;
            default:
                throw AssetLoadException("unknown block type", "TerrainSprite creation");
        }
        objects.push_back(std::make_unique<TerrainSprite>(t, *tex));
    }

    coinPrefab = std::make_unique<CoinSprite>(nullptr, coinTex);
    for (auto& c : world.getCoins()) {
        auto sprite = coinPrefab->clone();
        auto* cs = dynamic_cast<CoinSprite*>(sprite.get());
        if (cs) {
            cs->attachCoin(&c);
        }
        objects.push_back(std::move(sprite));
    }
    // Dacă vrei să respecți „layer”-ul, poți sorta vectorul aici după getLayer().
    std::sort(objects.begin(), objects.end(),
              [](const std::unique_ptr<GameObject>& a,
                 const std::unique_ptr<GameObject>& b) {
                  return a->getLayer() < b->getLayer();
              });
}

void Game::handleInput() {

    Player& p = world.player();
    bool left  = sf::Keyboard::isKeyPressed(sf::Keyboard::A);
    bool right = sf::Keyboard::isKeyPressed(sf::Keyboard::D);
    bool jump  = sf::Keyboard::isKeyPressed(sf::Keyboard::Space);

    if (left && !right) {
        p.moveLeft();
    } else if (right && !left) {
        p.moveRight();
    } else {
        p.stopHorizontal();
    }
    if (jump) {
        p.jump();
    }
}

void Game::run() {
    while (window.isOpen()) {
        sf::Event event{};
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        float dt = clock.restart().asSeconds();

        handleInput();

        world.player().update(dt);

        world.update();

        {
            static bool spawnedCoins = false;

            if (!spawnedCoins && world.player().getX() > 1680.f) {
                spawnedCoins = true;

                const float xs[] = { 1700.f, 1920.f};
                const float ys[] = { 130.f,  220.f};
                for (int i = 0; i < 2; ++i) {
                    world.addCoin(Coin(xs[i], ys[i]));
                    Coin& newCoin = world.getCoins().back();
                    auto spriteClone = coinPrefab->clone();
                    auto* cs = dynamic_cast<CoinSprite*>(spriteClone.get());
                    if (cs) {
                        cs->attachCoin(&newCoin);
                    }
                    objects.push_back(std::move(spriteClone));
                }
            }
        }
        for (auto& o : objects)
            o->update();
        float camX = world.player().getX();
        float halfW = view.getSize().x / 2.f;
        if (camX < halfW) camX = halfW;
        view.setCenter(camX, window.getSize().y / 2.f);
        // aplici view-ul pe fereastră
        window.setView(view);
        for (auto& obj : objects) {
            if (auto* enemySprite = dynamic_cast<EnemySprite*>(obj.get())) {
                Enemy& e = enemySprite->getEnemy();
                if (e.getType() == DRONE) {
                    const float speed   = 120.f;
                    const float leftLim = 384.f;
                    const float rightLim= 640.f;
                     static float dir = 1.f;
                    e.moveX(dir * speed * dt);
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

        window.clear(sf::Color::Black);
        if (hasBackground) {
            window.setView(window.getDefaultView());
            window.draw(backgroundSprite);
        }
        window.setView(view);
        for (const auto& o : objects)
            o->draw(window);
        window.display();
        if (world.isGameOver()) {
            std::cout << "Game Over!\n";
            window.close();
            return;
        }
        if (world.isLevelCompleted()) {
            std::cout << "You Win!\n";
            window.close();
            return;
        }
    }
}
int Game::getCoinCount() const {
    return world.player().getBitcoinCount();
}
bool Game :: didPlayerWin() const { return world.isLevelCompleted(); }


