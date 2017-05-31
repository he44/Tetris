/* types.h - Defines to use the familiar explicitly-sized types in this
 * OS (uint32_t, int8_t, etc.).  This is necessary because we don't want
 * to include <stdint.h> when building this OS
 * vim:ts=4 noexpandtab
 */

#ifndef _TYPES_H
#define _TYPES_H

#ifndef ASM

/* Types defined here just like in <stdint.h> */
typedef int int32_t;
typedef unsigned int uint32_t;

typedef short int16_t;
typedef unsigned short uint16_t;

//typedef char int8_t;
typedef unsigned char uint8_t;


/*	Constants related to game board	*/
#define BOARD_WIDTH 10	//number of cells on game_board
#define BOARD_HEIGHT 20

#define size_cell 35	//number of pixel on one side of the cell
#define board_start_x 50	//starting pixel index of the game board
#define board_start_y 50

/*	Constants related to piece	*/
#define CELL_PP 4	// number of cells per piece is always 4
#define PIECE_TYPE 7	//there are 7 different shapes for a piece
#define ROTATION_TYPE 4	//there are 4 rotations for a piece(may be the same)
#define O_Shape 0	//yellow
#define	I_Shape 1	//cyan
#define T_Shape 2	//purple
#define L_Shape 3	//orange
#define J_Shape 4	//blue
#define S_Shape 5	//lime	
#define Z_Shape	6	//red






#endif /* ASM */

#endif /* _TYPES_H */
