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

v2d_t v2d_createV2D()
{
	v2d_t v = {0, 0};
	return v;
}

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
