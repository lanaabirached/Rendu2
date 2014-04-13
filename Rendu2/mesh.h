//
//  mesh.h
//  Bubbles
//

#ifndef Bubbles_mesh_h
#define Bubbles_mesh_h

#include <OpenGL/OpenGL.h>
#include <GLUT/GLUT.h>

typedef struct mesh mesh_t;

/**
 * Options to draw a mesh.
 * FILL: the inside mesh must be filled.
 * BORDER: the mesh border must be drawn.
 */
enum meshOptions {
	MESH_FILLED = 1,
	MESH_BORDERED,
};

/**
 * create a mesh representing a 2D circle.
 * \param res: number of edges.
 * \return a pointer to the mesh
 */
mesh_t* mesh_createCircle(unsigned short res);

/**
 * send the mesh to openGL to draw it.
 * \param mesh: the mesh to be drawn.
 * \param opt: option for the mesh.
 */
void mesh_draw(mesh_t* mesh, enum meshOptions opt);

#endif
