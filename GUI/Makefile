##
## EPITECH PROJECT, 2023
## B-YEP-400-REN-4-1-zappy
## File description:
## Makefile
##

# Project settings
NAME         = ../zappy_gui
COMPILER     = g++
SRC_DIR      = src/
SRC          = $(shell find $(SRC_DIR) -name '**.cpp')

OBJ          = $(SRC:.cpp=.o)
INCLUDE      = -I includes/
CXX_FLAGS    = -Wall -Wextra -Wpedantic -std=c++17 -pipe -g3
FAST_FLAGS   = -g3 #-Ofast -march=native -flto -funroll-loops -fomit-frame-pointer
DEBUG_FLAGS  = -g3 -ggdb -fno-omit-frame-pointer
LIB_THREADS  = -lpthread
LIB_SFML     = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
LIBS         = $(LIB_THREADS) $(LIB_SFML)

ifeq ($(shell uname), Darwin)
	CXXFLAGS += -Wno-unused-command-line-argument
endif

# Targets
all: $(NAME)

$(NAME): $(OBJ)
	@$(COMPILER) -o $(NAME) $(OBJ) $(CXX_FLAGS) $(FAST_FLAGS) $(INCLUDE) $(LIBS)

clean:
	@rm -rf $(OBJ)

ninja_all: gen_ninja
	@ninja zappy_gui

ninja_clean:
	@ninja -t clean

gen_ninja:
	@-Script/Install/install_ninja_ubuntu.sh 2> /dev/null
	@Script/Generate_Ninja.py

fclean: clean
	@rm -rf $(NAME)
	@-rm -rf .ninja_log
# If Macos
ifeq ($(shell uname), Darwin)
	@find . -type f -name "*.gcda" -exec rm {} +
	@find . -type f -name "*.gcno" -exec rm {} +
	@find . -type f -name "*.gcov" -exec rm {} +
else
	@find -type f -name "*.gcda" -delete
	@find -type f -name "*.gcno" -delete
	@find -type f -name "*.gcov" -delete
endif
	@-rm -rf obj/src
	@rm -rf vgcore.*

re: fclean all

debug: CXX_FLAGS += $(DEBUG_FLAGS)
debug: FAST_FLAGS = -Og
debug: re

%.o: %.cpp
	@$(COMPILER) $(CXX_FLAGS) $(FAST_FLAGS) $(INCLUDE) -c $< -o $@

tests_run: gen_ninja all
	@ninja test
	@mv test zappy_gui_tests
	@mv zappy_gui_tests ../

.PHONY: all clean
