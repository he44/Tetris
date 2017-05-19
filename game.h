#ifndef _GAME_H
#define _GAME_H

#include "window.h"
#include "types.h"

/*	in terms of cells	*/
#define BOARD_WIDTH 10
#define BOARD_HEIGHT 20
/*	in terms of pixels	*/
#define size_cell 35
#define board_start_x 50
#define board_start_y 50


class Game
{
	public:
		/*	Creates a default game	*/
		Game();
		/*	Constructs a game with desired board dimension	*/
		Game(int32_t width_arg, int32_t height_arg);
		/*	Copy Constructor	*/
		Game(Game const & other);
		/*	Destructor	*/
		~Game();
		/*	Assignment Operator	*/
		Game const & operator=(Game const & other);

		/*	Draw the board on SFML window	*/
		void draw_board(sf::RenderWindow* cur_window);
	private:
		/*	Private Fields	*/
		int32_t width;	//width of game board in terms of cells
		int32_t height;	//height of game board in terms of cells
		sf::RectangleShape* board;	//pointer to an array of width * height
		int8_t status;	//status of the game, 
						//1 means still going, 0 menas done/not started

		/*	Private Helper Functions	*/
		void clear();
		void copy(Game const & other);
};

#endif