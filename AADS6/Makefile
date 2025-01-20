CC=g++
FLG=-std=c++14 -Wall -Werror -Wextra

all: compile run

compile:
	$(CC) $(FLG) handler.cpp -o handler

run:
	.\handler.exe

run_nf:
	$(CC) handler.cpp -o handler
	.\handler.exe

clear:
	del /q *.exe

rebuild: clear all