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
    constexpr auto play1 = "resources/play1.png";
    constexpr auto play2 = "resources/play2.png";
    constexpr auto play3 = "resources/play3.png";
    constexpr auto play4 = "resources/play4.png";
    constexpr auto dynamite = "resources/dynamite.png";
    constexpr auto biem = "resources/biem.png";
    constexpr auto mapBackground = "resources/mapBackground.png";

    constexpr auto defaultBackground = "resources/defaultBackground.png";
    constexpr auto defaultButton = "resources/defaultButton.png";

    constexpr auto playerSpriteheet = "resources/playerSpritesheet.png";

    constexpr auto bombSpritesheet = "resources/bombFuse.png";


    // constexpr auto playerUp1 = "resources/playerAnimation/playerBack1.png";
    // constexpr auto playerUp2 = "resources/playerAnimation/playerBack2.png";
    // constexpr auto playerUp3 = "resources/playerAnimation/playerBack3.png";

    // constexpr auto playerDown1 = "resources/playerAnimation/playerFront1.png";
    // constexpr auto playerDown2 = "resources/playerAnimation/playerFront2.png";
    // constexpr auto playerDown3 = "resources/playerAnimation/playerFront3.png";

    // constexpr auto playerLeft1 = "resources/playerAnimation/playerLeft1.png";
    // constexpr auto playerLeft2 = "resources/playerAnimation/playerLeft2.png";
    // constexpr auto playerLeft3 = "resources/playerAnimation/playerLeft3.png";

    // constexpr auto playerRight1 = "resources/playerAnimation/playerRight1.png";
    // constexpr auto playerRight2 = "resources/playerAnimation/playerRight2.png";
    // constexpr auto playerRight3 = "resources/playerAnimation/playerRight3.png";
}

#endif // __DEFINITIONS_HPP__
