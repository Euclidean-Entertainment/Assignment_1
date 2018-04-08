/**
  *	Implementation of boat.h
  */

#include "platform.h"
#include "gl_helper.h"
#include "euclidean1/object/boat.h"
#include "euclidean1/math/vec2.h"

void r_drawBoat(boat_t* b)
{
	GLCall(glPushMatrix())

		//r_drawHull(0.2f,0.2f);
		//r_drawbridge(0.2f,0.2f);

	GLCall(glPopMatrix())
}

void r_drawHull(float l, float h)
{
	GLCall(glPushMatrix())
		GLCall(glScalef(l, h, 1.0f))
		GLCall(glBegin(GL_LINE_LOOP))
		GLCall(glVertex2f(-0.5f, -0.25f))
		GLCall(glVertex2f(0.5f, -0.25f))
		GLCall(glVertex2f(-1.0f, 0.25f))
		GLCall(glVertex2f(-1.0f, 0.25f))
		GLCall(glEnd())
	GLCall(glPopMatrix())
}

void r_drawbridge(float l, float h)
{
	GLCall(glPushMatrix())
		GLCall(glScalef(l, h, 1.0f))
		GLCall(glBegin(GL_LINE_LOOP))
		GLCall(glVertex2f(-0.25f, -0.25f))
		GLCall(glVertex2f(0.25f, -0.25f))
		GLCall(glVertex2f(0.25f, 0.25f))
		GLCall(glVertex2f(-0.25f, 0.25f))
		GLCall(glEnd())
	GLCall(glPopMatrix())
}
