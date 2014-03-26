//
//  rendu2.h
//  Rendu2
//
//  Created by Lana macbook on 26/03/14.
//  Copyright (c) 2014 Lana macbook. All rights reserved.
//

#ifndef Rendu2_rendu2_h
#define Rendu2_rendu2_h

#include "V2D.h"
#include "disques.h"
#include "rendu1.h"



unsigned rendu2_rayon_propagate( float dx, float dy, float ux, float uy,
                                int nbDisque, float tabDisque[][3],
                                short tabHit[]);

int rendu1_get_nb_students(void);

void rendu1_get_sciper_ids(int student_sciper_ids[]);


#endif
