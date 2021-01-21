#ifndef __DEFINITIONS_HPP__
#define __DEFINITIONS_HPP__

#include <memory>

struct GameData;
using gameDataRef = std::shared_ptr<GameData>;

namespace Resource {
    constexpr auto screenWidth = 1280;
    constexpr auto screenHeight = 720;

    constexpr auto mapFolderLocation = "resources/maps";

    constexpr auto menuButtonFilePath = "resources/menuButton.png";
    constexpr auto globalFont = "resources/256bytes.ttf";

    constexpr auto solid = "resources/solid.png";
    constexpr auto breakable = "resources/break.png";
    constexpr auto spawn = "resources/spawn.png";
    constexpr auto player1 = "resources/player1.png";
    constexpr auto player2 = "resources/player2.png";
    constexpr auto player3 = "resources/player3.png";
    constexpr auto player4 = "resources/player4.png";
    constexpr auto biem = "resources/biem.png";
    constexpr auto mapBackground = "resources/mapBackground.png";

    constexpr auto defaultBackground = "resources/defaultBackground.png";
    constexpr auto defaultButton = "resources/defaultButton.png";

    constexpr auto bombSpritesheet = "resources/bombFuse.png";

    constexpr float defaultPlayerMoveSpeed = 2.5;
    constexpr unsigned int defaultPlayerLives = 5;

}

#endif // __DEFINITIONS_HPP__
