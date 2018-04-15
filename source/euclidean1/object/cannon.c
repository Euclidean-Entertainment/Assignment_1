/**
 *  Implementation of cannon.h
 */
#include "euclidean1/object/cannon.h"
#include "euclidean1/math/angle.h"
#include "euclidean1/object/projectile.h"

#include "gl_helper.h"

#include <math.h>

void c_drawCannon(cannon_t* c, float r, float g, float b)
{
    GLCall(glColor4f(r, g, b, 1.0f))

    GLCall(glPushMatrix())
    //GLCall(glScalef(0.1f, 0.1f, 1.0f))
    GLCall(glRotatef(c->z_rot, 0.0f, 0.0f, 1.0f))

    glBegin(GL_QUADS);
        glVertex3f(0.0f, 0.0f, -0.8f);
        glVertex3f(c->length, 0.0f, -0.8f);
        glVertex3f(c->length, -0.15f, -0.8f);
        glVertex3f(0.0f, -0.15f, -0.8f);
    glEnd();

    GLCall(glPopMatrix())
}

void c_rotateCannon(cannon_t* c, float angle)
{
    c->z_rot += angle;
}

void c_fireCannon(cannon_t* c, float x_force, float y_force, float angle, float scale, bool flip)
{
    projectile_t* p;
    float x;
    float y;
    float vx;
    float vy;

    // Take into account boat on the other side being flipped
    if(!flip)
        x = c->x + ((c->length * scale) * cosf(ANG_2_RAD(c->z_rot)));
    else
        x = c->x - ((c->length * scale) * cosf(ANG_2_RAD(angle)));

    y = c->y + ((c->length * scale) * sinf(ANG_2_RAD(c->z_rot))) + 0.1f;

    x -= x * (cosf(ANG_2_RAD(angle)) - y * sinf(ANG_2_RAD(angle))) * 0.1f;
    y -= x * (sinf(ANG_2_RAD(angle)) + y * cosf(ANG_2_RAD(angle))) * 0.1f;

    vx = x_force * cosf(ANG_2_RAD(c->z_rot));
    vy = y_force * sinf(ANG_2_RAD(c->z_rot));

    if(!flip)
    {
        vx += vx * cosf(ANG_2_RAD(angle)) - vy * sinf(ANG_2_RAD(angle));
        vy += vx * sinf(ANG_2_RAD(angle)) + vy * cosf(ANG_2_RAD(angle));         
    }
    else
    {
        vx += vx * cosf(ANG_2_RAD(-angle)) - vy * sinf(ANG_2_RAD(-angle));
        vy += vx * sinf(ANG_2_RAD(-angle)) + vy * cosf(ANG_2_RAD(-angle)); 
    }


    if(flip)    
        vx = -vx;

    p_init(p, x, y, vx, vy, 0.01f);
    //printf("angle: %f, x: %f, y: %f, vx: %f, vy: %f\n", angle, x, y, vx, vy);
    
}
