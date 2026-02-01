//
// Created by razva on 23/01/2026.
//

#ifndef OOP_SETTINGSMANAGER_H
#define OOP_SETTINGSMANAGER_H

#include <SFML/Graphics.hpp>
class SettingsManager {
private:
    SettingsManager();
    sf::Font mainFont;
    SettingsManager(const SettingsManager&) = delete;
    SettingsManager& operator=(const SettingsManager&) = delete;
public:
    static SettingsManager& getInstance();
    sf::Font& getFont();
};
#endif //OOP_SETTINGSMANAGER_H