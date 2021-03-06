#ifndef __BOMB_HPP__
#define __BOMB_HPP__

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "game.hpp"
#include "tile.hpp"
#include "collision.hpp"

/// \brief
/// Class Bomb
/// \details
/// Bomb is one bomb on the screen with is own time
class Bomb{
public:
    /// \brief
    /// Bomb constructor 
    /// \details
    /// Bomb will need gamedata to draw on the screen
    /// int playerId to keep track on who placed the bomb
    /// int lenghtx and int lenghtY for how big the explosion is
    /// float explodeTime for how long it takes to explode
    /// float timeCreated when to bomb is placed by de player
    /// sf::Vector2f position where to place the bomb on the map 
    Bomb(gameDataRef data, int playerId, int lenghtX, int lenghtY, float explodeTime, float timeCreated, sf::Vector2f pos);
    ~Bomb(){}

    /// \brief
    /// void draw
    /// \details
    /// draws the sprite on the screen
    void draw();

    /// \brief
    /// void explode
    /// \details
    /// will draw the explosion, the explosion is based on lenghtX and lenghtY
    void explode();

    /// \brief
    /// bool isExploded
    /// \details
    /// isExploded keeps track of the time
    /// it return true when the time is over
    bool isExploded(float currentTime);

    /// \brief
    /// int getBombId
    /// \details
    /// returns the bombId
    int getBombId();

    /// \brief
    /// bool playerHit
    /// \details
    /// playerHit will return true when the bomb explodes and hits a player
    /// it will not return true when you hit a opponent
    bool playerHit();

    /// \brief
    /// void setPos(sf::Vector2F)
    /// \details
    /// you can change the position of the bomb when it is placed
    void setPos(sf::Vector2f pos);

    /// \brief
    /// void clearBomb
    /// \details
    /// clearBomb get rid of al the explotion animations
    void clearBomb();

    /// \brief
    /// bool bombColliding()
    /// \details
    /// checks if a bomb collets with a player
    bool bombColliding(const sf::Sprite& target);

    /// \brief
    /// void animateFuse()
    /// \details
    /// This function will animate the bomb fuse on a standard delay of 0.5 seconds.
    /// It will cycle through all sprites declared in the constructor in the bombFuseAnimationRects.
    /// Function should be called no slower then every *delay* amount of seconds or else it will effect the animation speed.
    void animateFuse();
    
    /// \brief
    /// void animateExplosion()
    /// \details
    /// This function will animate the bomb explosion on a standard delay of 0.5 seconds.
    /// It will cycle through all sprites declared in the constructor in the bombExplosionAnimationRects.
    /// Function should be called no slower then every *delay* amount of seconds or else it will effect the animation speed. 
    void animateExplosion();

    /// \brief
    /// bool getPrimed()
    /// \details
    /// This function will return a bool with the value of private member variable primed.
    /// The variable returned decides if the bomb is ready to explode.
    /// It has influence in the Bomb::isExploded(float currentTime) function.
    bool getPrimed();

private:

    gameDataRef data;
    int id; // playerId who placed it

    int lengthX; //How big is the explotion in x 
    int lengthY;//How big is the explotion in y

    float explodeTime; //How many seconds does it need to explode
    float timeCreated; //When is the bomb placed

    sf::Sprite bombSprite;
    sf::Vector2f bombPosition;

    std::vector<sf::Vector2u> destroyedTiles;
    bool explodeAnimation = false;
    bool primed = false;

    std::vector<sf::IntRect> bombFuseAnimationRects;
    unsigned int bombFuseAnimationIterator;
    std::vector<sf::IntRect> bombExplosionAnimationRects;
    unsigned int bombExplosionAnimationIterator;
    sf::Clock clock;    
};

#endif // __BOMB_HPP__