#include "game_board.h"

uint8_t game_board[BOARD_HEIGHT*BOARD_WIDTH] = 
{	
	0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0, 
	0,0,0,0,0,0,0,0,0,0, 
	0,0,0,0,0,0,0,0,0,0
};

/*----------------------------------------------------------------------------*/
/*						Functions for game process							  */
/*----------------------------------------------------------------------------*/

int32_t start_game()
{
	clear_board();
	return 0;
}


int32_t set_piece()
{
	game_board[35] = 8;
	game_board[74] = 9;
	return 0;
}


int32_t clear_board()
{
	int row, col;
	for (row = 0; row < BOARD_HEIGHT; ++row){
		for (col = 0; col < BOARD_WIDTH; ++col){
			game_board[row*BOARD_WIDTH+col] = 0;
		}
	}
	return 0;
}



int32_t terminal_print_board()
{
	int row, col;
	for (row = 0; row < BOARD_HEIGHT; ++row){
		for (col = 0; col < BOARD_WIDTH; ++col){
			printf("%d ", game_board[row*BOARD_WIDTH+col]);
		}
		printf("\n");
	}
	return 0;
}
