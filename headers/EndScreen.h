#ifndef ENDSCREEN_H
#define ENDSCREEN_H

#include <SFML/Graphics.hpp>
#include <string>
#include "PopupBox.h"
//obiectele ce vor fi folosite de Abstract Factory
class EndScreen {
public:
    virtual ~EndScreen() = default;
    virtual void show() = 0; // Metoda virtuală pură
};
class WinScreen : public EndScreen {
private:
    PopupBox<sf::Sprite> popup;
    sf::Text messageText;
public:
    WinScreen(const std::string& msg, sf::Texture& tex);
    void show() override;
};
class LossScreen : public EndScreen {
private:
    PopupBox<sf::Sprite> popup;
    sf::Text messageText;
public:
    LossScreen(const std::string& msg, sf::Texture& tex);
    void show() override;
};
#endif