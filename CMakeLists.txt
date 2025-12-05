cmake_minimum_required(VERSION 3.26)

# NOTE: update executable name in .github/workflows/cmake.yml:25 when changing executable name in this file
set(MAIN_PROJECT_NAME "oop")
set(MAIN_EXECUTABLE_NAME "${MAIN_PROJECT_NAME}")

project(${MAIN_PROJECT_NAME} LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(cmake/Options.cmake)
include(cmake/CompilerFlags.cmake)
include(cmake/CopyHelper.cmake)

###############################################################################
# SFML: pe Windows folosim instalarea ta (SFML_DIR),
#        pe Linux/macOS folosim FetchContent (pt. CI / alte mașini)
###############################################################################

if (WIN32)
    # aici pui calea spre instalarea TA de SFML
    set(SFML_DIR "D:/sfml/SFML-2.6.2/lib/cmake/SFML" CACHE PATH "Path to SFMLConfig.cmake")
    find_package(SFML 2.6 COMPONENTS system window graphics audio REQUIRED)
else()
    include(FetchContent)

    set(FETCHCONTENT_QUIET OFF)
    set(FETCHCONTENT_UPDATES_DISCONNECTED ON)

    FetchContent_Declare(
            SFML
            GIT_REPOSITORY https://github.com/SFML/SFML.git
            GIT_TAG        2.6.2
            GIT_SHALLOW    1
    )

    FetchContent_MakeAvailable(SFML)
endif()

###############################################################################
# Executabilul principal
###############################################################################

add_executable(${MAIN_EXECUTABLE_NAME}
        main.cpp
        headers/Player.cpp
        headers/Player.h
        headers/Enemy.cpp
        headers/Enemy.h
        headers/Blocuri_Inamici.h
        headers/Terrain.cpp
        headers/Terrain.h
        headers/Coin.cpp
        headers/Coin.h
        headers/World.cpp
        headers/World.h
        headers/Menu.cpp
        headers/Menu.h
        headers/GameObject.cpp
        headers/GameObject.h
        headers/PlayerSprite.cpp
        headers/PlayerSprite.h
        headers/EnemySprite.cpp
        headers/EnemySprite.h
        headers/TerrainSprite.cpp
        headers/TerrainSprite.h
        headers/CoinSprite.cpp
        headers/CoinSprite.h
        headers/Game.cpp
        headers/Game.h
        headers/GameExcepsions.cpp
        headers/GameExcepsions.h
)

target_include_directories(${MAIN_EXECUTABLE_NAME} PRIVATE headers)

target_link_libraries(${MAIN_EXECUTABLE_NAME}
        sfml-system
        sfml-window
        sfml-graphics
        sfml-audio
)

# flags / sanitizers
set_compiler_flags(RUN_SANITIZERS TRUE TARGET_NAMES ${MAIN_EXECUTABLE_NAME})

###############################################################################
# Instalare / copiere fișiere
###############################################################################

install(TARGETS ${MAIN_EXECUTABLE_NAME} DESTINATION ${DESTINATION_DIR})
if(APPLE)
    install(FILES launcher.command DESTINATION ${DESTINATION_DIR})
endif()

copy_files(FILES tastatura.txt COPY_TO_DESTINATION TARGET_NAME ${MAIN_EXECUTABLE_NAME})
copy_files(DIRECTORY assets COPY_TO_DESTINATION TARGET_NAME ${MAIN_EXECUTABLE_NAME})
