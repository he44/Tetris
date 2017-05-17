#ifndef _G_BOARD_H
#define _G_BOARD_H

#include <stdio.h>
#include "types.h"

/*		Constants		*/
#define BOARD_HEIGHT 20
#define BOARD_WIDTH 10


extern uint8_t game_board[BOARD_HEIGHT*BOARD_WIDTH];


/*		Functions for game progess		*/
int32_t start_game();
int32_t set_piece();

/*		Helper Functions for game progress		*/
int32_t clear_board();


/*		Functions for debugging		*/
int32_t terminal_print_board();




#endif