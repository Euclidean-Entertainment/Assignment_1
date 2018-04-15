/**
 *  Boat data structures and functions
 */
#ifndef _BOAT_H_INCLUDED
#define _BOAT_H_INCLUDED

#include "euclidean1/object/cannon.h"
#include "euclidean1/system/aabb.h"

#include <stdbool.h>

#define BOAT_ACCEL 0.05f

typedef struct
{
    float       x;        /**< x position to start drawing from */
    float       y;        /**< y position to start drawing from */
    float       width;    /**< Width of the hull */
    float       height;   /**< Height of the hull */

    float       r;
    float       g;
    float       b;

    float       z_rot;      /**< This boat's rotation along the z-axis */
    bool        flip;

    float       curr_speed; /**< Current boat speed */
    float       wait_time;

    int         id;
    int         health;

    cannon_t    cannon;
    AABB        b_vol;      /**< This boat's bounding volume */
} boat_t;


/**
 *  Initialise a boat
 */
void b_init(boat_t* boat, int id, float x, float y, float width, float height, float c_length, float c_zrot, float r, float b, float g, bool flip);

/**
 *  Boat update function
 */
void b_update(boat_t* b, float dt);

/**
 *  Draw boat using a hierarchial method.
 */
void b_drawBoat(boat_t* b);

/**
 * Fire the boat's cannon!
 */
void b_fire(boat_t* b);

#endif
