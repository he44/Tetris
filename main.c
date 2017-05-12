#include "game_board.h"

int main()
{
	start_game();
	terminal_print_board();
	printf("--------------------------\n");
	set_piece();
	terminal_print_board();
	return 0;
}