/**
 *  Cannon functions and data structures
 */
#ifndef _CANNON_H_INCLUDED
#define _CANNON_H_INCLUDED

#include <stdbool.h>

typedef struct
{
    float x; // x position of cannon
    float y; // y position of cannon

    float length;
    float z_rot;
} cannon_t;

/**
 *  Draw this cannon to the screen
 */
void c_drawCannon(cannon_t* c, float r, float g, float b);

/**
 *  Rotate cannon c around the z-axis
 */
void c_rotateCannon(cannon_t* c, float angle);

/**
 *  Fire the cannon
 */
void c_fireCannon(cannon_t* c, float x_force, float y_force, float angle, float scale, bool flip);

#endif
