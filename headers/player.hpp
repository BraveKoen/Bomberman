#ifndef __PLAYER_HPP__
#define __PLAYER_HPP__

#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory> 

#include "bombHandler.hpp"
#include "character.hpp"
#include "definitions.hpp"
#include "controlScheme.hpp"
#include "collision.hpp"
#include "utilities.hpp"

class Player : public Character {
public:
    Player(gameDataRef gameData, std::shared_ptr<BombHandler> bombHandler, ControlScheme controls, const sf::Vector2f& spawnPosition, uint16_t movementSpeed=Resource::defaultPlayerMoveSpeed, uint8_t playerHealth=Resource::defaultPlayerLives);
    // ~Player(){std::cout << "PlayerDespt" << std::endl;}

    void draw() override;
    void handleInput();
    void update(const float & delta);

    void setHealth(uint8_t health) override;
    int getHealth() const override;

    void setPosition(const sf::Vector2f& pos) override;
    const sf::Vector2f& getPosition() const override;

    void setMovementSpeed(uint8_t speed) override;
    int getMovementSpeed() const override;

    sf::Sprite& getSprite();

    bool playerMove(const float & delta);
    void revertMove(const char & axis=' ');

private:
    gameDataRef gameData;
    std::shared_ptr<BombHandler> bombHandler;
    ControlScheme controls;
    sf::Vector2f playerPosition;
    sf::Vector2f prevPosition;
    uint16_t movementSpeed;
    uint8_t playerHealth;
    sf::Vector2i movementDirection;
    sf::Vector2i prevMovementDirection;
    bool placeBomb;
    
    sf::Sprite playerSprite;
    int playerId = 69; //???
    sf::Clock clock;
    float timeBombPlaced;
    bool bombCooldown = false;

    bool playerHit = false;
    float timePlayerHit;
};

#endif // __PLAYER_HPP__