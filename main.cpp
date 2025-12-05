#include <iostream>
#include <exception>

#include "Menu.h"
#include "Game.h"
#include "GameExcepsions.h"
int main() {
    try {
        Menu menu;

        while (menu.isRunning()) {
            menu.showStart();

            if (menu.getChoice()== 1) {
                bool playing=true;
                while (playing) {
                    Game game;
                    game.run();
                    int coins  = game.getCoinCount();          // numărul de monede adunate
                    menu.showEnd(coins);
                    if (menu.getChoice()==1)
                        continue;
                    else
                        playing=false;
                }
            } else if (menu.getChoice()== 2) {
                Menu::showInstructions();
            } else { // 3 = Exit
                break;
            }
        }

        return 0;
    }
    catch (const GameException& e) {
        std::cerr << "Game error: " << e.what() << "\n";
        return 1;
    }
    catch (const std::exception& e) {
        std::cerr << "Fatal error: " << e.what() << "\n";
        return 1;
    } catch (...) {
        std::cerr << "Unknown fatal error.\n";
        return 1;
    }
}
