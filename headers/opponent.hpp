#ifndef __OPPONENT_HPP__
#define __OPPONENT_HPP__

#include <SFML/Graphics.hpp>
#include <iostream>
#include "character.hpp"

class Opponent : public Character{
public:
    Opponent(gameDataRef data, std::shared_ptr<BombHandler> bombHandler, sf::Vector2f spawnPosition, std::string textureName);
    // ~Opponent();

    void draw() override;

    void setHealth(uint8_t health) override;
    int getHealth() const override;

    void setPosition(const sf::Vector2f& pos) override;
    const sf::Vector2f& getPosition() const override;

    void setMovementSpeed(uint8_t speed) override;
    int getMovementSpeed() const override;

    void spawnBomb(int opponentId);

    void animateMovementDirection();

    void animateMovement(std::vector<sf::IntRect> & animationRect, unsigned int & iterator);

    void setIsAlive(bool alive);

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
