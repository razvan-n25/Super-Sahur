#ifndef OOP_GAMEEXCEPTIONS_H
#define OOP_GAMEEXCEPTIONS_H

#include <stdexcept>
#include <string>

// Baza: derivată din std::runtime_error (=> std::exception)
class GameExceptions : public std::runtime_error {
public:
    explicit GameExceptions(const std::string& msg);
    ~GameExceptions() override = default;

};

class AssetLoadException : public GameExceptions {
public:
    AssetLoadException(const std::string& file, const std::string& what);
};

class LevelConfigException : public GameExceptions {
public:
    explicit LevelConfigException(const std::string& msg);
};

class MenuInputException : public GameExceptions {
public:
    explicit MenuInputException(const std::string& msg);
};

#endif // OOP_GAMEEXCEPTIONS_H
