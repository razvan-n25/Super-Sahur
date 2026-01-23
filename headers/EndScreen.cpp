#include "EndScreen.h"


WinScreen::WinScreen(const std::string& msg, sf::Texture& tex)
    : popup("VICTORIE", sf::Sprite(tex)) {
    messageText.setFont(SettingsManager::getInstance().getFont()); // Singleton
    messageText.setString(msg);
    messageText.setFillColor(sf::Color::Green);
    messageText.setCharacterSize(40);
    messageText.setPosition(310, 250); // Poziție vizibilă
}

void WinScreen::show() {
    popup.displayWithOverlay(messageText); // Desenează și textul!
}


LossScreen::LossScreen(const std::string& msg, sf::Texture& tex)
    : popup("INFRINGERE", sf::Sprite(tex)) {
    messageText.setFont(SettingsManager::getInstance().getFont());
    messageText.setString(msg);
    messageText.setFillColor(sf::Color::Red);
    messageText.setCharacterSize(40);
    messageText.setPosition(270, 250);
}

void LossScreen::show() {
    popup.displayWithOverlay(messageText);
}