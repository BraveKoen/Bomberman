#ifndef __OPPONENT_HPP__
#define __OPPONENT_HPP__

#include <SFML/Graphics.hpp>
#include <iostream>
#include "character.hpp"

class Opponent : public Character{
public:
    Opponent(gameDataRef data, std::shared_ptr<BombHandler> bombHandler, sf::Vector2f spawnPosition, std::string textureName, unsigned int playerId);
    // ~Opponent();

    /// \brief
    ///  void draw
    /// \details
    /// draw the player on current screen
    void draw() override;

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
    ///  spawnBomb int
    /// \details
    /// opponent will spawn a bomb
    void spawnBomb(int opponentId);

    /// \brief
    /// void animateMovementDirection()
    /// \details
    /// This function will decide on wich movmement direction the Opponent should be animated in.
    /// After wich it will call the animateMovement with these directions.
    /// By saving the old position of the Opponent it can decide the movement direction.
    /// If the Opponent is moving in two or more directions at the same time,
    /// it will prefer to draw the Opponent walking to the right, then left, then up, then down.
    void animateMovementDirection();

    /// \brief
    /// void animateMovement(std::vector<sf::IntRect> & animationRect, unsigned int & iterator)
    /// \details
    /// This function will (given a animationrect and iterator) animate the Opponent on a standard delay of 0.5 seconds.
    /// It will cycle through all sprite rects in the animationRect using the iterator.
    /// Function should be called no slower then every *delay* amount of seconds or else it will effect the animation speed.
    void animateMovement(std::vector<sf::IntRect> & animationRect, unsigned int & iterator);

    /// \brief
    ///  void setIsAlive bool
    /// \details
    /// you can let a player die
    void setIsAlive(bool alive);

    /// \brief
    ///  bool isPlayerAlive
    /// \details
    /// returns if the opponent is alive
    bool isPlayerAlive() const override;

    /// \brief
    ///  unsigned int getPlayerId
    /// \details
    /// returns opponentId
    unsigned int getPlayerId() const override;

private:
    gameDataRef gameData;
    std::shared_ptr<BombHandler> bombHandler;
    sf::Sprite opponentSprite;
    sf::Vector2f opponentPosition;
    sf::Vector2f oldPosition;
    std::string textureName;
    int movementSpeed;
    int opponentHealth;
    bool isAlive = true;
    unsigned int playerId;
    

    std::vector<sf::IntRect> opponentUpAnimationRects;
    unsigned int opponentUpAnimationIterator;
    std::vector<sf::IntRect> opponentDownAnimationRects;
    unsigned int opponentDownAnimationIterator;
    std::vector<sf::IntRect> opponentLeftAnimationRects;
    unsigned int opponentLeftAnimationIterator;
    std::vector<sf::IntRect> opponentRightAnimationRects;
    unsigned int opponentRightAnimationIterator;
    sf::Clock opponentAnimationClock; 
};

#endif // __OPPONENT_HPP__
