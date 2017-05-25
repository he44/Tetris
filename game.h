#ifndef _GAME_H
#define _GAME_H

#include "window.h"
#include "types.h"


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
		/*	Functions for Game Process	*/
		int is_LockDown(int* x, int* y);
		void lockDown(int* x, int* y, sf::RectangleShape* cells);
		void clearLine();
	private:
		/*	Private Fields	*/
		int32_t width;	//width of game board in terms of cells
		int32_t height;	//height of game board in terms of cells
		int8_t* bool_board;	//pointer to an array of width * height
							//each element has two vals
							//0 means cell occupied, 1 otherwise
		sf::RectangleShape* board;	//pointer to an array of width * height
									//each element is a rectangle shape
		int8_t status;	//status of the game, 
						//1 means still going, 0 menas done/not started

		/*	Private Helper Functions	*/
		void clear();
		void copy(Game const & other);
};

#endif