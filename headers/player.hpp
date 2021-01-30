#ifndef __PLAYER_HPP__
#define __PLAYER_HPP__

#include <iostream>
#include <memory>
#include <SFML/Graphics.hpp>
#include "bombHandler.hpp"
#include "character.hpp"
#include "definitions.hpp"
#include "controlScheme.hpp"
#include "collision.hpp"
#include "utilities.hpp"
#include "serverInfo.hpp"

class Player : public Character {
public:
    Player(gameDataRef gameData, std::shared_ptr<BombHandler> bombHandler, ControlScheme controls, const sf::Vector2f& spawnPosition, unsigned int playerId, std::string textureName, float movementSpeed=Resource::defaultPlayerMoveSpeed, int playerHealth=Resource::defaultPlayerLives);
    // ~Player(){std::cout << "PlayerDespt" << std::endl;}

    /// \brief
    ///  void draw
    /// \details
    /// draw the player on current screen
    void draw() override;

    /// \brief
    ///  void handleInput
    /// \details
    /// this function is mostly for bomb placement
    /// when the player presses the bomb button is will spawn a bomb when the player is alive
    void handleInput();

    /// \brief
    ///  void update float 
    /// \details
    /// the update function checks if the player hits a wall
    /// it also check if the player get hit by a bomb

    void update(const float & delta);

    /// \brief
    ///  void setPlayerId int
    /// \details
    /// set the id of the player
    void setPlayerId(unsigned int id);

    /// \brief
    ///  unsigned int getPlayerId
    /// \details
    /// returns the current playerId
    unsigned int getPlayerId() const override;

    /// \brief
    ///  void setHealth uint8_t
    /// \details
    /// set Health of the player
    void setHealth(uint8_t health) override;

    /// \brief
    ///  int getHealth 
    /// \details
    /// returns current health
    int getHealth() const override;

    /// \brief
    ///  bool isPlayerAlive
    /// \details
    /// returns false when the player has no health left
    bool isPlayerAlive() const override;

    /// \brief
    ///  void setPosition sf::Vector2f
    /// \details
    /// set the player on the given position
    void setPosition(const sf::Vector2f& pos) override;

    /// \brief
    ///  void getPosition
    /// \details
    /// returns the current player Position
    const sf::Vector2f& getPosition() const override;

    /// \brief
    ///  void setMovementSpeed uint8_t
    /// \details
    /// you can set how fast the player walks
    void setMovementSpeed(uint8_t speed) override;

    /// \brief
    ///  int getMovementSpeed
    /// \details
    /// returns the current movementspeed
    int getMovementSpeed() const override;

    /// \brief
    ///  void setTexture sf::Texture
    /// \details
    /// you can change the sprite
    void setTexture(const sf::Texture & newTexture);

    /// \brief
    ///  sf::Sprite getSprite
    /// \details
    /// returns the current used sprite
    sf::Sprite& getSprite();

    bool playerMove(const float & delta);
    void revertMove(const char & axis=' ');

    /// \brief
    /// void animateMovementDirection()
    /// \details
    /// This function will decide on wich movmement direction the Player should be animated in.
    /// After wich it will call the animateMovement with these directions.
    /// By using the sf::Vector2i movementDirection it can decide the movement direction of the Player.
    /// If the player is moving in two or more directions at the same time,
    /// it will prefer to draw the Player walking to the right, then left, then up, then down.
    void animateMovementDirection();

    /// \brief
    /// void animateMovement(std::vector<sf::IntRect> & animationRect, unsigned int & iterator)
    /// \details
    /// This function will (given a animationrect and iterator) animate the Player on a standard delay of 0.5 seconds.
    /// It will cycle through all sprite rects in the animationRect using the iterator.
    /// Function should be called no slower then every *delay* amount of seconds or else it will effect the animation speed.
    void animateMovement(std::vector<sf::IntRect> & animationRect, unsigned int & iterator);

private:
    gameDataRef gameData;
    std::shared_ptr<BombHandler> bombHandler;
    ControlScheme controls;
    sf::Vector2f playerPosition;
    sf::Vector2f prevPosition;
    unsigned int playerId;
    float movementSpeed;
    int playerHealth;
    sf::Vector2i movementDirection;
    sf::Vector2i prevMovementDirection;
    bool placeBomb;
    PlayerInfo playerInfo;
    
    Collision collision;
    sf::Sprite playerSprite;
    sf::Clock clock;
    float timeBombPlaced;
    bool bombCooldown = false;

    bool playerHit = false;
    float timePlayerHit;

    bool isAlive = true;

    std::vector<sf::IntRect> playerUpAnimationRects;
    unsigned int playerUpAnimationIterator;
    std::vector<sf::IntRect> playerDownAnimationRects;
    unsigned int playerDownAnimationIterator;
    std::vector<sf::IntRect> playerLeftAnimationRects;
    unsigned int playerLeftAnimationIterator;
    std::vector<sf::IntRect> playerRightAnimationRects;
    unsigned int playerRightAnimationIterator;
    sf::Clock playerAnimationClock; 
};

#endif // __PLAYER_HPP__