.PHONY: build clean

SFML_LIB := ../../sfml-2.5.1/lib
SFML_INC := ../../sfml-2.5.1/include

SFML_STL := -lsfml-main -lsfml-graphics-s -lsfml-window-s -lsfml-system-s
WIN_STL := -lgdi32 -lopengl32 -lwinmm

FLAGS := -std=c++17 -pedantic -Wall -Werror -Wextra -Wno-unused-parameter
OBJECTS := editor.o drawable.o color-option.o

# -luser32 -lfreetype -lwinmm -lmingw32 -lopengl32 -lgdi32
# -lsfml-graphics -lsfml-window -lsfml-system

# note: revert -mwindows later

editor: $(OBJECTS)
	g++ $(FLAGS) $(OBJECTS) -o editor.exe -L $(SFML_LIB) $(SFML_STL) $(WIN_STL) 
# -mwindows

editor.o: editor.cpp color-panel.hpp
	g++ $(FLAGS) -c editor.cpp -I $(SFML_INC) -o editor.o

drawable.o: drawable.cpp drawable.hpp
	g++ $(FLAGS) -c drawable.cpp -I $(SFML_INC) -o drawable.o

color-option.o: color-option.cpp color-option.hpp
	g++ $(FLAGS) -c color-option.cpp -I $(SFML_INC) -o color-option.o

# color-panel.o: color-panel.hpp
# 	g++ $(FLAGS) -c color-panel.hpp -I $(SFML_INC) -o color-panel.o

clean:
	del $(OBJECTS)

build:
	editor
