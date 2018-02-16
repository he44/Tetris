/*									
 *
 * piece.h - header file contatining Piece class definitions and function lists
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
 * Creation Date:   2017-05-21
 * Filename:	    piece.h
 * History:
 * Notice:			
 */

#ifndef _PIECE_H
#define _PIECE_H

// #include "window.h"
#include "types.h"
#include "game.h"
#include <time.h>
#include <stdlib.h>

//array to get color for each shape
extern sf::Color default_color[PIECE_TYPE];	
//arrays to get original(newly generated) position for each shape
extern int default_x[PIECE_TYPE][CELL_PP];
extern int default_y[PIECE_TYPE][CELL_PP];
//arrays to get offset for each shape of piece when doing rotation
extern int O_x_offset[ROTATION_TYPE][CELL_PP];
extern int O_y_offset[ROTATION_TYPE][CELL_PP];
extern int I_x_offset[ROTATION_TYPE][CELL_PP];
extern int I_y_offset[ROTATION_TYPE][CELL_PP];
extern int T_x_offset[ROTATION_TYPE][CELL_PP];
extern int T_y_offset[ROTATION_TYPE][CELL_PP];
extern int L_x_offset[ROTATION_TYPE][CELL_PP];
extern int L_y_offset[ROTATION_TYPE][CELL_PP];
extern int J_x_offset[ROTATION_TYPE][CELL_PP];
extern int J_y_offset[ROTATION_TYPE][CELL_PP];
extern int S_x_offset[ROTATION_TYPE][CELL_PP];
extern int S_y_offset[ROTATION_TYPE][CELL_PP];
extern int Z_x_offset[ROTATION_TYPE][CELL_PP];
extern int Z_y_offset[ROTATION_TYPE][CELL_PP];


class Piece
{
public:	
	/*	Default Constructor	*/
	Piece();
	/*	Copy Constructor */
	Piece(Piece const & other);
	/*	Constuctor with the shape and rotation constant	*/
	Piece(int8_t shape_arg);
	/*	assignment operator	*/
	Piece const & operator=(Piece const & other);
	/*	Destructor	*/
	~Piece();
	/*	Functions related to Game Process	*/
	void soft_drop();
	void hard_drop(Game* game);
	int is_LockDown(Game* game);
	void lockDown(Game* game);
	void moveLeft(Game* game);
	void moveRight(Game* game);
	void rotate(Game* game);
	int isOccupied(Game* game);
	/*	Functions related to Video mem	*/
	void draw_piece(sf::RenderWindow* cur_window);

private:
	int8_t locked;
	int8_t shape;
	int8_t rotation;
	sf::RectangleShape* cells;
	int* x_coord;
	int* y_coord;

	void clear();
	void copy(Piece const & other);
};

static Piece* uni_active_piece = NULL;

#endif