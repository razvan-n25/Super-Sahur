//
// Created by razva on 23/01/2026.
//
#ifndef OOP_POPUPBOX_H
#define OOP_POPUPBOX_H
#include <SFML/Graphics.hpp>

template <typename T>
class PopupBox {
private:
    std::string title;
    T content;
public:
    PopupBox(const std::string& t, const T& item)
        : title(t), content(item) {}
    void display() {
        sf::RenderWindow win(sf::VideoMode(400, 200), title);
        while (win.isOpen()) {
            sf::Event event;
            while (win.pollEvent(event)) {
                if (event.type == sf::Event::Closed) win.close();
            }
            win.clear(sf::Color(40, 44, 52));
            win.draw(content);
            win.display();
        }
    }

    void displayWithOverlay(const sf::Text& extraText) {
        sf::RenderWindow window(sf::VideoMode(800, 600), title);
        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) window.close();
            }
            window.clear();
            window.draw(content);
            window.draw(extraText);
            window.display();
        }
    }
};
#endif //OOP_POPUPBOX_H