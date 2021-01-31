# Makefile Recipe Generator
#
# File:     makefile
# Version:  0.4
#
# Author:   Joeri Kok
# Date:     January 2021
#
# Description:
#	A makefile orignally designed for the Bomberman project which generates
#   target recipes based on file header inclusions within source files.
#
# Summary:
#   This makefile searches for CPP source files located within the directory
#   specified by the SRC_DIR variable. For every source file it finds, it will
#   look for all the user included header files (encapsulated within quotes
#   rather than pointy brackets) within that source file and its corresponding
#   header file. After that, a recipe is created which is tied to the header
#   files that were found. This allows the makefile to be flexible yet
#   efficient. There is no need to manually update the makefile when creating
#   new source files and the object files are only being rebuild when it is
#   deemed necessary.
#
SFML_PATH := d:/arduino/sfml-2.5.1

SFML_LIB := $(SFML_PATH)/lib
SFML_INC := $(SFML_PATH)/include

SFML_STL := -lsfml-main -lsfml-graphics-s -lsfml-window-s -lsfml-system-s -lsfml-network-s
WIN_STL := -lgdi32 -lopengl32 -lws2_32 -lwinmm -lfreetype -lstdc++fs

MACROS := SFML_STATIC

# note: to hide the console window, add the following flag: -mwindows
CFLAGS := -std=c++17 -pedantic -Wall -Wextra -Werror -D $(MACROS)
OUT_FILE := bomberman.exe

SRC_DIR := sources
HDR_DIR := headers

VPATH = $(SRC_DIR):$(HDR_DIR)

# extract file names from all CPP files within the SRC_DIR directory
# and replace the .cpp extensions with .o
targets := $(patsubst %.cpp,%.o,$(notdir $(wildcard $(SRC_DIR)/*.cpp)))

# search through the HPP and CPP file specified by the $1 (first) argument and
# only return the strings that start with '#include "' (note the double quote)
find_includes = findstr 2^>nul /b /i /c:"\#include "^" "$(HDR_DIR)\\$1.hpp" "$(SRC_DIR)\\$1.cpp"

# walk through the output of the find_includes command, returning the 2nd token
# delimited by double quotes while only keeping the file name and extension
find_dependencies = for /f tokens^=2^ delims^=^" %%e in ('$(find_includes)') do echo %%~nxe

# creates a recipe for a target based on the 1st argument it receives and runs
# the find_dependencies command to look for all corresponding header files
define create_target_recipe
    $1.o: $1.cpp $(shell $(find_dependencies))
		g++ $(CFLAGS) -c $$< -I $(SFML_INC) -o $$@
endef

build: $(targets)
	g++ $(CFLAGS) $(targets) -o $(OUT_FILE) -L $(SFML_LIB) $(SFML_STL) $(WIN_STL)

# iterate over all the targets found and create a recipe for each of them
$(foreach target, $(basename $(targets)), $(eval $(call create_target_recipe,$(target))))

clean:
	del $(targets) 2>nul

.PHONY: build clean
