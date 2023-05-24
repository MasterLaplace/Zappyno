##
## EPITECH PROJECT, 2023
## B-YEP-400-REN-4-1-zappy
## File description:
## Makefile
##

all:
	@ $(MAKE) -C Client
	@ $(MAKE) -C GUI
	@ $(MAKE) -C Server

clean:
	@ $(MAKE) -C Client clean
	@ $(MAKE) -C GUI clean
	@ $(MAKE) -C Server clean
	@rm -f zappy_gui_tests
	@rm -f zappy_server_tests
	@rm -f zappy_gui
	@rm -f zappy_server
	@rm -f zappy_ai
	@rm -f build.ninja

fclean: clean
	@ $(MAKE) -C Client fclean
	@ $(MAKE) -C GUI fclean
	@ $(MAKE) -C Server fclean

tests_run:
	@ $(MAKE) -C GUI tests_run
	@ $(MAKE) -C Server tests_run

re:
	@ $(MAKE) -C Client re
	@ $(MAKE) -C GUI re
	@ $(MAKE) -C Server re

.PHONY: all clean fclean re tests_run


# Variables (do not edit)
NO_PRINT = --no-print-directory

# Color definitions
DEFAULT = "\033[00m"
BOLD = "\e[1m"
RED = "\e[31m"
GREEN = "\e[32m"
LIGHT_BLUE = "\e[94m"
WHITE = "\e[1;37m"

all: Client GUI Server
	@echo $(BOLD) $(GREEN)"\n► ALL 👷 !"$(DEFAULT)

Client:
	@$(MAKE) all -C ./GUI/ $(NO_PRINT)
	@echo $(BOLD) $(GREEN)"\n► GUI ⛽ !"$(DEFAULT)
clean_Client:
	@$(MAKE) fclean -C ./GUI/ $(NO_PRINT)
	@echo $(BOLD) $(GREEN)"\n► FCLEAN GUI 🧻 !"$(DEFAULT)

Server:
	@$(MAKE) all -C ./GUI/ $(NO_PRINT)
	@echo $(BOLD) $(GREEN)"\n► GUI ⛽ !"$(DEFAULT)
clean_Server:
	@$(MAKE) fclean -C ./GUI/ $(NO_PRINT)
	@echo $(BOLD) $(GREEN)"\n► FCLEAN GUI 🧻 !"$(DEFAULT)

GUI:
	@$(MAKE) all -C ./GUI/ $(NO_PRINT)
	@echo $(BOLD) $(GREEN)"\n► GUI ⛽ !"$(DEFAULT)
clean_GUI:
	@$(MAKE) fclean -C ./GUI/ $(NO_PRINT)
	@echo $(BOLD) $(GREEN)"\n► FCLEAN GUI 🧻 !"$(DEFAULT)

clean: clean_Client clean_Server clean_GUI
	@echo $(BOLD) $(GREEN)"\n► CLEAN 💨 !"$(DEFAULT)

fclean: clean
	@rm -f vgcore.*
	@echo $(BOLD) $(GREEN)"\n► FCLEAN 🧻 !"$(DEFAULT)

re: fclean all

debug:
	@$(MAKE) debug -C ./GUI/ $(NO_PRINT)
	@echo $(BOLD) $(GREEN)"\n► DEBUG 🔧 !"$(DEFAULT)

.PHONY: all clean fclean re
