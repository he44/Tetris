CC=g++
CFLAGS=-std=c++1y -stdlib=libc++ -g -O0 $(WARNINGS) -MMD -MP

all:	tetris

tetris:	main.o window.o
	$(CC) main.o window.o -o tetris -lsfml-graphics -lsfml-window -lsfml-system

main.o:	main.cpp
	$(CC) -c main.cpp

window.o: window.cpp
	$(CC) -c window.cpp

clean:
	rm -f window.o main.o tetris	


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
