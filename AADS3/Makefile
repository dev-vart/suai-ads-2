CC=g++
FLG=-std=c++14 -Wall -Werror -Wextra

all: cpmrun

run:
	.\taskHandler.exe

cpmrun: taskHandler
	.\taskHandler.exe

taskHandler:
	$(CC) $(FLG) taskHandler.cpp stackstruct.cpp taskGen.cpp task.cpp queue.cpp -o taskHandler

clean:
	del /q *.exe

rebuild: clean all