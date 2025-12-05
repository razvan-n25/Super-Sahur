#ifndef OOP_GAMEEXCEPTIONS_H
#define OOP_GAMEEXCEPTIONS_H

#include <stdexcept>
#include <string>

// Baza: derivată din std::runtime_error (=> std::exception)
class GameException : public std::runtime_error {
public:
    explicit GameException(const std::string& msg);
    ~GameException() override = default;

};

// 1) Eroare la încărcarea resurselor (texturi, fonturi, etc.)
class AssetLoadException : public GameException {
public:
    AssetLoadException(const std::string& file, const std::string& what);
};

// 2) Eroare de configurare a nivelului (world / level)
class LevelConfigException : public GameException {
public:
    explicit LevelConfigException(const std::string& msg);
};

// 3) Eroare de input în meniuri (citire din cin)
class MenuInputException : public GameException {
public:
    explicit MenuInputException(const std::string& msg);
};

#endif // OOP_GAMEEXCEPTIONS_H
