// *************************************************************************
// scene_matrix.h
// This is a component of Acid Rain, Pre ALPHA non-distribution version
//
// -By Insomnia (Steaphan Greene)   (Copyright 2002 Steaphan Greene)
//                   (stea@core.binghamton.edu)
//      No waranty stated or implied, I am not responsible for any damage
// caused directly or indirectly by this software.
//      Permision granted for use/distribution/modification by anyone,
// provided this header remains intact, and modified versions are marked
// as so immediately below this header.
//      Products utilizing the code or methods within may be distributed
// freely along with this licence, but any sales for profit of such products
// must have the author's permission, and may be subject to a royaltee fee.
// *************************************************************************

#ifndef SCENE_MATRIX_H
#define SCENE_MATRIX_H

//Node Flags
#define	NF_VISITED	1

//Construct Flags
#define	NF_ENCOUNTERED	1
#define	NF_DETECTED	2

//Node Types
#define NODE_UNKNOWN	0
#define NODE_PUBPORT	1
#define NODE_PRIVPORT	2
#define NODE_LTG0	10
#define NODE_LTG1	11
#define NODE_LTG2	12
#define NODE_LTG3	13
#define NODE_LTG4	14
#define NODE_LTG5	15
#define NODE_LTG6	16
#define NODE_LTG7	17
#define NODE_LTG8	18
#define NODE_LTG9	19

#define NODE_RANDOM	100
#define NODE_BANK	101
#define NODE_LIBRARY	102

#define ZONE_UNKNOWN	0
#define ZONE_OWNED	1
#define ZONE_PUBLIC	2
#define ZONE_WELCOME	3
#define ZONE_PRIVATE	4
#define ZONE_PROTECTED	5
#define ZONE_SECURE	6

#define MOVE_RECENTER	101
#define MOVE_TARGET	102
#define MOVE_PORT1	103
#define MOVE_PORT2	104
#define MOVE_DATA1	103
#define MOVE_DATA2	104
#define MOVE_TRAVEL	105
#define MOVE_TRAVEL2	106

#define MOVE_RUN_DIAL	200
#define MOVE_RUN_SCAN	201

#define FUNC_DIAL	0x00000001

#define LTG_DIGITS	36LL
const static int ltg_xp[LTG_DIGITS+1] = {
	1, 2, 3, 4, 5, 6, 7,
	1, 2, 3,    5, 6, 7,
	1, 2,          6, 7,
	1,                7,
	1, 2,          6, 7,
	1, 2, 3,    5, 6, 7,
	1, 2, 3, 4, 5, 6, 7,
	4 };
const static int ltg_yp[LTG_DIGITS+1] = {
	1, 1, 1, 1, 1, 1, 1,
	2, 2, 2,    2, 2, 2,
	3, 3,          3, 3,
	4,                4,
	5, 5,          5, 5,
	6, 6, 6,    6, 6, 6,
	7, 7, 7, 7, 7, 7, 7,
	4 };
const static int ltg_tp[LTG_DIGITS+1] = {
	0, 0, 0, 0, 0, 0, 0,
	0, 0, 0,    0, 0, 0,
	0, 0,          0, 0,
	0,                0,
	0, 0,          0, 0,
	0, 0, 0,    0, 0, 0,
	0, 0, 0, 0, 0, 0, 0,
	1 };
const static double moves[] = {
        1.0/100.0,
        3.0/99.0,
        6.0/96.0,
        15.0/90.0,
        25.0/75.0,
        25.0/50.0,
        15.0/25.0,
        6.0/10.0,
        3.0/4.0,
        1.0/1.0
        };

const static double spreads[] = {
        1.1,
        1.3,
        1.6,
        2.0,
        2.5,
        3.1,
        3.8,
        4.6,
        5.5,
        6.5
        };

typedef struct _matrix_path {  
  int xp, yp;
  struct _matrix_path *prev;
  } matrix_path;

#endif /* SCENE_MATRIX_H */
