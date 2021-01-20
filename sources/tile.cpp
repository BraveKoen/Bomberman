#include "../headers/tile.hpp"
#include <iostream>

Tile::Tile(std::string type, sf::Sprite sprite):
    type(type),
    sprite(sprite)
{}

void Tile::setType(std::string newType){
    type = newType;
}

const std::string& Tile::getType()const{
    return type;
}

void Tile::setTexture(const sf::Texture & newTexture){
    sprite.setTexture(newTexture, true);
}

const sf::Texture* Tile::getTexture()const{
    return sprite.getTexture();
}

void Tile::setPosition(const sf::Vector2f & newPosition){
    sprite.setPosition(newPosition);
}

const sf::Vector2f& Tile::getPosition()const{
    return sprite.getPosition();
}

void Tile::setScale(const sf::Vector2f & newScale){
    sprite.setScale(newScale);
}

const sf::Vector2f& Tile::getScale()const{
    return sprite.getScale();
}

const sf::Vector2f Tile::getSize()const{
    return sf::Vector2f(sprite.getGlobalBounds().width, sprite.getGlobalBounds().height);
}

const sf::FloatRect Tile::getBounds()const{
    return sprite.getGlobalBounds();
}

void Tile::draw(sf::RenderWindow & window)const{
    window.draw(sprite);
}
