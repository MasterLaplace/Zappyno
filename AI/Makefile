##
## EPITECH PROJECT, 2023
## B-YEP-400-REN-4-1-zappy
## File description:
## Makefile for AI
##

NAME	= ../zappy_ai

PYTHON	= python3

PIP		= pip3

all: install lint type

install:
	$(PIP) install -r ./requirements.txt

lint:
	$(PYTHON) -m pylint src/*.py

type:
	$(PYTHON) -m mypy src/*.py

clean:
	rm -rf __pycache__ .pytest_cache

fclean: clean
	rm -rf $(NAME)

re: clean all

.PHONY: all install lint test clean
