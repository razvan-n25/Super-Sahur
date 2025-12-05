#include "Menu.h"
#include <string>
#include "GameExcepsions.h"
Menu::Menu() : choice(0), running(true) {}

Menu::Menu(const Menu& other)
    : choice(other.choice), running(other.running) {}

Menu& Menu::operator=(const Menu& other) {
    if (this != &other) {
        choice = other.choice;
        running = other.running;
    }
    return *this;
}

Menu::~Menu() = default;

void Menu::showStart() {
    std::string s;
    std::cout << "=========================\n";
    std::cout << "       CYBER PLATFORM    \n";
    std::cout << "=========================\n";
    std::cout << "1. Start Game\n";
    std::cout << "2. Instructions\n";
    std::cout << "3. Exit\n";
    std::cout << "=========================\n";
    while (true) {
        std::cout << "Choice: ";
        if (!(std::cin >> s)) {
            throw MenuInputException("Failed to read input in showStart()");
        }

        if (s == "1" || s == "2" || s == "3") {
            choice = s[0] - '0';
            return;
        }

        throw MenuInputException("Invalid input in showStart()");
    }
}

void Menu::showInstructions() {
    std::cout << "\nCommands:\n";
    std::cout << "d  - move forward\n";
    std::cout << "a  - move backward\n";
    std::cout << "space  - jump up\n";
}

void Menu::showEnd(int coins) {
    std::string s;
    std::cout << "Bitcoins collected: " << coins << "\n";
    std::cout << "=========================\n";
    std::cout << "1. Play Again\n";
    std::cout << "2. Exit\n";
    while (true) {
        std::cout << "Choice: ";
        if (!(std::cin >> s)) {
            throw MenuInputException("Failed to read input in showEnd()");
        }

        if (s == "1" || s == "2") {
            choice = s[0] - '0';
            if (choice == 2) running = false;
            return;
        }

        throw MenuInputException("Invalid input in showEnd()");
    }
}

int Menu::getChoice() const { return choice; }
bool Menu::isRunning() const { return running; }

std::ostream& operator<<(std::ostream& os, const Menu& m) {
    os << "Menu(choice=" << m.choice
       << ", running=" << (m.running ? "true" : "false") << ")";
    return os;
}
