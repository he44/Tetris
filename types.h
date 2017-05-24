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

/*	in terms of cells	*/
#define BOARD_WIDTH 10
#define BOARD_HEIGHT 20
/*	in terms of pixels	*/
#define size_cell 35
#define board_start_x 50
#define board_start_y 50
// number of cells per piece is always 4
#define CELL_PP 4
#define PIECE_TYPE 7
#define O_Shape 0	//yellow
#define	I_Shape 1	//cyan
#define T_Shape 2	//purple
#define L_Shape 3	//orange
#define J_Shape 4	//blue
#define S_Shape 5	//lime	
#define Z_Shape	6	//red


#endif /* ASM */

#endif /* _TYPES_H */
