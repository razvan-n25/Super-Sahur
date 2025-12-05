#include "GameExcepsions.h"
GameException::GameException(const std::string& msg)
    : std::runtime_error(msg) {}

// ----------------- AssetLoadException -----------------

AssetLoadException::AssetLoadException(const std::string& file,
                                       const std::string& what)
    : GameException("Asset load error (" + what + "): " + file) {}

// ----------------- LevelConfigException -----------------

LevelConfigException::LevelConfigException(const std::string& msg)
    : GameException("Level configuration error: " + msg) {}

// ----------------- MenuInputException -----------------

MenuInputException::MenuInputException(const std::string& msg)
    : GameException("Menu input error: " + msg) {}