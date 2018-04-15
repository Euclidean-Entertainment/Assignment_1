/**
 *  Implementation of boat.h
 */
#include "euclidean1/object/boat.h"
#include "euclidean1/object/water.h"
#include "euclidean1/math/angle.h"

#include "gl_helper.h"

#include <math.h>

#define DRAG_FORCE 20.0f

static float prev_z_rot = 0.0f;

static void r_drawDeck(float r, float g, float b, float z_rot)
{
    GLCall(glColor4f(r, g, b, 1.0f))

    GLCall(glPushMatrix())
    GLCall(glScalef(0.1f, 0.35f, 1.0f))

    glBegin(GL_POLYGON);
        glVertex3f(0.0f - 0.2, 0.0f + 0.1, -0.8f);
        glVertex3f(0.0f + 0.2, 0.0f + 0.1, -0.8f);
        glVertex3f(0.0f + 0.2, 0.0f - 0.1, -0.8f);
        glVertex3f(0.0f - 0.2, 0.0f - 0.1, -0.8f);
    glEnd();

    GLCall(glPopMatrix())
}

static void r_drawHull(float r, float g, float b, float z_rot, float width, float height, bool flip)
{
    GLCall(glColor4f(r, g, b, 1.0f))

    if(flip)
    {
        GLCall(glScalef(-1.0f, 1.0f, 1.0f))
    }

    GLCall(glPushMatrix())
    GLCall(glScalef(0.35f, 0.35f, 1.0f))

    glBegin(GL_POLYGON);
        glVertex3f(0.0f - width - 0.1, 0.0f + height, -0.8f);
        glVertex3f(0.0f + width + 0.1, 0.0f + height, -0.8f);
        glVertex3f(0.0f + width, 0.0f - height, -0.8f);
        glVertex3f(0.0f - width, 0.0f - height, -0.8f);
    glEnd();

    GLCall(glPopMatrix())
}

void b_init(boat_t* boat, int id, float x, float y, float width, float height, float c_length, float c_zrot, float r, float g, float b, bool flip)
{
    if(boat == NULL)
    {
        printf("%s: boat == NULL!\n", __PRETTY_FUNCTION__);
        exit(-1);
    }

    boat->x                 = x;
    boat->y                 = y;
    boat->width             = width;
    boat->height            = height;
    boat->cannon.length     = c_length;
    boat->cannon.z_rot      = c_zrot;
    boat->id                = id;

    boat->r                 = r;
    boat->g                 = g;
    boat->b                 = b;

    boat->flip              = flip;

    boat->b_vol.x           = x;
    boat->b_vol.y           = y + 0.01f - (height / 2.0f);
    boat->b_vol.width       = width;
    boat->b_vol.height      = height + 0.02;
    boat->b_vol.scale       = 0.35;

    boat->health            = 10;
}

void b_drawBoat(boat_t* b)
{
    if(b == NULL)
        return;

    GLCall(glPushMatrix())
    GLCall(glTranslatef(b->x, b->y, 0.0f))

	GLCall(glRotatef(b->z_rot, 0.0f, 0.0f, 1.0f));

    // Draw base of the boat
    r_drawHull(b->r, b->g, b->b, b->z_rot, b->width, b->height, b->flip);

    // Draw the bridge
    GLCall(glTranslatef(0.0f, b->height - 0.05, 0.0f));
    r_drawDeck(b->r, b->g, b->b, b->z_rot);

    // HACK HACK HACK along, hack hack while I sing this song
    // There's obviously a way to do this without a sheer fuckload of
    // magic numbers, but it works so hey!
    b->cannon.x = b->x + b->width - 0.065f; 
    b->cannon.y = b->y + b->height - 0.05f - 0.015f;

    // Draw the cannon
    GLCall(glTranslatef(b->width - 0.065, -0.015f, 0.0f))
    GLCall(glScalef(0.1f, 0.1f, 0.0f))
	c_drawCannon(&b->cannon, b->r, b->g, b->b);
    GLCall(glPopMatrix())
}

void b_update(boat_t* b, float dt)
{   
    // If either boat tries to clip outside of the left or right side of the viewing frustum, 
    // apply a strong force in the opposite direction to kick them back in.

    // Left boat
    if(!b->flip)
    {
        if(b->b_vol.min < -1.0f)
        {
            b->curr_speed += 0.027f;
        }
    }
    else // Right boat
    {
        if(b->b_vol.min > 1.0f)
        {
            b->curr_speed -= 0.027f;
        }
    }

    b->x += b->curr_speed * dt * 1.5f;
    b->curr_speed *= (DRAG_FORCE * 0.048f);

    b->y            = w_calcSineAtX(b->x);
    b->z_rot        = ANG_2_DEGREES(w_getAngleAtX(b->x));

    b->cannon.x     = b->x + (b->width - 0.065f);;
    b->cannon.y     = b->y - 0.015f;

    b->b_vol.x      = b->x;
    b->b_vol.y      = b->y + 0.01f - (b->height / 2.0f);
    b->b_vol.min    = b->x - b->width;
    b->b_vol.max    = b->x + b->width; 

    if(b->wait_time > 0.0f)
        b->wait_time -= dt;

    if(b->wait_time < 0.0f)
        b->wait_time = 0.0f;
}

void b_fire(boat_t* b)
{  
    if(b->wait_time <= 0.0f)
    {
        b->wait_time = 1.0f;
        c_fireCannon(&b->cannon, 1.2f, 1.2f, b->z_rot, 0.1, b->flip);
    }
}
