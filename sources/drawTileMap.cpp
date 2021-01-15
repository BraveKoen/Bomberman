#include "../headers/drawTileMap.cpp"

void drawTileMap(TileMap tileMap, gameDataRef gameData, bool drawPlayerSpawns){
    sf::Sprite background(gameData->assetManager.getTexture("map background"));
    background.setPosition(tileMap.getTileMapPosition());
    background.setScale(tileMap.getTileMapSize().x/background.getTexture()->getSize().x, tileMap.getTileMapSize().y/background.getTexture()->getSize().y);
    gameData->window.draw(background);
    std::vector<std::vector<std::string>> map = tileMap.getMap();
    for(unsigned int i=0; i<map.size(); i++){
        for(unsigned int j=0; j<map[i].size(); j++){
            if(map[i][j] != "empty"){
                sf::Sprite sprite;
                if(map[i][j] == "solid"){
                    sprite.setTexture(gameData->assetManager.getTexture("unbreakable wall"));
                }else if(map[i][j] == "break"){
                    sprite.setTexture(gameData->assetManager.getTexture("breakable wall"));
                }else if(drawPlayerSpawns){
                    if(map[i][j] == "play1"){
                        sprite.setTexture(gameData->assetManager.getTexture("player1 spawn location"));
                    }else if(map[i][j] == "play2"){
                        sprite.setTexture(gameData->assetManager.getTexture("player2 spawn location"));
                    }else if(map[i][j] == "play3"){
                        sprite.setTexture(gameData->assetManager.getTexture("player3 spawn location"));
                    }else if(map[i][j] == "play4"){
                        sprite.setTexture(gameData->assetManager.getTexture("player4 spawn location"));
                    }else{
                        continue;
                    }
                }else{
                    continue;
                }
                sprite.setPosition(tileMap.getTileMapPosition().x+((tileMap.getTileMapSize().x/tileMap.getMapSize().x)*i), tileMap.getTileMapPosition().y+((tileMap.getTileMapSize().y/tileMap.getMapSize().y)*j));
                sprite.setScale((tileMap.getTileMapSize().x/tileMap.getMapSize().x)/sprite.getTexture()->getSize().x, (tileMap.getTileMapSize().y/tileMap.getMapSize().y)/sprite.getTexture()->getSize().y);
                gameData->window.draw(sprite);
            }
        }
    }
}