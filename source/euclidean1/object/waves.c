/**
  *	Implementation of waves.h
  */

#include "platform.h"
#include "gl_helper.h"
#include "euclidean1/object/waves.h"
#include "euclidean1/math/vec2.h"

#include <stdio.h>
#include <math.h>

//this should prpbably go into vec2.c b/c we need to calc the y-pos of the boat
float calculateSinf(float x)
{
	float y,A,L,k,w;
	A = 0.2f;
	L = 1.0f;
	k = (2.0f * M_PI) / L;
    w = M_PI/4.0f;

    //y = A * sinf(k * x + (w * g.t)); //This is the sinwave with time
	y = A * sinf(k * x);

	return y;
}

void r_drawWaves(wave_t* w)
{
	vec2_t wave;
	float right = 1.0f;
	float left = -1.0f;
    float range = right - left;

    w->segments = 8.0f; //we will need to change this for adjustment

    float stepSize = range/w->segments;

    //glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glPolygonMode(GL_BACK, GL_LINE);


	GLCall(glBegin(GL_QUAD_STRIP))

	GLCall(glColor3f(0.0f, 0.47f, 0.75f))
	//write a for loop to iterate from 0 to the numer of segments (inclusive)
    for(float i = 0.0f; i <= w->segments; i += stepSize)
    {
		wave.x = i * stepSize + left;
		wave.y = calculateSinf(wave.x);

        GLCall(glVertex3f(wave.x, wave.y - glutGet(GLUT_WINDOW_HEIGHT), -0.8f))
        GLCall(glVertex3f(wave.x, wave.y, -0.8f))
    }
	GLCall(glEnd())


 	/*for(float i = 0.0f; i <= w->segments; i += stepSize)
    {
        wave.x = i * stepSize + left;
        wave.y = calculateSinf(wave.x);

        //wave.i = wave.x;
        //wave.j = 1.0f;


        //v_normalize(&wave);
        //v_draw(&wave, 0.0f, 1.0f, 0.0f);

       

    }*/


}