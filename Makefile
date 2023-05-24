##
## EPITECH PROJECT, 2023
## B-YEP-400-REN-4-1-zappy
## File description:
## Makefile
##

NO_PRINT = --no-print-directory

DEFAULT = "\033[00m"
BOLD = "\e[1m"
RED = "\e[31m"
GREEN = "\e[32m"
LIGHT_BLUE = "\e[94m"
WHITE = "\e[1;37m"

all: gui
	@echo $(BOLD) $(GREEN)"\n► ALL 👷 !"$(DEFAULT)

gui:
	@make all -C ./GUI/ $(NO_PRINT)
	@echo $(BOLD) $(GREEN)"\n► GUI ⛽ !"$(DEFAULT)
clean_gui:
	@make fclean -C ./GUI/ $(NO_PRINT)
	@echo $(BOLD) $(GREEN)"\n► FCLEAN GUI 🧻 !"$(DEFAULT)

clean:
	@make clean -C ./GUI/ $(NO_PRINT)
	@echo $(BOLD) $(GREEN)"\n► CLEAN 💨 !"$(DEFAULT)

fclean:
	@rm -f vgcore.*
	@make fclean -C ./GUI/ $(NO_PRINT)
	@echo $(BOLD) $(GREEN)"\n► FCLEAN 🧻 !"$(DEFAULT)

re: fclean all

debug:
	@make debug -C ./GUI/ $(NO_PRINT)
	@echo $(BOLD) $(GREEN)"\n► DEBUG 🔧 !"$(DEFAULT)

.PHONY: all clean fclean re
