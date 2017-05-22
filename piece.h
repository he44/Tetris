#ifndef _PIECE_H
#define _PIECE_H

#include "window.h"
#include "types.h"

// number of cells per piece is always 4
#define CELL_PP 4



class Piece
{
public:	
	/*	Default Constructor	*/
	Piece();
	/*	Copy Constructor */
	Piece(Piece const & other);
	/*	Constuctor with the shape and rotation constant	*/
	Piece(int8_t shape_arg, int8_t rotation_arg);
	/*	assignment operator	*/
	Piece const & operator=(Piece const & other);
	/*	Destructor	*/
	~Piece();

	void active_piece_fall();
	void active_piece_draw();

private:
	int8_t shape;
	int8_t rotation;
	sf::RectangleShape* cells;
	uint8_t* x_coord;
	uint8_t* y_coord;

	void clear();
	void copy(Piece const & other);
};

static Piece* uni_active_piece = NULL;

#endif