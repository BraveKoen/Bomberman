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

/// \brief
///  namespace Resource
/// \details
/// contains all static data
/// this makes it more easy to change values without missing one in the code

namespace Resource {
    constexpr auto screenWidth = 1280;
    constexpr auto screenHeight = 720;
    inline const auto screenSize = sf::Vector2f{screenWidth, screenHeight};

    constexpr auto mapFolderLocation = "resources/maps";
    constexpr auto globalFont = "resources/KOMIKAX_.ttf";
    inline const sf::Color globalFontColor(22, 21, 51);

    /// \brief
    /// Map object resources
    /// \details
    /// Contains the file locations of all the resources that are needed
    /// for properly drawing map related objects onto the screen.
    constexpr auto solid = "resources/solid.png";
    constexpr auto breakable = "resources/break.png";
    constexpr auto spawn = "resources/spawn.png";
    constexpr auto player1 = "resources/player1.png";
    constexpr auto player2 = "resources/player2.png";
    constexpr auto player3 = "resources/player3.png";
    constexpr auto player4 = "resources/player4.png";
    constexpr auto biem = "resources/biem.png";
    constexpr auto mapBackground = "resources/mapBackground.png";

    /// \brief
    /// Menu resources
    /// \details
    /// Contains the file locations of all the resources that are needed
    /// for properly drawing menus onto the screen.
    constexpr auto defaultBackground = "resources/defaultBackground.png";
    constexpr auto defaultButton = "resources/defaultButton.png";
    constexpr auto menuButton = "resources/menuButton.png";

    constexpr auto bombSpritesheet = "resources/bombFuse.png";
    constexpr auto title = "resources/title.png";

    constexpr auto defaultPlayerMoveSpeed = 2.5f;
    constexpr auto defaultPlayerLives = 5u;

    constexpr auto maxTileMaps = 5u;
    constexpr auto fileExtension = ".txt";

    /// \brief
    ///  Hud in Resource
    /// \details
    /// to make is more clear that all this values is used for the hud
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
