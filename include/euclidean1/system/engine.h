/**
 *  Engine related structures and functions
 */
#ifndef _ENGINE_H_INCLUDED
#define _ENGINE_H_INCLUDED

#include <stdbool.h>

#include "euclidean1/system/window.h"

typedef struct
{
    void        (*e_update)();      /**< Engine idle update loop */
    void        (*e_input)();       /**< Engine input function pointer */


    window_t*   hwnd;               /**< Our window handle */
    bool        running;            /**< Is the game currently running??? */
    bool        debug;              /**< Is debug mode enabled? */
    bool        wireframe;          /**< Should we draw in wireframe mode? */

    // Timing related stuff
    float       time_elapsed;       /**< Elapsed time since our program started (in ms) */
    float       framerate;          /**< Current frame rate */
    float       dt;
    float       last_frametime;
    float       frame_interval;             
    long        frames;             /**< Frame count */
} engine_t;

/**
 *  Engine initilisation routine. Gets us out of main.
 *
 *  @param argv Arguments passed from the command line
 */
bool e_init(char** argv);

/**
 *  Engine shutdown function
 */
void e_shutdown(void);





#endif
