//
// Created by razva on 29/11/2025.
//

#ifndef OOP_MENU_H
#define OOP_MENU_H
#include <iostream>

class Menu {
private:
    int choice;
    bool running;

public:
    Menu();
    Menu(const Menu& other);
    Menu& operator=(const Menu& other);
    ~Menu();

    void showStart();
    static void showInstructions();
    void showEnd(bool win, int coins);

    [[nodiscard]] int getChoice() const;
    [[nodiscard]] bool isRunning() const;

    friend std::ostream& operator<<(std::ostream& os, const Menu& m);
};
#endif //OOP_MENU_H