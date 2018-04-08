/**
  *	Implementation of cannon.h
  */

#include "platform.h"
#include "gl_helper.h"
#include "euclidean1/object/tower.h"
#include "euclidean1/math/vec2.h"

void r_drawTower(tower_t* c)
{
	r_drawbase();

}

void r_drawbase()
{
	GLCall(glBegin(GL_QUADS))

	GLCall(glColor3f(1.0f, 1.0f, 0.0f))

    GLCall(glVertex3f(-0.2f, -1.0f, -0.9f))
    GLCall(glVertex3f(0.2f, -1.0f, -0.9f))
    GLCall(glVertex3f(0.2f, 0.2f, -0.9f))
    GLCall(glVertex3f(-0.2f, 0.2f, -0.9f))

	GLCall(glEnd())
}
