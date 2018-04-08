/**
 *  cannon related structures and functions
 */
#ifndef _CANNON_H_INCLUDED
#define _CANNON_H_INCLUDED

typedef enum
{
	base,
	tower_cannon

} tower_t;

void r_drawTower(tower_t* c);

void r_drawbase();



#endif