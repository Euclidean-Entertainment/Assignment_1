/**
 *  Implementation of window.h
 */
#include "euclidean1/system/window.h"

#include "platform.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


window_t* r_createWindow(int width, int height, const char* title)
{
    window_t* hwnd; // Window handle

    hwnd = malloc(sizeof(window_t));

    if(!hwnd)
    {
        printf("%s: hwnd == NULL!\n", __PRETTY_FUNCTION__);
        return NULL;
    }

    hwnd->title = malloc(strlen(title));
    
    hwnd->height = height;
    hwnd->width = width;
    strcpy(hwnd->title, title);

    // Now get GLUT to initialse the physical window
    glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);

    glutInitWindowSize(width, height);
    glutCreateWindow(title);

    return hwnd;
}

bool r_freeWindow(window_t* hwnd)
{
    if(hwnd != NULL)
    {
        free(hwnd);
        hwnd = NULL;
        return false;    
    }

    // We can't free a NULL pointer!
    printf("%s: Cannot Free Window (hwnd == NULL)!\n", __PRETTY_FUNCTION__);
    return false;
}

void r_setDrawFunction(window_t* hwnd, void (*drawCB)(void))
{
    if(hwnd == NULL)
    {
        printf("%s: hwnd == NULL!\n", __PRETTY_FUNCTION__);
        return;       
    }

    if(drawCB == NULL)
    {
        printf("%s: Cannot set hwnd->r_draw() to NULL!\n", __PRETTY_FUNCTION__);
        return;
    }

    hwnd->r_draw = drawCB;
    glutDisplayFunc(hwnd->r_draw);
}


