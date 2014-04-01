
// Assign the number of group members to the symbol "NB_GROUP_MEMBERS"
#define RENDU1_NB_GROUP_MEMBERS 2

// Assign the sciper ids of your group members to the array below
// i.e Replace the 11 and 12 by your sciper ids
static int rendu1_sciper_ids[RENDU1_NB_GROUP_MEMBERS] = {234712, 236091};


#include <stdio.h>
#include <stdlib.h>

#include "jeu.h"
#include "V2D.h"
#include "disques.h"
#include "rendu1.h"



unsigned rendu2_rayon_propagate(float dx, float dy, float ux, float uy,
                                int nbDisque, float tabDisque[][3],
                                short tabHit[])
{
    v2d_t pt_depart;
    v2d_t r_norm;
    v2d_t centre;
    struct disque bubble;
    float *cx, *cy, *v;
    short   i;
    
    
    
  // reorganiser en malloc ou garder comme ca ??
    *cx = tabDisque[0][0];
    *cy = tabDisque[0][1];
    *v  = tabDisque[0][2];
    

    {
        if (float rendu1_rayon_intersecte(dx, dy, ux, uy, cx, cy, r))
        {
            printf("Intersection !\n");
            return 1;
        }
        
        
        else
        {
            printf("No intersection !\n");
            return 0;
        }
    }
    
}


