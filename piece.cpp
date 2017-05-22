#include "piece.h"

Piece::Piece()
{
	shape = -1;
	rotation = -1;
	cells = new sf::RectangleShape[CELL_PP];
	x_coord = new uint8_t[CELL_PP];
	y_coord = new uint8_t[CELL_PP];
}

Piece::Piece(Piece const & other)
{
	copy(other);
}

Piece::Piece(int8_t shape_arg, int8_t rotation_arg)
{

}


Piece const & Piece::operator=(Piece const & other)
{
	if (this != &other){
		clear();
		copy(other);
	}
	return *this;
}

Piece::~Piece()
{
	clear();
}	

/*	active_piece_fall
	INPUT:	NONE
	OUTPUT:	NONE
	EFFECT:
*/
void Piece::active_piece_fall()
{

}

/*	active_piece_draw
	INPUT:	NONE
	OUTPUT:	NONE
	EFFECT:
*/
void Piece::active_piece_draw()
{

}

void Piece::clear()
{
	shape = -1;
	rotation = -1;
	delete [] cells;
	delete [] x_coord;
	delete [] y_coord;
	cells = NULL;
	x_coord = NULL;
	y_coord = NULL;
}

void Piece::copy(Piece const & other)
{
	shape = other.shape;
	rotation = other.rotation;
	for (int i = 0; i < CELL_PP; ++i){
		cells[i] = other.cells[i];
		x_coord[i] = other.x_coord[i];
		y_coord[i] = other.y_coord[i];
	}
}
