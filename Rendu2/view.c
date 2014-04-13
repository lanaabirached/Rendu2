/*
 * view.c
 * The view module use OpenGL to show the present status of a game.
 * It uses the VBO indexing to powering the render. Only one mesh is generated
 * during the module initialisation and used to draw all circles in the display
 * function.
 *
 * created by Lana Abi Rached and Vianney Rousset.
 *
 * version:			  2.1
 * last modification: 2014-04-11
 * responsable:		  R. Boulic
 */

#include <stdio.h>
#include <OpenGL/OpenGL.h>
#include <GLUT/GLUT.h>

#include "view.h"
#include "players.h"															///

#include "config.h"
#include "mesh.h"
#include "V2D.h"

// main_window: the windows where the game is drawn.
static int main_window;

// mainGame: this link the module to the present game state.					/// "state" ?
static game_t* mainGame = NULL;

// circle: this mesh is generated once with the mesh module and will be used to
//		   draw all circles.
static mesh_t* circle = NULL;

// display is the glut display function that draw the game in the main window.
static void display(void);

// reshape is the glut reshape function that correct the aspect ratio.
static void reshape(int w, int h);

// refresh will be used as the glut idle function to any for any animations.
static void refresh(void);

void view_Init(int* argc, char** argv)
{
	// init glut
	glutInit(argc, argv);

	// get screen size (width and height)
	int screenW = glutGet(GLUT_SCREEN_WIDTH),
		screenH = glutGet(GLUT_SCREEN_HEIGHT);
	
	// open main window
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowPosition((screenW - WINDOW_WIDTH) / 2,
						   (screenH - WINDOW_HEIGHT) / 2);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	main_window = glutCreateWindow(WINDOW_TITLE);

	// set glut functions
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutIdleFunc(NULL);
	
	// enable anti-aliasing (+set blending, +set anti-aliasing quality)
    glEnable(GL_MULTISAMPLE);
    glEnable(GL_BLEND);
    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_POLYGON_SMOOTH);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// create the circle mesh
	circle = mesh_createCircle(DISK_RESOLUTION);
}

void view_redraw(void)
{
	printf("INFO: redraw game.\n");
	refresh();
}

/// setters ///
void view_setGame(game_t* game)
{
	mainGame = game;
}

/// getters ///
game_t* view_getGame(void)
{
	return mainGame;
}

int view_getMainWindow()
{
	return main_window;
}

void refresh(void)
{
	glutPostRedisplay();
}

void display(void)
{	
	// iterator variables
	unsigned char  i = 0;
	unsigned short j = 0;

	// reset modelview and clear
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glClearColor(0.95, 0.95, 0.9, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// draw disks
	if (mainGame != NULL)
		for (i = 0; i < MAX_PLAYER; i++)
		{
			player_t* player = game_getPlayer(mainGame, i);
			const unsigned short ndisks = player_getNDisks(player);
			for (j = 0; j < ndisks; j++) {
				disk_t* disk = player_getDisk(player, j);
				v2d_t position = disk_getPos(disk);
				float radius   = disk_getValue(disk) * MIN_RADIUS * 0.9;
				// transform origin
				glLoadIdentity();
				glTranslatef(position.x, position.y, 0);
				glScaled(radius, radius, radius);
				
				// draw circle
				if (circle != NULL)
				{
					glColor3f(0.2*i, 0.5/(i+1), 0.2);
					mesh_draw(circle, MESH_FILLED);
					glColor3f(0.5*i, 0.8/(i+1), 0.5);
					mesh_draw(circle, MESH_BORDERED);
				} else
					error("The circle mesh isn't created.");
			}
		}
	
	// unbind buffers
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// swap buffers
	glutSwapBuffers();
}

void reshape(int w, int h)														////
{
	float xy_aspect;
	
	xy_aspect = (float)w / (float)h;
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (xy_aspect > 1)
		glViewport(0, 0, h, h);
	else
		glViewport(0, 0, w, w);
	glOrtho(0, MAX_MODELE, 0, MAX_MODELE, 0, 100);
	
	glutPostRedisplay();
}
