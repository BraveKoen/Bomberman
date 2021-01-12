.PHONY: build clean

SFML_PATH := d:/arduino/sfml-2.5.1

SFML_LIB := $(SFML_PATH)/lib
SFML_INC := $(SFML_PATH)/include

SFML_STL := -lsfml-main -lsfml-graphics-s -lsfml-window-s -lsfml-system-s
WIN_STL := -lgdi32 -lopengl32 -lwinmm

FLAGS := -std=c++17 -pedantic -Wall -Werror -Wextra
OBJECTS := dbg.o input.o menu.o

# -luser32 -lfreetype -lwinmm -lmingw32 -lopengl32 -lgdi32
# -lsfml-graphics -lsfml-window -lsfml-system

# note: revert -mwindows later

dbg: $(OBJECTS)
	g++ $(FLAGS) $(OBJECTS) -o dbg.exe -L $(SFML_LIB) $(SFML_STL) $(WIN_STL) 
# -mwindows

dbg.o: dbg.cpp game-data.hpp state.hpp
	g++ $(FLAGS) -c dbg.cpp -I $(SFML_INC) -o dbg.o

input.o: input-manager.cpp input-manager.hpp
	g++ $(FLAGS) -c input-manager.cpp -I $(SFML_INC) -o input.o

menu.o: ../menu/main-menu.cpp ../menu/main-menu.hpp
	g++ $(FLAGS) -c ../menu/main-menu.cpp -I $(SFML_INC) -o menu.o

clean:
	del $(OBJECTS)

build:
	editor
