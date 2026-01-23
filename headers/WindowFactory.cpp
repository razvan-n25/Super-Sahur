#include "WindowFactory.h"

EndScreen* CyberUIFactory::createEndResult(const std::string& msg, sf::Texture& tex) {
    if (msg.find("WIN") != std::string::npos || msg.find("VICTORIE") != std::string::npos) {
        return new WinScreen(msg, tex);
    } else {
        return new LossScreen(msg, tex);
    }
}