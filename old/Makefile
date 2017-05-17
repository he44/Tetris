CC=gcc
CFLAGS=-g -std=c99 -Wall #-Werror

all: tetris

tetris: main.o game_board.o video.o
	$(CC) $(CFLAGS) main.o game_board.o video.o -o tetris 

main.o: main.c
	$(CC) $(CFLAGS) -c main.c `sdl2-config --cflags --lib`

game_board.o: game_board.c
	$(CC) $(CFLAGS) -c game_board.c

video.o: video.c
	$(CC) $(CFLAGS) -c video.c 


clean:
	rm -f video.o game_board.o main.o tetris
