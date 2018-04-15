/**
 *  Implementation of engine.h
 */
#include "euclidean1/system/engine.h"
#include "euclidean1/system/window.h"

#include "platform.h"
#include "gl_helper.h"

#include "euclidean1/math/angle.h"
#include "euclidean1/system/text.h"
#include "euclidean1/object/water.h"
#include "euclidean1/object/boat.h"
#include "euclidean1/object/cannon.h"
#include "euclidean1/object/tower.h"
#include "euclidean1/system/aabb.h"
#include "euclidean1/object/projectile.h"

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <time.h>

#define MILLISECOND_TIME 1000.0f

static engine_t engine;

extern water_t          water;
extern active_list_t    p_list;


static bool drawNormals     = false;
static bool drawTangents    = false;

static boat_t 	p1;
static boat_t 	p2;
static tower_t	tower;

static bool gameover = false;

/**
 *  Our draw function
 */
static void draw(void)
{
    char buffer[256];
    char buffer2[256];
    
    GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT))
    GLCall(glEnable(GL_DEPTH_TEST))

    if(gameover)
        r_drawString(50, 100, "GAME OVER! Press ESC to exit!");

    if(engine.wireframe)
    {
        GLCall(glPolygonMode(GL_FRONT_AND_BACK, GL_LINE))
    }
    else
    {
        GLCall(glPolygonMode(GL_FRONT_AND_BACK, GL_FILL))
	}

    // Hmmm, it would seem glut is locking the framerate to the refresh rate.
    // Frametime is 200ms but fps is only 60? I smell something fishy...
    sprintf(buffer, "fps: %.2f(fps)\0", engine.framerate);
    sprintf(buffer2, "ft:  %.2f(ms)\0", engine.dt*MILLISECOND_TIME);


    if(engine.debug)
    {
        r_drawString(0, 0, "DEBUG MODE");
        r_drawString(0, 20, buffer);
        r_drawString(0, 30, buffer2);
        
        drawAABB(&(p1.b_vol));
        drawAABB(&(p2.b_vol));
    	drawAABB(&(tower.b_vol));
    
        for(int i = 0; i < MAX_PROJECTILES; i++)
        {
            if(p_list.projectiles[i] != NULL)
                drawAABB(&(p_list.projectiles[i]->b_vol));
        }
    }

    // Draw health for p1
    if(p1.health > 0)
    {
        GLCall(glColor3f(p1.r, p1.g, p1.b))
        glBegin(GL_QUADS);
            glVertex2f(-0.9, 0.9);
            glVertex2f(-0.9 + (p1.health * 0.06), 0.9);
            glVertex2f(-0.9 + (p1.health * 0.06), 0.85);
            glVertex2f(-0.9, 0.85);
        glEnd();
    }

    if(p2.health > 0)
    {
        // Draw health for p2
        GLCall(glColor3f(p2.r, p2.g, p2.b))
        glBegin(GL_QUADS);
            glVertex2f(-0.9, 0.8);
            glVertex2f(-0.9 + (p2.health * 0.06), 0.8);
            glVertex2f(-0.9 + (p2.health * 0.06), 0.75);
            glVertex2f(-0.9, 0.75);
        glEnd();
    }

    // Draw health for tower
    GLCall(glColor3f(1.0f, 1.0f, 0.0f))
    glBegin(GL_QUADS);
        glVertex2f(-0.9, 0.7);
        glVertex2f(-0.9 + (tower.health * 0.03), 0.7);
        glVertex2f(-0.9 + (tower.health * 0.03), 0.65);
        glVertex2f(-0.9, 0.65);
    glEnd();

    for(int i = 0; i < MAX_PROJECTILES; i++)
    {
        if(p_list.projectiles[i] != NULL)
            p_draw(p_list.projectiles[i]);
    }	

    b_drawBoat(&p1);
    b_drawBoat(&p2);
	t_draw(&tower, 1.0f, 1.0f, 0.0f);

    w_drawSine(drawNormals, drawTangents);
  


    glutSwapBuffers();
    engine.frames++;
}

static void e_update(void)
{
    static float prev_t = -1.0f;
    float t = 0.0f;
    float dt = 0.0f;

    t = glutGet(GLUT_ELAPSED_TIME) / MILLISECOND_TIME; // Number of ms since glutInit() was called

    // Skip the first frame to prevent / 0
    // Also keep the clock running even if the sim is paused to dt doesn't become huge
    if(prev_t < 0.0f || !engine.running)
    {
        prev_t = t;
        return;
    }          

    dt = t - prev_t;
    
    w_calculateSine(dt);

    //.y = w_calcSineAtX(p1.x); // Absolutely disgusting hack
    //.z_rot = ANG_2_DEGREES(w_getAngleAtX(p1.x));

    //.y = w_calcSineAtX(p2.x); // Absolutely disgusting hack
    //.z_rot = ANG_2_DEGREES(w_getAngleAtX(p2.x));

    b_update(&p1, dt);
    b_update(&p2, dt);
    t_update(&tower, dt);

    for(int i = 0; i < MAX_PROJECTILES; i++)
    {
        int ret;
        if(p_list.projectiles[i] != NULL)
        {
            ret = p_update(p_list.projectiles[i], dt);

            if(ret)
                p_list.projectiles[i] = NULL;
        }
    }

	// A collision has occured between the two boats
    if(testIntersection(&(p1.b_vol), &(p2.b_vol)))
    {
		// Classical mechanics ala Jurassic Park: Trespasser
		// Move the two offending boat away until they are no longer touching.
		
		p1.curr_speed -= 0.006f;
	}

	if(testIntersection(&(p1.b_vol), &(tower.b_vol)))
	{
		p1.curr_speed -= 0.027f;
	}

	if(testIntersection(&(p2.b_vol), &(tower.b_vol)))
	{
		p2.curr_speed += 0.027f;
	}

    for(int i = 0; i < MAX_PROJECTILES; i++)
    {
        int ret;
        if(p_list.projectiles[i] != NULL)
        {
            projectile_t* p = p_list.projectiles[i];

            if(testIntersection(&(p1.b_vol), &(p->b_vol)))
            {
                p_remove(p, i);
                p1.health--;
            }

            if(testIntersection(&(p2.b_vol), &(p->b_vol)))
            {
                p_remove(p, i);
                p2.health--;
            }

            if(testIntersection(&(tower.b_vol), &(p->b_vol)))
            {
                p_remove(p, i);
                tower.health--;
            }
        }
    }

    if(tower.health <= 0)
    {
        gameover = true;
        engine.running = false;
    }

    if(p1.health <= 0 && p2.health <= 0)
    {
        gameover = true;
        engine.running = true;
    }

    prev_t = t;
    
    dt = t - engine.last_frametime;

    if(dt > 0.2)
    {        
        engine.framerate = (engine.frames/dt);
        engine.dt = dt;
        engine.last_frametime = t;
        engine.frames = 0;
    }

    glutPostRedisplay();
}

static void r_reshape(int width, int height)
{
    r_setDimensions(width, height); // Update our logical screen to retain resize info!
    
    // Set the GL viewport to perform affine transformation to the current stuff on the screen (so it doesn't become all warped!)
    GLCall(glViewport(0, 0, width, height))

    // Reload our projection matrix
    GLCall(glMatrixMode(GL_PROJECTION))
    GLCall(glLoadIdentity())
    GLCall(glOrtho(-1.0f, 1.0f, -1.0f, 1.0f, -1.0f, 1.0f)) // Fill it with an orthographic matrix
    
    GLCall(glMatrixMode(GL_MODELVIEW))
    GLCall(glLoadIdentity())
}

void e_input(unsigned char c, int x, int y)
{
    switch(c)
    {
    case 27:
        exit(EXIT_SUCCESS);
        break;
	case '+':
		water.tesselations *= 2;
		if(water.tesselations > WATER_MAX_TESS)
			water.tesselations = WATER_MAX_TESS;
		break;
	case '-':
		water.tesselations /= 2;
		if(water.tesselations < WATER_MIN_TESS)
			water.tesselations = WATER_MIN_TESS;
		break;
    case 'w':
        engine.wireframe = !engine.wireframe;
        break;
    case '\'':
        engine.debug = !engine.debug;
        break;
    case 'g':
        if(!gameover)
            engine.running = !engine.running;
        break;
    case 'n':
        drawNormals = !drawNormals;
        break;
    case 't':
        drawTangents = !drawTangents;
        break;
    // Left player controls
    case 'a':
        if(p1.health > 0)
            p1.curr_speed -= BOAT_ACCEL;
        break;
    case 'd':
        if(p1.health > 0)
            p1.curr_speed += BOAT_ACCEL;
        break;
    case 'q':
        if(p1.cannon.z_rot < 90.0f && p1.health > 0)
            c_rotateCannon(&p1.cannon, 2.0f);
        break;
    case 'Q':
        if(p1.cannon.z_rot > 0.0f && p1.health > 0)
            c_rotateCannon(&p1.cannon, -2.0f);
        break;
    // Right player controls
    case 'k':
        if(p2.health > 0)
            p2.curr_speed -= BOAT_ACCEL;
        break;
    case 'l':
        if(p2.health > 0)
            p2.curr_speed += BOAT_ACCEL;
        break;
    case 'o':
        if(p2.cannon.z_rot < 90.0f && p2.health > 0)
            c_rotateCannon(&p2.cannon, 2.0f);
        break;
    case 'O':
        if(p2.cannon.z_rot > 0.0f && p2.health > 0)
            c_rotateCannon(&p2.cannon, -2.0f);
        break;
    case 'e':
        if(p1.health > 0)
            b_fire(&p1);
        break;
    case 'i':
        if(p2.health > 0)
            b_fire(&p2);
        break;

    case 'f':
        if(tower.cannon.z_rot < 180.0f)
            c_rotateCannon(&tower.cannon, 1.0f);
        break;
    case 'h':
        if(tower.cannon.z_rot > 0.0f)
            c_rotateCannon(&tower.cannon, -1.0f);
        break;
    case ' ':
        t_fire(&tower);
        break;
    default:
        break;
    }
}

bool e_init(char** argv)
{
    r_createWindow(640, 480, "Test");
    r_setDrawFunction(&draw);
    
    glutIdleFunc(e_update);
    glutKeyboardFunc(e_input);
    //glutReshapeFunc(r_reshape);    

    // Engine stuff
    engine.debug            = false;
    engine.wireframe        = false;
    engine.frames           = 0;
    engine.frame_interval   = 0.2;
    engine.last_frametime   = 0.0f;
    engine.time_elapsed     = 0.0f;
    engine.framerate        = 0.0f;    

	// Water init
	water.tesselations = 64;
	water.y_vals = (float*)calloc(WATER_MAX_TESS + 1, sizeof(float));
    water.x_vals = (float*)calloc(WATER_MAX_TESS + 1, sizeof(float));

    b_init(&p1, 0, -0.8f, 0.0f, 0.1f, 0.1f, 0.5f, 45.0f, 1.0f, 0.0f, 0.0f, false);
    b_init(&p2, 1, 0.8f, 0.0f, 0.1f, 0.1f, 0.5f, 45.0f, 0.0f, 0.0f, 1.0f, true);
	t_init(&tower, -0.25f, 0.3f, 0.5f, -1.3f);

    p_list.num = 0;
    for(int i = 0; i < MAX_PROJECTILES; i++)
    {
        p_list.projectiles[i] = NULL;
    }
    
    GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
	GLCall(glEnable(GL_BLEND))
	GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA))
    engine.running = true;
    
    
    glutMainLoop();
}
