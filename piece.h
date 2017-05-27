#ifndef _PIECE_H
#define _PIECE_H

#include "window.h"
#include "types.h"
#include "game.h"
#include <time.h>
#include <stdlib.h>

extern int default_x[PIECE_TYPE][CELL_PP];
extern int default_y[PIECE_TYPE][CELL_PP];
extern sf::Color default_color[PIECE_TYPE];

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