#include "../headers/tile.hpp"

Tile::Tile(std::string type, sf::Sprite sprite):
    type(type),
    sprite(sprite)
    {}

void Tile::setType(std::string newType){
    type = newType;
}

std::string Tile::getType(){
    return type;
}

void Tile::setTexture(const sf::Texture & newTexture){
    sprite.setTexture(newTexture, true);
}

const sf::Texture* Tile::getTexture(){
    return sprite.getTexture();
}

void Tile::setPosition(const sf::Vector2f & newPosition){
    sprite.setPosition(newPosition);
}

sf::Vector2f Tile::getPosition(){
    return sprite.getPosition();
}

void Tile::setScale(const sf::Vector2f & newScale){
    sprite.setScale(newScale);
}

sf::Vector2f Tile::getScale(){
    return sprite.getScale();
}

sf::Vector2f Tile::getSize(){
    return sf::Vector2f(sprite.getGlobalBounds().width, sprite.getGlobalBounds().height);
}

sf::FloatRect Tile::getBounds(){
    return sprite.getGlobalBounds();
}

void Tile::draw(sf::RenderWindow & window){
    window.draw(sprite);
}