/*									
 *
 * game.h - header file contatining Game class definitions and function lists
 *
 * "Copyright (c) 2017 by Yuchen He."
 * Permission to use, copy, modify, and distribute this software and its
 * documentation for any purpose, without fee, and without written agreement is
 * hereby granted, provided that the above copyright notice and the following
 * two paragraphs appear in all copies of this software.
 * 
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE TO ANY PARTY FOR DIRECT, INDIRECT, 
 * SPECIAL, INCIDENTAL, OR CONSEQUENTIAL DAMAGES ARISING OUT OF THE USE OF THIS 
 * SOFTWARE AND ITS DOCUMENTATION, EVEN IF THE AUTHOR HAS BEEN ADVISED OF THE 
 * POSSIBILITY OF SUCH DAMAGE.
 * 
 * THE AUTHOR SPECIFICALLY DISCLAIM ANY WARRANTIES, INCLUDING, BUT NOT LIMITED 
 * TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR 
 * PURPOSE.  THE SOFTWARE PROVIDED HEREUNDER IS ON AN "AS IS" BASIS, AND THE 
 * AUTHOR HAS NO OBLIGATION TO PROVIDE MAINTENANCE, SUPPORT, UPDATES, 
 * ENHANCEMENTS, OR MODIFICATIONS."
 *
 * Author:	    	Yuchen He
 * Version:	    	1
 * Creation Date:   2017-05-18
 * Filename:	    game.h
 * History:
 * Notice:			
 */

#ifndef _GAME_H
#define _GAME_H

// #include "window.h"
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
		int isOccupied(int* x, int* y);
		int is_LeftBound(int* x, int* y);
		int is_RightBound(int* x, int* y);
		int is_LockDown(int* x, int* y);
		void lockDown(int* x, int* y, sf::RectangleShape* cells);
		void clearLine();
		void clearLine_helper(int row);
		void setPosition(int r, int c);

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