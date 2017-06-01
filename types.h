/*									
 *
 * types.h - header file contatining Tetris constants and definition of some 
 			 integer data type
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
 * Filename:	    types.h
 * History:
 * Notice:			The portion about typedef is almost the same the contents in
 					file types.h from ECE391 MP3 at University of Illinois.
 */




/* types.h - Defines to use the familiar explicitly-sized types in this
 * OS (uint32_t, int8_t, etc.).  This is necessary because we don't want
 * to include <stdint.h> when building this OS
 * vim:ts=4 noexpandtab
 */

#ifndef _TYPES_H
#define _TYPES_H

#include <SFML/Graphics.hpp>

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


#endif /* _TYPES_H */
