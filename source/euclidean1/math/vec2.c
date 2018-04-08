/**
 *  Implementation of vec2.h
 */
#include "euclidean1/math/vec2.h"

#include "gl_helper.h"
#include "platform.h"

#include <math.h>
#include <stdio.h>

void v_normalize(vec2_t* vec)
{
    float mag;

    if(vec == NULL)
    {
        printf("%s: vec == NULL!\n", __PRETTY_FUNCTION__);
        return;
    }

    mag = sqrtf((vec->i * vec->i) + (vec->j * vec->j)); //duplicate code here - use v_getMagnitude?

    vec->i /= mag;
    vec->j /= mag;
}

void v_add(vec2_t* vec1, vec2_t* vec2)
{
    if(vec1 == NULL || vec2 == NULL)
        return;

    vec1->i += vec2->i;
    vec1->j += vec2->j;
}

void v_subtract(vec2_t* vec1, vec2_t* vec2)
{
    if(vec1 == NULL || vec2 == NULL)
        return;

    vec1->i -= vec2->i;
    vec1->j -= vec2->j;
}

float v_getMagnitude(vec2_t* vec)
{
    return sqrtf((vec->i * vec->i) + (vec->j * vec->j));
}

float v_getAngle(vec2_t* vec)
{
    return atanf(vec->j / vec->i);
}

void v_draw(vec2_t* vec, float r, float g, float b)
{
    GLCall(glBegin(GL_LINES));
        GLCall(glColor3f(r, g, b));
        GLCall(glVertex3f(vec->x, vec->y, 1.0f));
        GLCall(glVertex3f(vec->x + vec->i, vec->y + vec->j, 1.0f))
    GLCall(glEnd());
}
