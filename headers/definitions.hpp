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
    constexpr auto biem = "resources/biem.png";
    constexpr auto mapBackground = "resources/mapBackground.png";

    constexpr auto defaultBackground = "resources/defaultBackground.png";
    constexpr auto defaultButton = "resources/defaultButton.png";

    constexpr auto playerSprite = "resources/playerSprite.png";
    constexpr auto bombFuseSprite1 = "resources/bombFuse/bombFuseSprite1.png";
    constexpr auto bombFuseSprite2 = "resources/bombFuse/bombFuseSprite2.png";
    constexpr auto bombFuseSprite3 = "resources/bombFuse/bombFuseSprite3.png";
    constexpr auto bombFuseSprite4 = "resources/bombFuse/bombFuseSprite4.png";
    
    constexpr auto bombExplosionSprite1 = "resources/bombExplosion/bombExplosionSprite1.png";
    constexpr auto bombExplosionSprite2 = "resources/bombExplosion/bombExplosionSprite2.png";
    constexpr auto bombExplosionSprite3 = "resources/bombExplosion/bombExplosionSprite3.png";
    constexpr auto bombExplosionSprite4 = "resources/bombExplosion/bombExplosionSprite4.png";
}

#endif // __DEFINITIONS_HPP__
