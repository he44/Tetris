#include "game.h"

/*	Game::Game()	Default Constructor
	INPUT:	NONE
	OUTPUT:	A default Game object
	EFFECT:	Creates a Game object with board size 0*0 and
			NULL board pointer
*/
Game::Game()
{
	width = 0;
	height = 0;
	bool_board = NULL;
	board = NULL;
	status = 0;
}

/*	Game::Game(width_arg, height_arg)
	INPUT:	width_arg -- desired width of game board
			height_arg -- desired height of game board
	OUTPUT:	A Game object with board of size width_arg * height_arg
	EFFECT: Creates a Game object with desired dimension
			and board pointer to a corresponding uint8_t array
*/
Game::Game(int32_t width_arg, int32_t height_arg)
{
	if(width_arg <= 0 || height_arg <= 0){
		cout << "width is " << width << endl;
		cout << "height is " << height << endl;
		cout << "Invalid Board Dimension" << endl;
		return;
	}
	this->width = width_arg;
	this->height = height_arg;
	this->bool_board = new int8_t[width_arg * height_arg];
	this->board = new sf::RectangleShape[width_arg * height_arg];		
	this->status = 1;
	/*	fill in all "cell" with default properties	*/
	int i = 0;
	int pos_x = 0;
	int pos_y = 0;
	for (int row = 0; row < height_arg; ++row){
		for (int col = 0; col < width_arg; ++col){
			i = row * width_arg + col;
			pos_x = board_start_x + col * size_cell;
			pos_y = board_start_y + row * size_cell;
			//	the cell is not occupied yet
			(this->bool_board)[i] = 0;
			//	resize the rectangle to single square "cell"	
			(this->board)[i].setSize(sf::Vector2f(size_cell,size_cell));			
			//	set the fill color to blue(just to see if it works)
			(this->board)[i].setFillColor(sf::Color(135, 206, 235));
			//	set the location of the shape 
			(this->board)[i].setPosition(sf::Vector2f(pos_x, pos_y));
			//	set the outline of the shape
			(this->board)[i].setOutlineThickness(-1);
			(this->board)[i].setOutlineColor(sf::Color::White);
		}
	}


}

/*	Game::Game(other)	Copy Constructor
	INPUT:	other -- reference to another Game object
	OUPUT:	a Game object which is the same as other
	EFFECT:	Creates a new Game object by copying everything from other
*/
Game::Game(Game const & other)
{
	copy(other);
}
		

/*	Game::~Game()	Destructor	
	INPUT:	NONE
	OUTPUT:	NONE
	EFFECT:	Destroys a Game object by clearing all related field
*/
Game::~Game()
{
	clear();
}
		
/*	operator=(other)	Assignment Operator	
	INPUT:	other -- reference to another Game object
	OUTPUT:	NONE
	EFFECT:	Assign everything from another Game object to this Game
			object
*/
Game const & Game::operator=(Game const & other)
{
	if(this != &other){
		clear();
		copy(other);
	}
	return *this;
}

/*	is_LeftBound
	INPUT:	x -- pointer to four x_coordinate values of active piece
			y -- pointer to four y_coordinate values of active piece
	OUTPUT:	0 -- the active piece cannot move toward left
			1 -- the active piece can still move toward left
	EFFECT:	This function returns wheter the active piece has blocking cells on
			the left side.
			It should be callled in Piece::moveLeft()
*/
int Game::is_LeftBound(int* x, int* y)
{
	int ret = 0;
	for(int i = 0; i < CELL_PP; ++i){
		ret |= bool_board[x[i] - 1 + y[i] * BOARD_WIDTH];
	}
	return ret;
}

/*	is_RightBound
	INPUT:	x -- pointer to four x_coordinate values of active piece
			y -- pointer to four y_coordinate values of active piece
	OUTPUT:	0 -- the active piece cannot move toward right
			1 -- the active piece can still move toward right
	EFFECT:	This function returns wheter the active piece has blocking cells on
			the right side.
			It should be callled in Piece::moveRight()
*/
int Game::is_RightBound(int* x, int* y)
{
	int ret = 0;
	for(int i = 0; i < CELL_PP; ++i){
		ret |= bool_board[x[i] + 1 + y[i] * BOARD_WIDTH];
	}
	return ret;
}

/*	is_LockDown
	INPUT:	x -- pointer to four x_coordinate values of active piece
			y -- pointer to four y_coordinate values of active piece
	OUTPUT:	1 -- the piece cannot soft-drop/move anymore
			-> should generate new active piece
			0 -- the piece can still soft-drop/move
			-> should continue dropping this piece
	EFFECT:	This function is called inside the is_LockDown function from
			piece class. In the main loop, this function is called at every 
			periodic interrupt, before "dropping" the active piece
*/
int Game::is_LockDown(int* x, int* y)
{
	int ret = 0;
	for(int i = 0; i < CELL_PP; ++i){
		ret |= bool_board[x[i] + (y[i]+1) * BOARD_WIDTH];
	} 
	return ret;
}

/*	lockDown
	INPUT:	x -- pointer to four x_coordinate values of active piece
			y -- pointer to four y_coordinate values of active piece
	OUTPUT:	NONE
	EFFECT:	This function will add the active piece to the current game_board.
			From the player, a new active piece should appear from the top and 
			the old one should not be allowed to move.
			From my code, the old active piece will be drawn within main_game
			instead of act_piece.
*/
void Game::lockDown(int* x, int* y, sf::RectangleShape* cells)
{
	for(int i = 0; i < CELL_PP; ++i){
		bool_board[x[i] + y[i] * BOARD_WIDTH] = 1;
		board[x[i] + y[i] * BOARD_WIDTH] = cells[i];
	}
}

/*	clearLine
	INPUT:	NONE
	OUTPUT:	NONE
	EFFECT:
*/
void Game::clearLine()
{
	cout << "in function " << endl;
	int r, c;	//row, col index
	int flag = 1;
	for(r = BOARD_HEIGHT; r >= 0; --r){
		flag = 1;
		/*	Check bool_board to see whether occupied	*/
		for(c = 0; c < BOARD_WIDTH; ++c){
			if(bool_board[c + r * BOARD_WIDTH] == 0){
				flag = 0;
			}
		}
		if (flag == 1){
			cout << "here " << endl;
			this->clearLine_helper(r);
		}
	}
}

/*	clearLine_helper()
	INPUT:	row -- the index of the row to be cleared
	OUTPUT:	NONE
	EFFECT:	This function should move all the cells above "row" downward by one
			cell.
*/
void Game::clearLine_helper(int row)
{
	int r, c;
	for(r = row; r >= 0; --r){
		for(c = 0; c < BOARD_WIDTH; ++c){
			if(r == 0){
				//	default cell
				board[c + r * BOARD_WIDTH].setFillColor(sf::Color(135, 206, 235));
				bool_board[c + r * BOARD_WIDTH] = 0;
			} else {
				// cell from the line above
				bool_board[c + r * BOARD_WIDTH] = bool_board[c + (r-1) * BOARD_WIDTH];
				board[c + r * BOARD_WIDTH] = board[c + (r-1) * BOARD_WIDTH];
				setPosition(r, c);
				// board has to reset its location
			}
		}
	}
}

void Game::setPosition(int r, int c)
{
	int pos_x = board_start_x + c * size_cell;
	int pos_y = board_start_y + r * size_cell;
	board[c + r * BOARD_WIDTH].setPosition(pos_x, pos_y);
}


/*	draw_board
	INPUT:	cur_window	-- pointer to the window where we want to draw 
	OUTPUT:	NONE
	EFFECT:	This is supposed to draw the whole game board into window based on
			starting location defined in game.h
*/
void Game::draw_board(sf::RenderWindow* cur_window)
{
	int i = 0;
	for(i = 0; i < (this->width * this->height); ++i){
		cur_window->draw(this->board[i]);
	}
}

/*	copy	private helper function
	INPUT:	other -- reference to another Game object
	OUTPUT:	NONE
	EFFECT:	Assign everything from another Game object to this Game
			object
*/
void Game::copy(Game const & other)
{
	width = other.width;
	height = other.height;
	status = other.status;
	bool_board = new int8_t[width * height];
	board = new sf::RectangleShape[width * height];
	
	for (int r = 0; r < height; r++){
		for (int c = 0; c < width; c++){
			bool_board[r * width + c] = (other.bool_board)[r * width + c];
			board[r * width + c] = (other.board)[r * width + c];		
		}
	}
}

/*	clear	private helper function
	INPUT:	NONE
	OUTPUT:	NONE
	EFFECT:	clearing all related field of this Game object
*/
void Game::clear()
{
	width = 0;
	height = 0;
	delete [] bool_board;
	delete [] board;
	status = 0;
}



