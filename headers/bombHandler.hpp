#ifndef __BOMBHANDLER_HPP__
#define __BOMBHANDLER_HPP__

#include <vector>
#include <iostream> 
#include <memory> 

#include "bomb.hpp"

/// \brief
/// Class BombHandler
/// \details
/// BombHandler keeps track of all the bombs placed
class BombHandler{
public:
    /// \brief
    /// BombHandler constructor
    /// \details
    /// BombHandler needs gameDataRef
    BombHandler(gameDataRef data);
    ~BombHandler(){}

    /// \brief
    /// void createBomb
    /// \details
    /// createBomb needs int playerId
    /// int lenghtX
    /// int lenghtY
    /// int explodeTime how long it will when the bomb explodes
    /// sf::vector2f pos where the bomb needs to be placed
    void createBomb(int playerId, int lenghtX, int lenghtY, int explodeTime, sf::Vector2f pos);

    /// \brief
    /// void draw
    /// \details
    /// loop through every bomb in the list
    void draw();

    /// \brief
    /// void update
    /// \details
    /// deletes a bomb when it is exploded
    void update();

    /// \brief
    /// bool checkBombCollision
    /// \details
    /// when a bomb hits a sprite it will return true
    bool checkBombCollision(const sf::Sprite& target);

private:

    std::vector<std::unique_ptr<Bomb>> bombs;

    gameDataRef data;

    sf::Clock clock;
};

#endif // __BOMBMANAGER_HPP__