#ifndef WINDOWFACTORY_H
#define WINDOWFACTORY_H

#include "EndScreen.h"


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