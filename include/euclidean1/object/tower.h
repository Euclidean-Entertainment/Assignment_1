/**
 *	Tower structures and functions	
 */
#ifndef _TOWER_H_INCLUDED
#define _TOWER_H_INCLUDED

#include "euclidean1/object/cannon.h"
#include "euclidean1/system/aabb.h"

typedef struct
{
	float 		x;
	float 		y;
	float 		width;
	float 		height;

	cannon_t 	cannon;
	AABB		b_vol;

    float       wait_time;
	int 		health;
} tower_t;

void t_init(tower_t* t, float x, float y, float width, float height);

/**
 *	Draw this tower to the screen
 */
void t_draw(tower_t* t, float r, float g, float b);

/**
 *	Update this tower
 */
void t_update(tower_t* t, float dt);

/**
 *  Fire the tower's cannon
 */
void t_fire(tower_t* t);

#endif
