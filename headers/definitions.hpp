#ifndef __DEFINITIONS_HPP__
#define __DEFINITIONS_HPP__

#include <array>
#include <memory>
#include <SFML/Graphics.hpp>

struct GameData;
using gameDataRef = std::shared_ptr<GameData>;

// the linker doesn't seem to like this:
//   using textureData = struct {const char *name; const char *file;};
//   using textureDataExt = struct {const char *name; const char *file; sf::Sprite *sprite;};
typedef struct {const char *name; const char *file;} resourceData;
typedef struct {const resourceData& data; sf::Sprite *sprite = nullptr;} resourceContainer;

namespace Resource {
    constexpr auto screenWidth = 1280;
    constexpr auto screenHeight = 720;
    inline const auto screenSize = sf::Vector2f{screenWidth, screenHeight};

    constexpr auto mapFolderLocation = "resources/maps";

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

    constexpr auto bombSpritesheet = "resources/bombFuse.png";
    constexpr auto title = "resources/title.png";

    constexpr auto defaultPlayerMoveSpeed = 2.5f;
    constexpr auto defaultPlayerLives = 5u;

    constexpr auto maxTileMaps = 5u;
    constexpr auto fileExtension = ".txt";

    namespace Button {
        constexpr auto defaultTexture = resourceData{"default button", "resources/defaultButton.png"};
        constexpr auto defaultFont = resourceData{"default font", "resources/KOMIKAX_.ttf"};
        inline const auto defaultFontColor = sf::Color{22, 21, 51};
        inline const auto defaultButtonScale = sf::Vector2f{5, 10};
        constexpr auto defaultSpacingScale = 1.2f;
        constexpr auto defaultTextScale = 1.4f;
        inline const auto defaultTextOffset = sf::Vector2f{0, 2};
        inline const auto defaultTextColor = Resource::Button::defaultFontColor;
    }

    namespace HUD {
        constexpr auto mainFrame = resourceData{"main frame", "resources/mainFrame.png"};
        constexpr auto subFrame = resourceData{"sub frame", "resources/subFrame.png"};
        constexpr auto menuFrame = resourceData{"menu frame", "resources/menuFrame.png"};

        constexpr auto fullLife = resourceData{"full life", "resources/fullLife.png"};
        constexpr auto emptyLife = resourceData{"empty life", "resources/emptyLife.png"};

        constexpr auto banner = resourceData{"banner", "resources/banner.png"};
        constexpr auto profiles = std::array{
            resourceData{"profile1", "resources/profile1.png"},
            resourceData{"profile2", "resources/profile2.png"},
            resourceData{"profile3", "resources/profile3.png"},
            resourceData{"profile4", "resources/profile4.png"}
        };
        constexpr auto maxPlayers = Resource::HUD::profiles.size();
        constexpr int maxLives = 5u;
    }

    constexpr auto serverIp = "77.161.253.51";
    //constexpr auto serverIp = "192.168.2.14";

}

#endif // __DEFINITIONS_HPP__
