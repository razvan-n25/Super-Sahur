#ifndef WINDOWFACTORY_H
#define WINDOWFACTORY_H

#include "EndScreen.h"

//Abstract Factory care creeaza screenurile de loss si win, cu pointer catre obiectele de tip EndScreen
class WindowFactory {
public:
    virtual ~WindowFactory() = default;
    virtual EndScreen* createEndResult(const std::string& msg, sf::Texture& tex) = 0;
};
class CyberUIFactory : public WindowFactory {
public:
    EndScreen* createEndResult(const std::string& msg, sf::Texture& tex) override;
};
#endif