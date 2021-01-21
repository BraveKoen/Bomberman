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
    Player(gameDataRef gameData, std::shared_ptr<BombHandler> bombHandler, ControlScheme controls, const sf::Vector2f& spawnPosition, unsigned int playerId, std::string textureName, float movementSpeed=Resource::defaultPlayerMoveSpeed, uint8_t playerHealth=Resource::defaultPlayerLives);
    // ~Player(){std::cout << "PlayerDespt" << std::endl;}

    void draw() override;
    void handleInput();
    void update(const float & delta);

    void setPlayerId(unsigned int id);
    unsigned int getPlayerId() const;

    void setHealth(uint8_t health) override;
    int getHealth() const override;

    bool isPlayerAlive() const;

    void setPosition(const sf::Vector2f& pos) override;
    const sf::Vector2f& getPosition() const override;

    void setMovementSpeed(uint8_t speed) override;
    int getMovementSpeed() const override;

    void setTexture(const sf::Texture & newTexture);

    sf::Sprite& getSprite();

    bool playerMove(const float & delta);
    void revertMove(const char & axis=' ');

    void animateMovementDirection();
    void animateMovement(std::vector<sf::IntRect> & animationRect, unsigned int & iterator);

private:
    gameDataRef gameData;
    std::shared_ptr<BombHandler> bombHandler;
    ControlScheme controls;
    sf::Vector2f playerPosition;
    sf::Vector2f prevPosition;

    float movementSpeed;
    uint8_t playerHealth;
    sf::Vector2i movementDirection;
    sf::Vector2i prevMovementDirection;
    bool placeBomb;
    
    Collision collision;
    sf::Sprite playerSprite;

    int playerId = -1;

    sf::Clock clock;
    float timeBombPlaced;
    bool bombCooldown = false;

    bool isReady = false;

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
    PlayerInfo playerInfo;
};

#endif // __PLAYER_HPP__