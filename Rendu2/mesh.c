//
//  mesh.c
//  Bubbles
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "mesh.h"
#include "V2D.h"
#include "config.h"

#define str(x)	# x
#define xstr(x)	str(x)

// definition of a mesh
struct mesh
{
	// all vertices needed to draw the mesh
	float* vertices;															// could be deleted once

	// VBO index for: 0. filling, 1. border
	unsigned int* index[2];														// could be deleted once

	// number of vertice to draw index 0 (filling) or index 1 (border)
	unsigned int nbrVertices[2];

	// GL buffers ids for: 0.vertices, 1. index 0 (filling), 2. index 1 (border)
	GLuint bufferId[3];
};

mesh_t* mesh_createCircle(unsigned short res)
{
	// mesh: the creating mesh, rotM: a rotation matrix to calculate vertices,
	// vert: the first vertice that will be rotated with rotM
	mesh_t* mesh = malloc(sizeof(mesh_t));
	m2d_t rotM;
	v2d_t vert = {1, 0};

	// check resolution and create matrix
	if (res < 3)
	{
		printf("WARNING: Circle resolution must be at least 3 f." xstr(__FILE__)
		" l." xstr(__LINE__) "\n");
		res = 3;
	}

	rotM = m2d_createRotationMatrix(2 * M_PI / res);

	// allocations of the vertices and the 2 indexes
	mesh->vertices = (float*) calloc(2 * (res+1), sizeof(float));
	if (mesh->vertices == NULL)
	{
		printf("Allocation failed f." xstr(__FILE__) " l." xstr(__LINE__) "\n");
		return NULL;
	}
	mesh->index[0] = (unsigned int*) calloc(3 * (res), sizeof(unsigned int));
	if (mesh->index[0] == NULL)
	{
		printf("Allocation failed f." xstr(__FILE__) " l." xstr(__LINE__) "\n");
		return NULL;
	}
	mesh->index[1] = (unsigned int*) calloc(res, sizeof(unsigned int));
	if (mesh->index[1] == NULL)
	{
		printf("Allocation failed f." xstr(__FILE__) " l." xstr(__LINE__) "\n");
		return NULL;
	}

	// calculating vertices and indexes
	for (unsigned short i = 0; i < res; i++)
	{
		// vertices
		vert = m2d_multiVector(rotM, vert);
		mesh->vertices[2 * i + 2] = vert.x;
		mesh->vertices[2 * i + 3] = vert.y;
				
		// VBO index for filling
		mesh->index[0][3 * i]	  = 0;
		mesh->index[0][3 * i + 1] = i + 1;
		mesh->index[0][3 * i + 2] = (i == res-1) ? 1 : i + 2;
		
		// VBO index for border
		mesh->index[1][i] = i+1;
	}

	mesh->nbrVertices[0] = res * 3;
	mesh->nbrVertices[1] = res;

	// generate GL buffers
	glGenBuffers(3, mesh->bufferId);

	// vertices buffer
	glBindBuffer(GL_ARRAY_BUFFER, mesh->bufferId[0]);
	glBufferData(GL_ARRAY_BUFFER, 3 * 2 * res * sizeof(float), mesh->vertices, // param 2 incertain
			GL_STATIC_DRAW);

	// filling buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->bufferId[1]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,
			3 * res * sizeof(int), mesh->index[0], GL_STATIC_DRAW);

	// border buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->bufferId[2]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,
				 res * sizeof(int), mesh->index[1], GL_STATIC_DRAW);

	return mesh;
}

void mesh_draw(mesh_t* mesh, enum meshOptions opt)
{
	glBindBuffer(GL_ARRAY_BUFFER, mesh->bufferId[0]);
	glVertexPointer(2, GL_FLOAT, 0, 0);
	glEnableClientState(GL_VERTEX_ARRAY);

	// filling
	if (opt & MESH_FILLED)
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->bufferId[1]);
		glDrawElements(GL_TRIANGLES, mesh->nbrVertices[0], GL_UNSIGNED_INT, 0);
	}
	
	// border
	if (opt & MESH_BORDERED)
	{		
		glLineWidth(DISK_BORDER_WEIGHT);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->bufferId[2]);
		glDrawElements(GL_LINE_LOOP, mesh->nbrVertices[1], GL_UNSIGNED_INT, 0);
	}
	glDisableClientState(GL_VERTEX_ARRAY);
}
