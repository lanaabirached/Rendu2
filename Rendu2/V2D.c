/*
 * V2D.c
 * Bring the 2 dimensional mathematic object vector and some operations on it.
 * created by Lana Abi Rached and Vianney Rousset
 *
 * project:			  jeu de réflexion
 * version:			  1.0
 * last modification: 2014-03-16
 * responsable:		  R. Boulic
 */

#include <stdio.h>
#include <math.h>

#include "V2D.h"

v2d_t v2d_opp(v2d_t v)
{
	v2d_t v1 = {-v.x, -v.y};
	return v1;
}

float v2d_norm(v2d_t v)
{
	return sqrt(v.x*v.x + v.y*v.y);
}

v2d_t v2d_normalize(v2d_t v)
{
	float l = v2d_norm(v);
	v2d_t v1 = {v.x / l, v.y / l};
	return v1;
}

v2d_t v2d_add(v2d_t v1, v2d_t v2)
{
	v2d_t v = {v1.x + v2.x, v1.y + v2.y};
	return v;
}

v2d_t v2d_sub(v2d_t v1, v2d_t v2)
{
	v2d_t v = {v1.x - v2.x, v1.y - v2.y};
	return v;
}

v2d_t v2d_multii(int k, v2d_t v)
{
	v2d_t v1 = {k * v.x, k * v.y};
	return v1;
}

v2d_t v2d_multif(float c, v2d_t v)
{
	v2d_t v1 = {c * v.x, c * v.y};
	return v1;
}

float v2d_dot(v2d_t v1, v2d_t v2)
{
	return v1.x * v2.x + v1.y * v2.y;
}

float v2d_crossNorm(v2d_t v1, v2d_t v2)
{
	return v1.x * v2.y - v1.y * v2.x;
}

/*** Matrix 2x2 ***/

m2d_t m2d_createRotationMatrix(float angle)
{
	m2d_t m = {{cosf(angle), -sinf(angle)},{sinf(angle), cosf(angle)}};
	return m;
}

v2d_t m2d_multiVector(m2d_t m, v2d_t v)
{
	v2d_t v1;
	v1.x = m.v1.x * v.x + m.v2.x * v.y;
	v1.y = m.v1.y * v.x + m.v2.y * v.y;
	return v1;
}

m2d_t m2d_multiMatrix(m2d_t m1, m2d_t m2)
{
	m2d_t m;
	m.v1.x = m1.v1.x * m2.v1.x + m1.v2.x * m1.v1.y;
	m.v2.x = m1.v1.x * m2.v2.x + m1.v2.x * m1.v2.y;
	m.v1.y = m1.v1.y * m2.v1.x + m1.v2.y * m1.v1.y;
	m.v2.y = m1.v1.y * m2.v2.x + m1.v2.y * m1.v2.y;
	
	return m;
}
