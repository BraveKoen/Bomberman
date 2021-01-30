#ifndef __OPPONENT_HPP__
#define __OPPONENT_HPP__

#include <SFML/Graphics.hpp>
#include <iostream>
#include "character.hpp"

class Opponent : public Character{
public:
    Opponent(gameDataRef data, std::shared_ptr<BombHandler> bombHandler, sf::Vector2f spawnPosition, std::string textureName, unsigned int playerId);
    // ~Opponent();

    void draw() override;

    void setHealth(uint8_t health) override;
    int getHealth() const override;

    void setPosition(const sf::Vector2f& pos) override;
    const sf::Vector2f& getPosition() const override;

    void setMovementSpeed(uint8_t speed) override;
    int getMovementSpeed() const override;

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

    void setIsAlive(bool alive);

    bool isPlayerAlive() const override;

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
