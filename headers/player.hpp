#ifndef __PLAYER_HPP__
#define __PLAYER_HPP__

#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory> 

#include "bombHandler.hpp"
#include "character.hpp"

class Player : public Character {
public:
    Player(gameDataRef data, std::shared_ptr<BombHandler> bombHandler, bool arrowkeys, const sf::Vector2f& spawnPosition);

    void draw() override;
    void update();

    void setHealth(uint8_t health) override;
    int getHealth() const override;

    void setPosition(const sf::Vector2f& pos) override;
    const sf::Vector2f& getPosition() const override;

    void setMovementSpeed(uint8_t speed) override;
    int getMovementSpeed() const override;

    sf::Sprite& getSprite();

    bool playerMove();
    void revertMove();

private:
    gameDataRef data;
    std::shared_ptr<BombHandler> bombHandler;
    sf::Sprite playerSprite;
    bool arrowKeys;
    sf::Vector2f playerPosition;
    sf::Vector2f prevPosition;
    uint16_t movementSpeed;
    uint8_t playerHealth = 100;
    int playerId = 69;
    sf::Clock clock;
    float timeBombPlaced;
    bool bombCooldown = false;

    bool playerHit = false;
    float timePlayerHit;

    std::vector<sf::Texture> playerUpAnimation;
    unsigned int playerUpAnimationIterator;
    std::vector<sf::Texture> playerDownAnimation;
    unsigned int playerDownAnimationIterator;
    std::vector<sf::Texture> playerLeftAnimation;
    unsigned int playerLeftAnimationIterator;
    std::vector<sf::Texture> playerRightAnimation;
    unsigned int playerRightAnimationIterator;
};

#endif // __PLAYER_HPP__