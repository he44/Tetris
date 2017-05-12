CC=gcc
CFLAGS=-g -std=c99 -Wall #-Werror

all: tetris

# mp10: main.o sparsemat.o
# 	$(CC) $(CFLAGS) main.o sparsemat.o cmp_mat.o -o mp10

tetris: main.o game_board.o
	$(CC) $(CFLAGS) main.o game_board.o -o tetris

main.o: main.c
	$(CC) $(CFLAGS) -c main.c

# sparsemat.o: sparsemat.c
# 	$(CC) $(CFLAGS) -c sparsemat.c

game_board.o: game_board.c
	$(CC) $(CFLAGS) -c game_board.c


clean:
	rm -f game_board.o main.o tetris
