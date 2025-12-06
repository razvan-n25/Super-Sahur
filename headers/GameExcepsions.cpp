#include "GameExcepsions.h"
GameExceptions::GameExceptions(const std::string& msg)
    : std::runtime_error(msg) {}


AssetLoadException::AssetLoadException(const std::string& file,
                                       const std::string& what)
    : GameExceptions("Asset load error (" + what + "): " + file) {}

LevelConfigException::LevelConfigException(const std::string& msg)
    : GameExceptions("Level configuration error: " + msg) {}

MenuInputException::MenuInputException(const std::string& msg)
    : GameExceptions("Menu input error: " + msg) {}