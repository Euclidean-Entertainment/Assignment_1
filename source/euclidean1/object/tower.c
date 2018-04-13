/**
 *	Implementation of tower.h
 */
#include "euclidean1/object/tower.h"

#include "gl_helper.h"

#define TOWER_WIDTH 1.0f

void t_init(tower_t* t, float x, float y, float width, float height)
{
	t->x 		= x;
	t->y 		= y;
	t->width 	= width;
	t->height 	= height;

	t->b_vol.x	 = x;
	t->b_vol.y	 = y + height;

	t->b_vol.width  = width;
	t->b_vol.height = -height;

	t->b_vol.min = x;
	t->b_vol.max = x + width;	

	t->cannon.x = x + (x/2);
	t->cannon.y = y + 0.0f;
	t->cannon.length = 0.5f;
	

	printAABB(&t->b_vol);
	//t->b_vol.width = width;
	//t->b_vol.height = height;
}

void t_draw(tower_t* t, float r, float g, float b)
{
	GLCall(glPushMatrix())
	GLCall(glTranslatef(0.0f, 0.0f, 0.0f))
	GLCall(glColor3f(r, g, b))

	glBegin(GL_QUADS);
		glVertex3f(-0.25f, 0.3f, -0.7f);
		glVertex3f(-0.25f + t->width, 0.3f, -0.7f);
		glVertex3f(-0.25f + t->width, -1.0f, -0.7f);
		glVertex3f(-0.25f, -1.0f, -0.7f);
	glEnd();

	GLCall(glTranslatef(0.0f, 0.5f, 0.0f))
	//GLCall(glScalef(3.0f, 3.0f, 0.0f));
	c_drawCannon(&(t->cannon), 1.0f, 1.0f, 0.0f);

	GLCall(glPopMatrix())
}
