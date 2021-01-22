SFML_PATH := d:/arduino/sfml-2.5.1

SFML_LIB := $(SFML_PATH)/lib
SFML_INC := $(SFML_PATH)/include

SFML_STL := -lsfml-main -lsfml-graphics-s -lsfml-window-s -lsfml-system-s
WIN_STL := -lgdi32 -lopengl32 -lwinmm -lfreetype -lstdc++fs

FLAGS := -std=c++17 -pedantic -Wall -Werror -Wextra -D SFML_STATIC
OBJECTS := bomberman.o game.o state.o input.o asset.o menu.o button.o menubutton.o bomb.o bombhdlr.o player.o opponent.o tile.o tilemap.o gamestate.o mapselect.o collision.o hud.o gamehud.o playerhud.o ctrlscheme.o

SRC := sources/
HDR := headers/

# -luser32 -lfreetype -lwinmm -lmingw32 -lopengl32 -lgdi32
# -lsfml-graphics -lsfml-window -lsfml-system

# note: revert -mwindows later

bomberman: $(OBJECTS)
	g++ $(FLAGS) $(OBJECTS) -o bomberman.exe -L $(SFML_LIB) $(SFML_STL) $(WIN_STL) 
# -mwindows

bomberman.o: $(SRC)bomberman.cpp $(HDR)game.hpp $(HDR)definitions.hpp
	g++ $(FLAGS) -c $(SRC)bomberman.cpp -I $(SFML_INC) -o bomberman.o

game.o: $(SRC)game.cpp $(HDR)game.hpp $(HDR)stateMachine.hpp $(HDR)assetManager.hpp $(HDR)inputManager.hpp $(HDR)tileMap.hpp $(HDR)mainMenuState.hpp $(HDR)definitions.hpp
	g++ $(FLAGS) -c $(SRC)game.cpp -I $(SFML_INC) -o game.o

state.o: $(SRC)stateMachine.cpp $(HDR)stateMachine.hpp $(HDR)state.hpp 
	g++ $(FLAGS) -c $(SRC)stateMachine.cpp -I $(SFML_INC) -o state.o

input.o: $(SRC)inputManager.cpp $(HDR)inputManager.hpp
	g++ $(FLAGS) -c $(SRC)inputManager.cpp -I $(SFML_INC) -o input.o

asset.o: $(SRC)assetManager.cpp $(HDR)assetManager.hpp
	g++ $(FLAGS) -c $(SRC)assetManager.cpp -I $(SFML_INC) -o asset.o

menu.o: $(SRC)mainMenuState.cpp $(HDR)mainMenuState.hpp $(HDR)inputManager.hpp $(HDR)assetManager.hpp $(HDR)menuButton.hpp $(HDR)game.hpp $(HDR)state.hpp $(HDR)definitions.hpp $(HDR)utilities.hpp $(HDR)mapSelectorState.hpp
	g++ $(FLAGS) -c $(SRC)mainMenuState.cpp -I $(SFML_INC) -o menu.o

button.o: $(SRC)button.cpp $(HDR)button.hpp $(HDR)definitions.hpp
	g++ $(FLAGS) -c $(SRC)button.cpp -I $(SFML_INC) -o button.o

menubutton.o: $(SRC)menuButton.cpp $(HDR)menuButton.hpp $(HDR)button.hpp $(HDR)game.hpp $(HDR)definitions.hpp
	g++ $(FLAGS) -c $(SRC)menuButton.cpp -I $(SFML_INC) -o menubutton.o

bomb.o: $(SRC)bomb.cpp $(HDR)bomb.hpp $(HDR)game.hpp $(HDR)tile.hpp $(HDR)tileMap.hpp
	g++ $(FLAGS) -c $(SRC)bomb.cpp -I $(SFML_INC) -o bomb.o

bombhdlr.o: $(SRC)bombHandler.cpp $(HDR)bomb.hpp
	g++ $(FLAGS) -c $(SRC)bombHandler.cpp -I $(SFML_INC) -o bombhdlr.o

player.o: $(SRC)player.cpp $(HDR)player.hpp $(HDR)game.hpp $(HDR)bombHandler.hpp $(HDR)character.hpp
	g++ $(FLAGS) -c $(SRC)player.cpp -I $(SFML_INC) -o player.o

opponent.o: $(SRC)opponent.cpp $(HDR)opponent.hpp $(HDR)game.hpp $(HDR)bombHandler.hpp $(HDR)character.hpp
	g++ $(FLAGS) -c $(SRC)opponent.cpp -I $(SFML_INC) -o opponent.o

tile.o: $(SRC)tile.cpp $(HDR)tile.hpp
	g++ $(FLAGS) -c $(SRC)tile.cpp -I $(SFML_INC) -o tile.o

tilemap.o: $(SRC)tileMap.cpp $(HDR)tileMap.hpp $(HDR)tile.hpp $(HDR)game.hpp $(HDR)definitions.hpp
	g++ $(FLAGS) -c $(SRC)tileMap.cpp -I $(SFML_INC) -o tilemap.o

gamestate.o: $(SRC)inGameState.cpp $(HDR)inGameState.hpp $(HDR)player.hpp $(HDR)game.hpp $(HDR)utilities.hpp $(HDR)bombHandler.hpp $(HDR)definitions.hpp $(HDR)collision.hpp $(HDR)tileMap.hpp $(HDR)gameHud.hpp
	g++ $(FLAGS) -c $(SRC)inGameState.cpp -I $(SFML_INC) -o gamestate.o

mapselect.o: $(SRC)mapSelectorState.cpp $(HDR)mapSelectorState.hpp $(HDR)tileMap.hpp $(HDR)definitions.hpp $(HDR)game.hpp $(HDR)state.hpp
	g++ $(FLAGS) -c $(SRC)mapSelectorState.cpp -I $(SFML_INC) -o mapselect.o

collision.o: $(SRC)collision.cpp $(HDR)collision.hpp
	g++ $(FLAGS) -c $(SRC)collision.cpp -I $(SFML_INC) -o collision.o

hud.o: $(SRC)hud.cpp $(HDR)hud.hpp
	g++ $(FLAGS) -c $(SRC)hud.cpp -I $(SFML_INC) -o hud.o

gamehud.o: $(SRC)gameHud.cpp $(HDR)gameHud.hpp $(HDR)hud.hpp $(HDR)playerHud.hpp $(HDR)mainMenuState.hpp $(HDR)definitions.hpp $(HDR)utilities.hpp $(HDR)game.hpp
	g++ $(FLAGS) -c $(SRC)gameHud.cpp -I $(SFML_INC) -o gamehud.o

playerhud.o: $(SRC)playerHud.cpp $(HDR)playerHud.hpp $(HDR)hud.hpp $(HDR)definitions.hpp $(HDR)game.hpp $(HDR)utilities.hpp
	g++ $(FLAGS) -c $(SRC)playerHud.cpp -I $(SFML_INC) -o playerhud.o

ctrlscheme.o: $(SRC)controlScheme.cpp $(HDR)controlScheme.hpp
	g++ $(FLAGS) -c $(SRC)controlScheme.cpp -I $(SFML_INC) -o ctrlscheme.o

.PHONY: build clean

build:
	bomberman

clean:
	del $(OBJECTS) 2>nul
