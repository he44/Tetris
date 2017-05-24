#include "piece.h"

int default_x[7][4] = 
{
	{4, 5, 4, 5}, 
	{3, 4, 5, 6}, 
	{4, 3, 4, 5}, 
	{5, 3, 4, 5}, 
	{3, 3, 4, 5}, 
	{4, 5, 3, 4}, 
	{3, 4, 4, 5}
};

int default_y[7][4] = 
{
	{0, 0, 1, 1}, 
	{0, 0, 0, 0}, 
	{0, 1, 1, 1}, 
	{0, 1, 1, 1}, 
	{0, 1, 1, 1}, 
	{0, 0, 1, 1}, 
	{0, 0, 1, 1}
};

sf::Color default_color[PIECE_TYPE] = 
{
	sf::Color::Yellow, sf::Color::Cyan, sf::Color(128,0,128), 
	sf::Color(255,165,0),  sf::Color::Blue, sf::Color(50,205,50), 
	sf::Color::Red
};

/*	Default Constructor
	INPUT:	NONE
	OUTPUT:	A default piece object
	EFFECT:	This function is callled every time we want to create a piece 
			object. This function will fill the new piece with default info.
			The piece will basically be unrecognizeable and has nothing in it.
*/
Piece::Piece()
{                
	shape = -1;
	rotation = -1;
	cells = NULL;
	x_coord = NULL;
	y_coord = NULL;
}

/*	Copy Constructor
	INPUT:	other -- reference to another piece object
	OUTPUT:	a new piece object that is the same as the input
	EFFECT:	It copies all the information from the "other" piece object to the 
			new one. For the fields dynamically allocated, this constructor will
			allocate new fields and then copy the information
*/
Piece::Piece(Piece const & other)
{
	copy(other);
}

/*	Constructor with parameter
	INPUT:	shape_arg -- denoting the shape of the new piece
	OUTPUT:
	EFFECT:
*/
Piece::Piece(int8_t shape_arg)
{
	if (shape_arg < 0 || shape_arg > PIECE_TYPE){
		cout << "Invalid shape_arg " << endl;
		return;
	}
	shape = shape_arg;
	rotation = 0;
	cells = new sf::RectangleShape[CELL_PP];
	x_coord = new int[CELL_PP];
	y_coord = new int[CELL_PP];
	int i;
	int pos_x = 0;
	int pos_y = 0;
	for(i = 0; i < CELL_PP; ++i){
		x_coord[i] = default_x[shape][i];
		y_coord[i] = default_y[shape][i];
	}
	for(i = 0; i < CELL_PP; ++i){
		cells[i].setSize(sf::Vector2f(size_cell, size_cell));
		cells[i].setFillColor(default_color[shape]);
		cells[i].setOutlineThickness(-1);
		cells[i].setOutlineColor(sf::Color::White);
		pos_x = board_start_x + x_coord[i] * size_cell;
		pos_y = board_start_y + y_coord[i] * size_cell;
		cells[i].setPosition(sf::Vector2f(pos_x, pos_y));
	}
}

/*	Assignment Operator
	INPUT:	other -- reference to another piece object
	OUTPUT:	a new piece object that is the same as the input
	EFFECT:	It copies all the information from the "other" piece object to the 
			new one. For the fields dynamically allocated, this constructor will
			allocate new fields and then copy the information
*/
Piece const & Piece::operator=(Piece const & other)
{
	if (this != &other){
		clear();
		copy(other);
	}
	return *this;
}

/*	Destructor
	INPUT:	NONE
	OUTPUT:	NONE
	EFFECT:	
*/
Piece::~Piece()
{
	clear();
}	

/*	active_soft_drop
	INPUT:	NONE
	OUTPUT:	NONE
	EFFECT:	This function should be called at every periodic interrupt of the 
			game. It moves the active piece one cell lower.
*/
void Piece::soft_drop()
{
	int pos_x = 0;
	int pos_y = 0;
	for(int i = 0; i < CELL_PP; ++i){
		(y_coord[i]) ++;
		pos_x = board_start_x + x_coord[i] * size_cell;
		pos_y = board_start_y + y_coord[i] * size_cell;
		cells[i].setPosition(sf::Vector2f(pos_x, pos_y));
	}
}

/*	is_LockDown
	INPUT:	game -- pointer to the current Game object
	OUTPUT:	1 -- the piece cannot soft-drop/move anymore
			-> should generate new active piece
			0 -- the piece can still soft-drop/move
			-> should continue dropping this piece
	EFFECT:	This function should be called at every "periodic interrupt", before
			dropping the active piece
*/
int Piece::is_LockDown(Game* game)
{
	/*	Get coordinate of current piece	*/
	int* cur_x = new int[CELL_PP];
	int* cur_y = new int[CELL_PP];
	for(int i = 0; i < CELL_PP; ++i){
		cur_x[i] = this->x_coord[i];
	 	cur_y[i] = this->y_coord[i];
	}
	/*	Compare coordinate of current piece to the game board	*/
	/*	Special Case: at the bottom	 */
	if (cur_y[0] >= (BOARD_HEIGHT-1) || cur_y[1] >= (BOARD_HEIGHT-1) 
		|| cur_y[2] >= (BOARD_HEIGHT-1) || cur_y[3] >= (BOARD_HEIGHT-1))
	{return 1;}
	/*	Ordinary Case: check the next piece in vertical direction	*/
	// The thing here is we need the private field from the game object
	// i.e. the bool_board field
	// so i think it might be better to have two functions of the same name
	// in two classes
	return game->is_LockDown(cur_x, cur_y);	
}

/*	lockDown
	INPUT:	game -- pointer to the current Game object
	OUTPUT:	NONE
	EFFECT:	This function will lock down the active piece by marking the cells
			in game->status_board as occupied. 
			This function will also copy the corresponding shape information 
			from the piece field to the game field
			This function should be called in the main loop, if is_LockDown
			returns 1 
*/
void Piece::lockDown(Game* game)
{
	/*	Get coordinate and shape information of current piece	*/
	int* cur_x = new int[CELL_PP];
	int* cur_y = new int[CELL_PP];
	sf::RectangleShape* minos = new sf::RectangleShape[CELL_PP];
	for(int i = 0; i < CELL_PP; ++i){
		cur_x[i] = this->x_coord[i];
	 	cur_y[i] = this->y_coord[i];
	 	minos[i] = this->cells[i];
	}

	game->lockDown(cur_x, cur_y, minos);

}

/*	active_piece_draw
	INPUT:	NONE
	OUTPUT:	NONE
	EFFECT:	This function should be called in the "drawing" section of the main
			loop. It draws the 4 cells of the active piece into the current 
			window. 
*/
void Piece::draw_piece(sf::RenderWindow* cur_window)
{
	for(int i = 0; i < CELL_PP; i++){
		cur_window->draw(cells[i]);
	}
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
	cells = new sf::RectangleShape[CELL_PP];
	x_coord = new int[CELL_PP];
	y_coord = new int[CELL_PP];
	for (int i = 0; i < CELL_PP; ++i){
		cells[i] = other.cells[i];
		x_coord[i] = other.x_coord[i];
		y_coord[i] = other.y_coord[i];
	}
}