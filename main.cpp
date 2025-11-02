#include<iostream>
#include<cmath>
#include<vector>
enum HazardType {
    SNAKE,
    DRONE
};
enum CyberBlock {
    CEMENT, PLATFORM, JUMP_BOX_LOW, JUMP_BOX_HIGH, LAVA
};
class Player {
    friend class World;
private:
    int hearts;
    int bitcoins=0;
    float x,y;
    float jump;
    float height;
    void moveForward(float step=0.5f) {
        x+=step;
        if (y>0.0f) y=0.0f;
    }
    void moveBackward(float step=0.5f) {
        x=std::max(0.0f,x-step);
        if (y>0.0f) y=0.0f;
    }
    void jumpUp() {
        y=jump;
        std::cout<<"You jumped up to height"<< y <<"!\n";
    }
    void jumpForward(float step=0.5f) {
        x+=step;
        y=jump;
        std::cout<<"You jumped forward to ("<< x<<","<< y<<")!\n";
    }
    void jumpBackward(float step=0.5f) {
        x-=step;
        y=jump;
        std::cout<< "You jumped backward to ("<<x<<","<< y<<")!\n";
    }
    void addBitcoin(int n=1) {
        bitcoins+=n;
    }
    void takeDamage() {
        if (hearts>0) {
            hearts--;
            std::cout<< "-lost one heart ("<< hearts<< "left)\n";
        }
        else
            std::cout<< "You died\n";
    }
public:
    Player(): hearts(5), x(0.0f), y(0.0f), jump(2.5f), height(1.7f){}
    Player(float in_x, float in_y, int in_hearts) : hearts(in_hearts), x(in_x), y(in_y), jump(2.5f), height(1.7f){}
    Player(const Player&other) : hearts(other.hearts), x(other.x), y(other.y), jump(other.jump), height(other.height){}
    Player& operator=(const Player& other) {
        if (this!=&other) {
            hearts=other.hearts;
            bitcoins=other.bitcoins;
            x=other.x;
            y=other.y;
            jump=other.jump;
            height=other.height;
        }
        return *this;
    }
    ~Player()=default;
    [[nodiscard]] float getX() const{return x;}
    [[nodiscard]] float getY() const{return y;}
    [[nodiscard]] float getHeight() const{return height;}
    [[nodiscard]] int getHearts() const{return hearts;}
    [[nodiscard]] int getBitcoinCount() const{return bitcoins;}
    friend std::ostream& operator<<(std::ostream& os, const Player& a) {
        os<< "Player(x="<< a.x << ", y="<< a.y
        << ", hearts="<<a.hearts
        << ", jump="<<a.jump
        << ", height="<<a.height
        << ", bitcoins="<<a.bitcoins<< ")";
        return os;
    }
};
class Enemy {
private:
    HazardType type;
    float x,y;
    bool alive;
public:
    Enemy(float in_x, float in_y, HazardType in_type): type(in_type), x(in_x), y(in_y), alive(true){}
    Enemy(const Enemy& other): type(other.type), x(other.x), y(other.y), alive(other.alive){}
    Enemy& operator=(const Enemy& other) {
        if (this!=&other) {
            type=other.type;
            x=other.x;
            y=other.y;
            alive=other.alive;
        }
        return *this;
    }
    ~Enemy()=default;
    [[nodiscard]] float getX() const{return x;}
    [[nodiscard]] float getY() const{return y;}
    [[nodiscard]] HazardType getType() const {return type;}
    [[nodiscard]] bool isAlive() const {return alive;}
    void disable() {alive=false;}
    friend std::ostream& operator<<(std::ostream& os, const Enemy& e){
        os<<"Enemy(type="<<(e.type==SNAKE ? "SNAKE" : "DRONE")
        << ", x="<<e.x<<", y="<<e.y
        << ", alive="<<(e.alive ? "true" : "false")<< ")";
        return os;
    }
};
class Terrain {
private:
    float x, y;
    CyberBlock type;
public:
    explicit Terrain(float in_x, float in_y, CyberBlock in_type): x(in_x), y(in_y), type(in_type) {}
    Terrain(const Terrain& other): x(other.x), y(other.y), type(other.type) {}
    Terrain& operator=(const Terrain& other) {
        if (this!=&other) {
            x=other.x;
            y=other.y;
            type=other.type;
        }
        return *this;
    }
    ~Terrain()=default;
    [[nodiscard]] bool isHazard() const {return (type==LAVA);}
    [[nodiscard]] float getX() const {return x;}
    [[nodiscard]] float getY() const {return y;}
    [[nodiscard]] CyberBlock getType() const {return type;}
    friend std::ostream& operator<<(std::ostream& os, const Terrain& t) {
        os<< "Terrain(type=";
        switch (t.type) {
            case CEMENT: os<<"CEMENT"; break;
            case LAVA: os<<"LAVA"; break;
            case PLATFORM : os<<"PLATFORM"; break;
            case JUMP_BOX_LOW: os<<"JUMP_BOX_LOW"; break;
            case JUMP_BOX_HIGH: os<<"JUMP_BOX_HIGH"; break;
        }
        os<< ", x="<< t.x<<", y="<< t.y<< ")";
        return os;
    }
};
class Coin {
private:
    float x,y;
    bool collected;
public:
    explicit Coin(float in_x, float in_y): x(in_x), y(in_y), collected(false){}
    Coin(const Coin&other): x(other.x), y(other.y), collected(other.collected){}
    Coin& operator=(const Coin& other) {
        if (this!=&other) {
            x=other.x;
            y=other.y;
            collected=other.collected;
        }
        return *this;
    }
    ~Coin()=default;
    void collect() {collected=true;}
    [[nodiscard]] bool isCollected() const {return collected;}
    [[nodiscard]] float getX() const {return x;}
    [[nodiscard]] float getY() const {return y;}
    friend std::ostream& operator<<(std::ostream& os, const Coin& c) {
        os<<"Coin(x="<<c.x<<", y="<<c.y
        <<", collected="<<(c.collected ? "true" : "false")<<")";
        return os;
    }
};
class World {
private:
    Player player_;
    std::vector<Enemy>enemies_;
    std::vector<Terrain> terrains_;
    std::vector<Coin> coins_;
    void ReportStandingOnBlock() {
        const float epsX=0.25f;
        for (const auto&t:terrains_) {
            if (t.isHazard()) {
                bool sameX=std::fabs(player_.getX()-t.getX())<=epsX;
                bool on_or_up=player_.getY()<=t.getY();
                if (sameX && on_or_up) {
                    std::cout<<"You stepped in LAVA!\n";
                    std::cout<<"Instant death! You failed!\n";
                    while (player_.getHearts()>0) player_.takeDamage();
                    return;
                }
                continue;
            }
            bool sameX= std::fabs(player_.getX()-t.getX())<=epsX;
            bool above=player_.getY()>t.getY();
            bool sameLevel=player_.getY()<=t.getY();
            if (sameX && above) {
                const char* typeName="";
                switch (t.getType()) {
                    case CEMENT: typeName="CEMENT"; break;
                    case PLATFORM: typeName="PLATFORM"; break;
                    case JUMP_BOX_LOW: typeName="JUMP_BOX_LOW"; break;
                    case JUMP_BOX_HIGH: typeName="JUMP_BOX_HIGH"; break;
                    case LAVA :  typeName="LAVA"; break;
                }
                std::cout<<"Sunt pe bloc: "<<typeName<<" la x="<<t.getX()<<"\n";
            }
            else if (sameX && sameLevel)
                std::cout<< "Bloc in fata la x="<<t.getX()<<" trebuie sa sari ca sa poti trece!\n";
        }
    }
    void checkEnemies() {
        const float epsX=0.25f;
        const float epsHead=0.5f;
        for (auto&e:enemies_) {
            if (!e.isAlive()) continue;
            if (e.getType()==SNAKE) {
                bool touching=std::fabs(player_.getX()-e.getX())<=epsX && std::fabs(player_.getY()-e.getY())<=epsHead;
                if (touching) {
                    player_.takeDamage();
                    std::cout<<"You touched a SNAKE!\n";
                    e.disable();
                }
            } else {
                float headY=player_.getY()+player_.getHeight();
                bool nearX=std::fabs(player_.getX()-e.getX())<=epsX;
                if (nearX&&std::fabs(e.getY()-headY)<=epsHead) {
                    player_.takeDamage();
                    std::cout<<"Drone hit your HEAD!\n";
                    e.disable();
                }else if (nearX && e.getY()>headY+epsHead)
                    std::cout<<"Drone is above your head.\n";
            }
        }
    }
    void collectCoins() {
        for (auto& c:coins_) {
            if (c.isCollected()) continue;
            bool nearX=std::fabs(player_.getX()-c.getX())<=0.25f;
            float headY=player_.getY()+player_.getHeight();
            bool withinHeight=(c.getY()>=player_.getY()&&c.getY()<=headY);
            if (nearX && withinHeight) {
                c.collect();
                player_.addBitcoin();
                std::cout<<"+1 bitcoin collected!\n";
            }
        }
    }
public:
    explicit World(const Player& p): player_(p){}
    World(const World& other): player_(other.player_), enemies_(other.enemies_), terrains_(other.terrains_), coins_(other.coins_){}
    World& operator=(const World& other) {
        if (this!=&other) {
            player_=other.player_;
            terrains_=other.terrains_;
            coins_=other.coins_;
            enemies_=other.enemies_;
        }
        return *this;
    }
    ~World()=default;
    void addTerrain(const Terrain& t) {terrains_.push_back(t);}
    void addCoin(const Coin& c) {coins_.push_back(c);}
    void addEnemy(const Enemy& e) {enemies_.push_back(e);}
    Player& player(){return player_;}
    void update() {
        checkEnemies();
        collectCoins();
        ReportStandingOnBlock();
    }
    [[nodiscard]] bool isGameOver() const {return player_.getHearts()<=0;}
    friend std::ostream& operator<<(std::ostream& os, const World& w) {
        os<< "World:\n"<<w.player_<<"\n";
        for (const auto& e:w.enemies_) os<<e<<"\n";
        for (const auto& t:w.terrains_) os<<t<<"\n";
        for (const auto& c:w.coins_) os<<c<<"\n";
        return os;
    }
    void handleCommand(const std::string& tasta) {
        if (tasta=="f") player_.moveForward();
        else if (tasta=="b") player_.moveBackward();
        else if (tasta=="j") player_.jumpUp();
        else if (tasta=="fj") player_.jumpForward();
        else if (tasta=="bj") player_.jumpBackward();
        else std::cout<<"Invalid command.\n";
    }
};
class Menu {
private:
    int choice;
    bool running;
public:
    Menu(): choice(0), running(true){}
    Menu(const Menu& other): choice(other.choice), running(other.running){}
    Menu& operator=(const Menu& other) {
        if (this!=&other) {
            choice=other.choice;
            running=other.running;
        }
        return *this;
    }
    ~Menu()=default;
    void showStart() {
        std:: string s;
        std::cout << "=========================\n";
        std::cout << "       CYBER PLATFORM    \n";
        std::cout << "=========================\n";
        std::cout << "1. Start Game\n";
        std::cout << "2. Instructions\n";
        std::cout << "3. Exit\n";
        std::cout << "=========================\n";
        while (true) {
            std::cout << "Choice: ";
            std::cin>>s;
            if (s == "1" || s == "2" || s == "3") {
                choice = s[0] - '0';
                break; // ieșim din buclă dacă e valid
            }
            std::cout << "Invalid input. Enter 1, 2, or 3.\n";
        }

    }
    static void showInstructions() {
        std::cout<< "\nCommands:\n";
        std::cout<<"f - move forward\n";
        std::cout<<"b - move backward\n";
        std::cout<<"j - jump up\n";
        std::cout<<"fj - jump foerward\n";
        std::cout<<"bj - jump backward\n";
        std::cout<<"q - quit\n";
    }
    void showEnd(bool win, int coins) {
        std::string s;
        std::cout<<"\n=========================\n";
        std::cout<<(win ? "You Win!\n" : "You Failed!\n");
        std::cout<< "Bitcoins collected: "<<coins<<"\n";
        std::cout<<"=========================\n";
        std::cout<<"1. Play Again\n";
        std::cout<<"2. Exit\n";
        while (true) {
            std::cout << "Choice: ";
            std::cin>>s;
            if (s == "1" || s == "2") {
                choice = s[0] - '0';
                break;
            }
            std::cout << "Invalid input. Enter 1 or 2.\n";
        }

        if (choice == 2) running = false;
    }
    [[nodiscard]] int getChoice() const {return choice;}
    [[nodiscard]] bool isRunning() const {return running;}
    friend std::ostream& operator<<(std::ostream& os, const Menu& m) {
        os<<"Menu(choice="<<m.choice<<", running="<<(m.running? "true" : "false")<<")";
        return os;
    }
};
int main() {
    Menu menu;;
    while (menu.isRunning()) {
        menu.showStart();
        if (menu.getChoice()==3) break;
        if (menu.getChoice()==2) {
            Menu::showInstructions();
            continue;
        }
        Player hero(0.0f, 0.0f, 5);
        World world(hero);
        world.addTerrain(Terrain(0.0f,0.0f,CEMENT));
        world.addTerrain(Terrain(5.0f, 0.0f, LAVA));
        world.addTerrain(Terrain(3.0f, 0.0f, PLATFORM));
        world.addTerrain(Terrain(4.0f, 2.0f, JUMP_BOX_HIGH));
        world.addCoin(Coin(1.0f, 0.5f));
        world.addCoin(Coin(2.5f, 1.5f));
        world.addEnemy(Enemy(3.5f, 0.0f, SNAKE));
        world.addEnemy(Enemy(4.0f, 1.5f, DRONE));
        bool levelRunning=true;
        while (levelRunning) {
            std::cout<<"\nPos: ("<<world.player().getX()<<", "<<world.player().getY()
            << ") | Hearts: " << world.player().getHearts()
                      << " | BTC: " << world.player().getBitcoinCount() << "\n";
            std::cout << "[f] [b] [j] [fj] [bj] [q] > ";
            std::string cmd;
            std::cin >> cmd;
            if (cmd=="q") break;
            world.handleCommand(cmd);
            world.update();
            if (world.isGameOver()) {
                std::cout<<"Player has died!\n";
                levelRunning = false;
            }
            if (world.player().getX()>6.0f) {
                std::cout<<"You reached the end!\n";
                levelRunning = false;
            }
        }
        bool win=(world.player().getX()>6.0f&&world.player().getHearts()>0);
        menu.showEnd(win, world.player().getBitcoinCount());
    }
    std::cout<<"Game closed.\n";
    return 0;
}