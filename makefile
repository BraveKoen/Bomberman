SFML_PATH := d:/arduino/sfml-2.5.1

SFML_LIB := $(SFML_PATH)/lib
SFML_INC := $(SFML_PATH)/include

SFML_STL := -lsfml-main -lsfml-graphics-s -lsfml-window-s -lsfml-system-s
WIN_STL := -lgdi32 -lopengl32 -lwinmm -lfreetype

FLAGS := -std=c++17 -pedantic -Wall -Werror -Wextra -D SFML_STATIC
OBJECTS := bomberman.o game.o state.o input.o asset.o menu.o button.o menubutton.o

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

game.o: $(SRC)game.cpp $(HDR)game.hpp $(HDR)stateMachine.hpp $(HDR)assetManager.hpp $(HDR)inputManager.hpp $(HDR)mainMenuState.hpp
	g++ $(FLAGS) -c $(SRC)game.cpp -I $(SFML_INC) -o game.o

state.o: $(SRC)stateMachine.cpp $(HDR)stateMachine.hpp $(HDR)state.hpp 
	g++ $(FLAGS) -c $(SRC)stateMachine.cpp -I $(SFML_INC) -o state.o

input.o: $(SRC)inputManager.cpp $(HDR)inputManager.hpp
	g++ $(FLAGS) -c $(SRC)inputManager.cpp -I $(SFML_INC) -o input.o

asset.o: $(SRC)assetManager.cpp $(HDR)assetManager.hpp
	g++ $(FLAGS) -c $(SRC)assetManager.cpp -I $(SFML_INC) -o asset.o

menu.o: $(SRC)mainMenuState.cpp $(HDR)mainMenuState.hpp $(HDR)inputManager.hpp $(HDR)assetManager.hpp $(HDR)menuButton.hpp $(HDR)game.hpp $(HDR)state.hpp $(HDR)definitions.hpp $(HDR)utilities.hpp
	g++ $(FLAGS) -c $(SRC)mainMenuState.cpp -I $(SFML_INC) -o menu.o

button.o: $(SRC)button.cpp $(HDR)button.hpp $(HDR)game.hpp
	g++ $(FLAGS) -c $(SRC)button.cpp -I $(SFML_INC) -o button.o

menubutton.o: $(SRC)menuButton.cpp $(HDR)menuButton.hpp $(HDR)button.hpp $(HDR)game.hpp
	g++ $(FLAGS) -c $(SRC)menuButton.cpp -I $(SFML_INC) -o menubutton.o

.PHONY: build clean

build:
	bomberman

clean:
	del $(OBJECTS) 2>nul
