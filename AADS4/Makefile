CC=g++
FLG=-std=c++14 -Wall -Werror -Wextra

all: cpmrun

run:
	.\handler.exe

cpmrun: handler
	.\handler.exe

handler:
	$(CC) $(FLG) handler.cpp hashtable.cpp -o handler

clear:
	del /q *.exe

rebuild: clear all