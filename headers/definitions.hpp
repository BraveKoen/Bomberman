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
    constexpr auto play1 = "resources/play1.png";
    constexpr auto play2 = "resources/play2.png";
    constexpr auto dynamite = "resources/dynamite.png";
    constexpr auto mapBackground = "resources/mapBackground.png";
    constexpr auto dynamite = "resources/dynamite.png";
    constexpr auto biem = "resources/biem.png";

    constexpr auto defaultBackground = "resources/defaultBackground.png";
    constexpr auto defaultButton = "resources/defaultButton.png";
}

#endif // __DEFINITIONS_HPP__
