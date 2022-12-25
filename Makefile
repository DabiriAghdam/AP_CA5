CC := g++ -std=c++11
CCFLAGS += -l SDL2 -l SDL2_image -l SDL2_ttf -l SDL2_mixer

all: Main.out

Main.out: Main.o rsdl.o Map_Handler.o Event_Handler.o Physics_Handler.o Game_Window.o \
Mario.o Block.o Pipe.o Flag.o Brick.o Health_Mushroom.o Red_Mushroom.o Gomba.o Koopa.o 
	$(CC) Main.o rsdl.o Map_Handler.o Event_Handler.o Physics_Handler.o Game_Window.o Mario.o Block.o Pipe.o Flag.o Brick.o Health_Mushroom.o Red_Mushroom.o Gomba.o Koopa.o $(CCFLAGS) -o Main.out

Main.o: Main.cpp Game_Window.hpp
	$(CC) -c Main.cpp -o Main.o

Koopa.o: Koopa.cpp	Koopa.hpp Game_Window.hpp
	$(CC) -c Koopa.cpp -o Koopa.o

Gomba.o: Gomba.cpp Gomba.hpp Game_Window.hpp
	$(CC) -c Gomba.cpp -o Gomba.o

Red_Mushroom.o: Red_Mushroom.cpp Red_Mushroom.hpp Game_Window.hpp
	$(CC) -c Red_Mushroom.cpp -o Red_Mushroom.o

Health_Mushroom.o: Health_Mushroom.cpp Health_Mushroom.hpp Game_Window.hpp
	$(CC) -c Health_Mushroom.cpp -o Health_Mushroom.o

Brick.o: Brick.cpp Brick.hpp Game_Window.hpp
	$(CC) -c Brick.cpp -o Brick.o

Flag.o: Flag.cpp Flag.hpp Game_Window.hpp
	$(CC) -c Flag.cpp -o Flag.o

Pipe.o: Pipe.cpp Pipe.hpp Game_Window.hpp
	$(CC) -c Pipe.cpp -o Pipe.o

Block.o: Block.cpp Block.hpp Game_Window.hpp
	$(CC) -c Block.cpp -o Block.o

Mario.o: Mario.cpp Mario.hpp Game_Window.hpp
	$(CC) -c Mario.cpp -o Mario.o

Physics_Handler.o: Physics_Handler.cpp Physics_Handler.hpp Game_Window.hpp
	$(CC) -c Physics_Handler.cpp -o Physics_Handler.o

Event_Handler.o: Event_Handler.cpp Event_Handler.hpp Game_Window.hpp
	$(CC) -c Event_Handler.cpp -o Event_Handler.o
	
Map_Handler.o: Map_Handler.cpp Map_Handler.hpp
	$(CC) -c Map_Handler.cpp -o Map_Handler.o

Game_Window.o: Game_Window.cpp Game_Window.hpp rsdl.hpp Map_Handler.hpp Event_Handler.hpp Mario.hpp \
Block.hpp Pipe.hpp Flag.hpp Brick.hpp Health_Mushroom.hpp Red_Mushroom.hpp Koopa.hpp Gomba.hpp
	$(CC) -c Game_Window.cpp -o Game_Window.o

rsdl.o: rsdl.cpp rsdl.hpp
	$(CC) -c rsdl.cpp -o rsdl.o

.PHONY: clean
clean:
	rm -r *.o