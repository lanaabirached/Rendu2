/*
 * view.h
 * The view module use OpenGL to show the present status of a game.
 * created by Lana Abi Rached and Vianney Rousset
 *
 * version:			  2.1
 * last modification: 2014-04-11
 * responsable:		  R. Boulic
 */

#ifndef Bubbles_view_h
#define Bubbles_view_h

#include "game.h"

/**
 * Initialize openGl and glut.
 *
 * \param argc for the glut initialization
 * \param argv for the glut initialization
 */
void view_Init(int* argc, char** argv);

/**
 * Redraw the main game.
*/
void view_redraw(void);

/// setters ///
/**
 * Set the game to draw.
 *
 * \param game the game to be drawn.
 */
void view_setGame(game_t* game);

/// getters ///
/**
 * get the current game.
 *
 * \return a pointer to the current game.
 */
game_t* view_getGame(void);

/**
 * get the main window id.
 *
 * \return the main window id.
 */
int view_getMainWindow(void);

#endif
