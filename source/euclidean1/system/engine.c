/**
 *  Implementation of engine.h
 */
#include "euclidean1/system/engine.h"
#include "euclidean1/system/window.h"
#include "euclidean1/object/waves.h"
#include "euclidean1/object/boat.h"
#include "euclidean1/object/tower.h"

#include "platform.h"
#include "gl_helper.h"

#include <stdio.h>

static engine_t engine;
static wave_t waves;
static boat_t boat;
static tower_t tower;

static void draw(void)
{
    GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
    GLCall(glClearColor(0.0f, 0.0f, 1.0f, 1.0f));

    //GLCall(glPopMatrix()); // Good example of the GLCall() macro!
    r_drawWaves(&waves);

    r_drawBoat(&boat);

    r_drawTower(&tower);

    glutSwapBuffers();
}

bool e_init(char** argv)
{
    engine.hwnd = r_createWindow(640, 480, "Test");
    r_setDrawFunction(engine.hwnd, &draw);

    engine.running = true;

    while(engine.running)
    {
        glutMainLoopEvent();
    }

    e_shutdown();
}

void e_shutdown(void)
{
    printf("r_shutdown...\n");
    
    r_freeWindow(engine.hwnd);
}