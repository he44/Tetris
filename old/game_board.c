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
/*	start_game
	INPUT:	NONE
	OUTPUT:	0
	EFFECT:	This function is called beforing starting the game.
			It should clear the game board and set necessary constants
			It may also need to set up keyboard, timing and SDL for later.
*/
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

int32_t check_clear_line()
{
	
	return 0;
	// int row;
	// for (row = BOARD_HEIGHT - 1; row >=0; --row){

	// }
}

/*----------------------------------------------------------------------------*/
/*						Helper Functions for game process					  */
/*----------------------------------------------------------------------------*/
/*	clear_board
	INPUT:	NONE
	OUTPUT:	NONE
	EFFECT: This function clears the game board by putting Zero/Nothing in every
			cell
*/

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


/*----------------------------------------------------------------------------*/
/*						Functions for Debugging						  		  */
/*----------------------------------------------------------------------------*/
/*	terminal_print_board
	INPUT:	NONE
	OUTPUT:	0
	EFFECT:	This function prints out the current game board in the terminal
			This function is supposed to be used while debugging 
*/

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
