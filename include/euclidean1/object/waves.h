/**
 *  waves related structures and functions
 */
#ifndef _WAVES_H_INCLUDED
#define _WAVES_H_INCLUDED

#include <stdbool.h>
#include <math.h>

#ifndef M_PI
#define M_PI           3.14159265358979323846
#endif

typedef struct 
{
	float segments;


}wave_t;

float calculateSinf(float x);

void r_drawWaves(wave_t* w);




#endif