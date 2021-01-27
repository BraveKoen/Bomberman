#include "../headers/opponent.hpp"

Opponent::Opponent(gameDataRef data, std::shared_ptr<BombHandler> bombHandler, sf::Vector2f spawnPosition, std::string textureName):
    gameData(data),
    bombHandler(bombHandler),
    opponentPosition(spawnPosition),
    textureName(textureName)
{
    opponentUpAnimationIterator = 0;
    int frameSize = 100;
    opponentUpAnimationRects.emplace_back(100, 300, frameSize, frameSize);//these dimentions are here to cut out the sprites form the spritesheet
    opponentUpAnimationRects.emplace_back(200, 300, frameSize, frameSize);
    opponentUpAnimationRects.emplace_back(100, 300, frameSize, frameSize);
    opponentUpAnimationRects.emplace_back(0, 300, frameSize, frameSize);
    
    opponentDownAnimationIterator = 0;
    opponentDownAnimationRects.emplace_back(100, 0, frameSize, frameSize);//these dimentions are here to cut out the sprites form the spritesheet
    opponentDownAnimationRects.emplace_back(200, 0, frameSize, frameSize);
    opponentDownAnimationRects.emplace_back(100, 0, frameSize, frameSize);
    opponentDownAnimationRects.emplace_back(0, 0, frameSize, frameSize);

    opponentLeftAnimationIterator = 0;
    opponentLeftAnimationRects.emplace_back(100, 100, frameSize, frameSize);//these dimentions are here to cut out the sprites form the spritesheet
    opponentLeftAnimationRects.emplace_back(200, 100, frameSize, frameSize);
    opponentLeftAnimationRects.emplace_back(100, 100, frameSize, frameSize);
    opponentLeftAnimationRects.emplace_back(0, 100, frameSize, frameSize);
    
    opponentRightAnimationIterator = 0;
    opponentRightAnimationRects.emplace_back(100, 200, frameSize, frameSize);//these dimentions are here to cut out the sprites form the spritesheet
    opponentRightAnimationRects.emplace_back(200, 200, frameSize, frameSize);
    opponentRightAnimationRects.emplace_back(100, 200, frameSize, frameSize);
    opponentRightAnimationRects.emplace_back(0, 200, frameSize, frameSize);

    opponentSprite.setTexture(gameData->assetManager.getTexture(textureName));
    opponentSprite.setTextureRect(opponentDownAnimationRects.at(opponentDownAnimationIterator));
    auto tileSize = gameData->tileMap.getTileMapSize().x / gameData->tileMap.getMapSize().x;
    opponentSprite.setScale(
        tileSize / gameData->assetManager.getTexture(textureName).getSize().x *2,
        tileSize / gameData->assetManager.getTexture(textureName).getSize().y *2.5    
    );
    opponentSprite.setOrigin(
        gameData->assetManager.getTexture(textureName).getSize().x / 6, 
        gameData->assetManager.getTexture(textureName).getSize().y / 8
    );
    opponentSprite.setPosition(spawnPosition);




    // opponentSprite.setTexture(data->assetManager.getTexture("opponent4"));
    // auto tileSize = data->tileMap.getTileMapSize().x / data->tileMap.getMapSize().x;
    // opponentSprite.setScale(tileSize / data->assetManager.getTexture("opponent4").getSize().x / 2, tileSize / data->assetManager.getTexture("opponent4").getSize().y / 2);
    // opponentSprite.setOrigin(data->assetManager.getTexture("opponent4").getSize().x / 2, data->assetManager.getTexture("opponent4").getSize().y / 2); 
    // opponentSprite.setPosition(sf::Vector2f{150,150});
    // opponentSprite.setPosition(spawnPosition);
}

void Opponent::draw(){
    gameData->window.draw(opponentSprite);
}

void Opponent::setHealth(uint8_t health){
    opponentHealth = health;   
}

int Opponent::getHealth() const {
    return opponentHealth;
}

void Opponent::setPosition(const sf::Vector2f& pos){
    oldPosition = opponentPosition;
    opponentPosition = pos;
    opponentSprite.setPosition(pos);
    animateMovementDirection();
}

const sf::Vector2f& Opponent::getPosition() const {
    return opponentPosition;
}

void Opponent::setMovementSpeed(uint8_t speed){
    movementSpeed = speed;
}

int Opponent::getMovementSpeed() const {
    return movementSpeed;
}

void Opponent::spawnBomb(int opponentId){
    bombHandler->createBomb(opponentId, 4, 4, 2, opponentPosition);
}

void Opponent::animateMovementDirection(){
    if(oldPosition.x < opponentPosition.x){
        animateMovement(opponentRightAnimationRects, opponentRightAnimationIterator);
    }else if(oldPosition.x > opponentPosition.x){
        animateMovement(opponentLeftAnimationRects, opponentLeftAnimationIterator);
    }else if(oldPosition.y < opponentPosition.y){
        animateMovement(opponentUpAnimationRects, opponentUpAnimationIterator);
    }else if(oldPosition.y > opponentPosition.y){
        animateMovement(opponentDownAnimationRects, opponentDownAnimationIterator);
    }
}

void Opponent::animateMovement(std::vector<sf::IntRect> & animationRect, unsigned int & iterator){
    if (opponentAnimationClock.getElapsedTime().asSeconds() > 0.5f/animationRect.size()){
        if(iterator < animationRect.size()-1){
            iterator++;
        }else{
            iterator = 0;
        }
        opponentSprite.setTextureRect(animationRect.at(iterator));
        opponentAnimationClock.restart();
    }    
}