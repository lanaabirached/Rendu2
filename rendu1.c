
// Assign the number of group members to the symbol "NB_GROUP_MEMBERS"
#define RENDU1_NB_GROUP_MEMBERS 2

// Assign the sciper ids of your group members to the array below
// i.e Replace the 11 and 12 by your sciper ids
static int rendu1_sciper_ids[RENDU1_NB_GROUP_MEMBERS] = {234712, 236091};

#include <math.h>

float rendu1_rayon_intersecte (float dx, float dy, float ux, float uy, 
							   float cx, float cy, float r)
{
	// dc : vector between D and C, i : intersection point I,
	// n  : normalized vector CI, w : 
    float dcx = 0, dcy = 0, ix = 0, iy = 0,nx = 0, ny = 0, wx = 0, wy = 0;
    float n_norme, s, v, d, du, un;
    
    dcx = cx-dx;
    dcy = cy-dy;
    
    // s = u ⦁ DC
    s = ux*dcx + uy*dcy;
    
    // v = || u ^ DC ||
    v = ux*dcy - uy*dcx;
    
    if (s > 0 && v <= r)
    {
        du = dx*ux + dy*uy; // du = d.u
        un = ux*nx + uy*ny; // un = u.n
        
        n_norme = sqrt(pow(ix-cx, 2) + pow(iy-cy, 2));
        
        nx = (float)((ix - cx)/n_norme);
        ny = (float)((iy - cy)/n_norme);
        
        d  = s - sqrt(r*r - v*v);
        
        ix = dx + du;
        iy = dy + du;
        
        wx = ux - 2*un*nx;
        wy = uy - 2*un*ny;
        		
        return d;
    }
	
    else
    {
        return -1;
    }
}

///// DO NOT TOUCH THE PART BELOW! /////
int rendu1_get_nb_students(void)
{
	return RENDU1_NB_GROUP_MEMBERS;
}

void rendu1_get_sciper_ids(int student_sciper_ids[])
{
	int i = 0;
	for(; i < RENDU1_NB_GROUP_MEMBERS; ++i)
		student_sciper_ids[i] = rendu1_sciper_ids[i];
}
///// DO NOT TOUCH THE PART ABOVE /////
