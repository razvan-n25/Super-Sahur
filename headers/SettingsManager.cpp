//
// Created by razva on 23/01/2026.
//

#include "SettingsManager.h"
#include "GameExcepsions.h"
SettingsManager& SettingsManager::getInstance() {
    static SettingsManager instance;
    return instance;
}
SettingsManager::SettingsManager() {
    if (!mainFont.loadFromFile("C:/Windows/Fonts/arial.ttf")) {
        throw AssetLoadException("System Arial", "Singleton Font");
    }
}
sf::Font& SettingsManager::getFont() { return mainFont; }