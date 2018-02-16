CC=g++
CFLAGS=-std=c++1y -stdlib=libc++ -g -O0 $(WARNINGS) -MMD -MP

all:	tetris

tetris:	main.o window.o game.o piece.o
	$(CC) main.o window.o game.o piece.o -o tetris -lsfml-graphics -lsfml-window -lsfml-system

main.o:	main.cpp
	$(CC) -c main.cpp

window.o: window.cpp
	$(CC) -c window.cpp

game.o: game.cpp
	$(CC) -c game.cpp

piece.o: piece.cpp
	$(CC) -c piece.cpp

clean:
	rm -f piece.o game.o window.o main.o tetris	


# all: tetris

# tetris: main.o game_board.o video.o
# 	$(CC) $(CFLAGS) main.o game_board.o video.o -o tetris 

# main.o: main.c
# 	$(CC) $(CFLAGS) -c main.c `sdl2-config --cflags --lib`

# game_board.o: game_board.c
# 	$(CC) $(CFLAGS) -c game_board.c

# video.o: video.c
# 	$(CC) $(CFLAGS) -c video.c 


# clean:
# 	rm -f video.o game_board.o main.o tetris
