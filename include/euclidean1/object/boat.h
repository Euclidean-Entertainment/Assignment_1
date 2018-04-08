/**
 *  waves related structures and functions
 */
#ifndef _BOAT_H_INCLUDED
#define _BOAT_H_INCLUDED

typedef enum
{
	hull,
	bridge,
	cannon,

} boat_t;


void r_drawBoat(boat_t* b);

void r_drawHull(float l, float h);

void r_drawbridge(float l, float h);


#endif