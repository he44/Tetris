#include "piece.h"

/*	default_x, default_y
	These two arrays contain coordinates for the "newly generated" piece.
	Namely, these two arrays tell the location of each new piece.
	These two arrays are sorted first by PIECE_TYPE, and then by each cell
*/
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

/*	default_color
	This array contains the color associated with each shape of piece:
	O_Shape yellow
	I_Shape cyan
	T_Shape purple
	L_Shape orange
	J_Shape blue
	S_Shape lime	
	Z_Shape	red
*/
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
	locked = 0;
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
			0~6 is assigned to seven different shapes
	OUTPUT:
	EFFECT:
*/
Piece::Piece(int8_t shape_arg)
{
	if (shape_arg < 0 || shape_arg > PIECE_TYPE){
		cout << "Invalid shape_arg " << endl;
		return;
	}
	locked = 0;
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
	EFFECT:	This function will destory a Piece object by calling the private
	helper function: clear()
*/
Piece::~Piece()
{
	clear();
}	

/*	soft_drop
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

/*	hard_drop
	INPUT:	game -- pointer to the current game object
	OUTPUT:	NONE
	EFFECT:	This function should be called when "space" is pressed. 
			It directly moves the active piece to the farthest position possible
			Thus, it's just like doing many soft_drop in a much faster tempo
			Also, this function should lockDown the active piece in the end. 
*/
void Piece::hard_drop(Game* game)
{
	while (! this->is_LockDown(game)){
		this->soft_drop();	
	}
	this->lockDown(game);
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
	this->locked = 1;
	game->lockDown(cur_x, cur_y, minos);

}

/*	moveLeft
	INPUT:	NONE
	OUTPUT:	NONE
	EFFECT:	
*/
void Piece::moveLeft(Game* game)
{
	if (game == NULL){return;}
	//don't move locked piece
	if (this->locked){return;}
	//check left boundary of the game board	
	if (x_coord[0] == 0 || x_coord[1] == 0 ||
		x_coord[2] == 0 || x_coord[3] == 0){return;}
	//check the game board	
	if (game->is_LeftBound(x_coord, y_coord)){return;}
	int i = 0;
	int pos_x, pos_y;
	//change the coordinate and move the piece
	for(i = 0; i < CELL_PP; ++i){
		(x_coord[i])--;
		pos_x = board_start_x + x_coord[i] * size_cell;
		pos_y = board_start_y + y_coord[i] * size_cell;
		cells[i].setPosition(sf::Vector2f(pos_x, pos_y));
	}
}

/*	moveRight
	INPUT:
	OUTPUT:
	EFFECT:
*/
void Piece::moveRight(Game* game)
{
	if (this->locked){return;}
	if (x_coord[0] == BOARD_WIDTH-1 || x_coord[1] == BOARD_WIDTH-1 ||
		x_coord[2] == BOARD_WIDTH-1 || x_coord[3] == BOARD_WIDTH-1){return;}
	//check the game board	
	if (game->is_RightBound(x_coord, y_coord)){return;}
	int i = 0;
	int pos_x, pos_y;
	for(int i = 0; i < CELL_PP; ++i){
		(x_coord[i])++;
		pos_x = board_start_x + x_coord[i] * size_cell;
		pos_y = board_start_y + y_coord[i] * size_cell;
		cells[i].setPosition(sf::Vector2f(pos_x, pos_y));
	}
}

/*	draw_piece
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

/*	clear()	
	INPUT:	NONE
	OUTPUT:	NONE
	EFFECT:	clearing all related field of this Piece object
*/
void Piece::clear()
{
	locked = 0;
	shape = -1;
	rotation = -1;
	delete [] cells;
	delete [] x_coord;
	delete [] y_coord;
	cells = NULL;
	x_coord = NULL;
	y_coord = NULL;
}

/*	copy	
	INPUT:	other -- reference to another Piece object
	OUTPUT:	NONE
	EFFECT:	Assign everything from another Piece object to this Piece
			object
*/
void Piece::copy(Piece const & other)
{
	locked = other.locked;
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
