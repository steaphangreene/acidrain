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

#define MOVE_RUN_DIAL00	200
#define MOVE_RUN_DIAL01	201
#define MOVE_RUN_DIAL02	202
#define MOVE_RUN_DIAL03	203
#define MOVE_RUN_DIAL04	204
#define MOVE_RUN_DIAL05	205
#define MOVE_RUN_DIAL06	206
#define MOVE_RUN_DIAL07	207
#define MOVE_RUN_DIAL08	208
#define MOVE_RUN_DIAL09	209
#define MOVE_RUN_DIAL10	210

#define MOVE_RUN_SCAN	220

const static int ltg_digits = 10;
const static int ltg_xp[] = {2, 3, 4, 5, 6, 2, 3, 4, 5, 6, 4};
const static int ltg_yp[] = {6, 6, 6, 6, 6, 2, 2, 2, 2, 2, 4};
const static int ltg_tp[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1};

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

#endif /* SCENE_MATRIX_H */
