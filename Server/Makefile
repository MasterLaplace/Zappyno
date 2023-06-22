##
## EPITECH PROJECT, 2023
## B-YEP-400-REN-4-1-zappy-tristan.bros
## File description:
## Makefile for Server
##

# Project settings
NAME         = ../zappy_server
COMPILER     = gcc
SRC_DIR      = src/
SRC_TEST_DIR = tests/
SRC          = $(shell find $(SRC_DIR) -name '*.c')
SRC_TEST     = $(shell find $(SRC_TEST_DIR) -name '*.c')

OBJ          = $(SRC:.c=.o)
INCLUDE      = -iquote ./include/
C_FLAGS    = -Wall -Wextra -std=c99 -Wpedantic
FAST_FLAGS   = -g3 -ggdb
TEST_FLAGS   = -lcriterion --coverage

# Targets
all: $(NAME)

$(NAME): $(OBJ)
	@$(COMPILER) -o $(NAME) $(OBJ) $(C_FLAGS) $(FAST_FLAGS) $(INCLUDE)
	@make -s CLEAN_BUILD_FILES
	@make -s COMPLETE_TEXT

%.o: %.cpp
	$(eval counter=$(shell echo $$(($(counter)+1))))
	$(eval percentage=$(shell echo $$((($(counter) * 100) /\
	$(TOTAL_FILES)))))
	@printf "$(PYELLOW)$(PBOLD)↦🔹[%s] ($(percentage)%%)$(PRESET)" "$(subst $(shell pwd)/,,$<)"
	@$(COMPILER) -c $(C_FLAGS) $(FAST_FLAGS) $(INCLUDE) $< -o $@
	@printf "\r$(PGREEN)$(PBOLD)↦🔹[%s] ($(percentage)%%)$(PRESET)\n" "$(subst $(shell pwd)/,,$<)"; \

clean:
	@make -s CLEAN_TEXT
	@rm -f $(OBJ)
	@rm -f *.gcda
	@rm -f *.gcno
	@rm -f *.gcov

fclean: clean
	@rm -f $(NAME)

re: fclean all

tests_run: fclean
	@make -s CLEAN_TEXT
	@make -s CLEAN_BUILD_FILES
	@make -s COMPLETE_TEXT
	@printf "$(PBOLD) $(PBLUEC) RUNNING TESTS 🧪\n"
	@$(COMPILER) -o zappy_server_tests $(SRC) $(SRC_TEST) $(TEST_FLAGS) $(FAST_FLAGS) $(INCLUDE)
	@./zappy_server_tests -h
	@make -s CLEAN_BUILD_FILES
	@make -s COMPLETE_TEXT


debug: C_FLAGS += -g3 -ggdb
debug: FAST_FLAGS = -O0
debug: re
	@printf "$(PYELLOW)$(PBOLD) ⚠ Debug mode ON$(PRESET)\n"
	@printf "\033[1m\033[37mflags: $(C_FLAGS) $(FAST_FLAGS)\033[0m\n\n"

debug_IPC: C_FLAGS += -DIPC_DEBUG
debug_IPC: debug
# Silent targets
.SILENT: CLEAN_TEXT COMPLETE_TEXT BUILD_FAIL CLEAN_BUILD_FILES

CLEAN_TEXT:
	@printf "$(PBOLD) $(PBLUEC) CLEANING 🧹\n"

COMPLETE_TEXT:
	@printf "$(PBOLD) $(PGREEN) BUILD COMPLETED 🏗️\n"

BUILD_FAIL: CLEAN_BUILD_FILES
	@printf "$(PBOLD) $(PRED) BUILD FAILED 🚨\n"

CLEAN_BUILD_FILES:
	@printf "$(PBOLD) $(PBLUEC) CLEANING BUILD FILES 🧹\n"
	rm -f build.exit.0;
	rm -f build.exit.1;
	rm -f build.log;

.DELETE_ON_ERROR:
	@printf "$(PBOLD) $(PRED) ERROR CLEANING BUILD FILES 🧹\n"
	rm -f build.exit.0;
	rm -f build.exit.1;
	rm -f build.log;

.PHONY: all clean fclean re debug tests_run


# Variables (do not edit)

# Counters
TOTAL_FILES  = $(words $(SRC))
counter      = 0

# Color definitions
PGREEN   = \033[32m
PRED     = \033[31m
PORANGE  = \033[38;5;208m
PYELLOW  = \033[33m
PBLUE    = \033[34m
PBLUEC   = \033[36m
PRESET   = \033[0m
PBOLD    = \033[1m
