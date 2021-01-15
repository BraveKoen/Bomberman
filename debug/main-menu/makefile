.PHONY: build clean

SFML_PATH := d:/arduino/sfml-2.5.1

SFML_LIB := $(SFML_PATH)/lib
SFML_INC := $(SFML_PATH)/include

SFML_STL := -lsfml-main -lsfml-graphics-s -lsfml-window-s -lsfml-system-s
WIN_STL := -lgdi32 -lopengl32 -lwinmm -lfreetype

FLAGS := -std=c++17 -pedantic -Wall -Werror -Wextra
OBJECTS := bomberman.o input.o asset.o menu.o

SRC := sources/
HDR := headers/

# -luser32 -lfreetype -lwinmm -lmingw32 -lopengl32 -lgdi32
# -lsfml-graphics -lsfml-window -lsfml-system

# note: revert -mwindows later

bomberman: $(OBJECTS)
	g++ $(FLAGS) $(OBJECTS) -o bomberman.exe -L $(SFML_LIB) $(SFML_STL) $(WIN_STL) 
# -mwindows

bomberman.o: $(SRC)bomberman.cpp $(HDR)gameData.hpp $(HDR)mainMenu.hpp $(HDR)definitions.hpp
	g++ $(FLAGS) -c $(SRC)bomberman.cpp -I $(SFML_INC) -o bomberman.o

input.o: $(SRC)inputManager.cpp $(HDR)inputManager.hpp
	g++ $(FLAGS) -c $(SRC)inputManager.cpp -I $(SFML_INC) -o input.o

asset.o: $(SRC)assetManager.cpp $(HDR)assetManager.hpp
	g++ $(FLAGS) -c $(SRC)assetManager.cpp -I $(SFML_INC) -o asset.o

menu.o: $(SRC)mainMenu.cpp $(HDR)mainMenu.hpp $(HDR)inputManager.hpp $(HDR)assetManager.hpp $(HDR)gameData.hpp $(HDR)state.hpp $(HDR)definitions.hpp
	g++ $(FLAGS) -c $(SRC)mainMenu.cpp -I $(SFML_INC) -o menu.o

.PHONY: build clean

build:
	bomberman

clean:
	del $(OBJECTS) 2>nul
