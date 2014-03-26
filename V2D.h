/*
 * V2D.h
 * Bring the 2 dimensional mathematic object vector and some operations on it.
 * created by Lana Abi Rached and Vianney Rousset
 *
 * project:			  jeu de réflexion
 * version:			  1.0
 * last modification: 2014-03-16
 * responsable:		  R. Boulic
 */

#ifndef Rendu1_V2D_h
#define Rendu1_V2D_h

struct v2d {
  float x, y;
};

typedef struct v2d v2d_t;

// return a new null v2d
v2d_t v2d_createV2D();

// return -v
v2d_t v2d_opp(v2d_t v);

// return ||v|| (norm of v)
float v2d_norm(v2d_t v);

// return the normalization of v
v2d_t v2d_normalize(v2d_t v);

// return v1 + v2
v2d_t v2d_add(v2d_t v1, v2d_t v2);

// return v1 - v2
v2d_t v2d_sub(v2d_t v1, v2d_t v2);

// return k * v2 (multiplication of the v1 with a integer)
v2d_t v2d_multii(int k, v2d_t v);

// return k * v2 (multiplication of the v1 with a float point number)
v2d_t v2d_multif(float c, v2d_t v);

// return the dot product between v1 and v2
float v2d_dot(v2d_t v1, v2d_t v2);

// return ||v1 x v2|| (norm of the cross product between v1 and v2)
float v2d_crossNorm(v2d_t v1, v2d_t v2);

#endif
