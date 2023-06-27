##
## EPITECH PROJECT, 2023
## B-YEP-400-REN-4-1-zappy
## File description:
## Makefile
##

# Variables (do not edit)
NO_PRINT = --no-print-directory

# Color definitions
DEFAULT = "\033[00m"
BOLD = "\e[1m"
RED = "\e[31m"
GREEN = "\e[32m"
LIGHT_BLUE = "\e[94m"
WHITE = "\e[1;37m"

all: ai gui server

ai:
	ln -sf ./AI/src/main.py ./zappy_ai
	@$(MAKE) all -C ./AI $(NO_PRINT)
	@echo $(BOLD) $(GREEN)"► AI ⛽ !\n"$(DEFAULT)
clean_AI:
	@$(MAKE) clean -C ./AI $(NO_PRINT)
	@echo $(BOLD) $(GREEN)"► CLEAN AI 💨 !\n"$(DEFAULT)
fclean_AI:
	@$(MAKE) fclean -C ./AI $(NO_PRINT)
	@echo $(BOLD) $(GREEN)"► FCLEAN AI 🧻 !\n"$(DEFAULT)

server: fclean_Server
	@$(MAKE) all -C ./Server $(NO_PRINT)
	@echo $(BOLD) $(GREEN)"► SERVER ⛽ !\n"$(DEFAULT)
clean_Server:
	@$(MAKE) clean -C ./Server $(NO_PRINT)
	@echo $(BOLD) $(GREEN)"► CLEAN SERVER 💨 !\n"$(DEFAULT)
fclean_Server:
	@$(MAKE) fclean -C ./Server $(NO_PRINT)
	@echo $(BOLD) $(GREEN)"► FCLEAN SERVER 🧻 !\n"$(DEFAULT)

gui: # fclean_GUI
	@./GUI/Script/norm_checker.py
	@$(MAKE) all -C ./GUI $(NO_PRINT)
	@echo $(BOLD) $(GREEN)"► GUI ⛽ !\n"$(DEFAULT)
clean_GUI:
	@$(MAKE) clean -C ./GUI $(NO_PRINT)
	@echo $(BOLD) $(GREEN)"► CLEAN GUI 💨 !\n"$(DEFAULT)
fclean_GUI:
	@$(MAKE) fclean -C ./GUI $(NO_PRINT)
	@echo $(BOLD) $(GREEN)"► FCLEAN GUI 🧻 !\n"$(DEFAULT)
tests_run_gui:
	@$(MAKE) tests_run -C ./GUI $(NO_PRINT)
	@echo $(BOLD) $(GREEN)"► TESTS GUI 🧪 !\n"$(DEFAULT)

clean: clean_AI clean_GUI clean_Server
	@echo $(BOLD) $(GREEN)"► CLEAN 💨 !\n"$(DEFAULT)

fclean: fclean_AI fclean_GUI fclean_Server
	@$(RM) -rf vgcore.*
	@echo $(BOLD) $(GREEN)"► FCLEAN 🧻 !\n"$(DEFAULT)

re: fclean all

debug:
	@$(MAKE) debug -C ./AI $(NO_PRINT)
	@$(MAKE) debug -C ./GUI $(NO_PRINT)
	@$(MAKE) debug -C ./Server $(NO_PRINT)
	@echo $(BOLD) $(GREEN)"► DEBUG 🔧 !\n"$(DEFAULT)

.PHONY: all clean fclean re ai
