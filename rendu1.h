/* 
 * Project: Jeu de Reflexion
 * Nom: rendu1.h
 * Description: This header file is required to grade your project. Check
 * 				Rendu document for the specifications.
 * 
 * 				TODO:
 * 					1) Open rendu1.c and set the values as explained to
 * 					   RENDU1_NB_GROUP_MEMBERS and rendu1_sciper_ids.
 * 					2) Implement the function "rendu1_rayon_intersecte" 
 * 					   in rendu1.c file.
 * 					3) You should check if your submission is ok
 * 					   with the script named "rendu_submission_check.sh"
 * 					   by using "your final .zip file" and the main file
 * 					   we deliver you whose name is "rendu1_check.cpp".
 * 
 *				NOT TODO!:
 * 					1) DO NOT TOUCH THE PROTOTYPE of 
 * 					   "rendu1_rayon_intersecte"!. 
 * 					2) DO NOT TOUCH THE OTHER FUNCTIONS AND DEFINITIONS 
 * 					   MADE IN rendu1.h and rendu1.c.
 * 
 * 				OPTIONAL:
 * 						You can add more functions to it as long
 * 						as your project passes the submission check test.
 * 
 */


#ifndef __RENDU1_H__
#define __RENDU1_H__

// DO NOT TOUCH THE PART BELOW!
float rendu1_rayon_intersecte (float dx, float dy, float ux, float uy, 
							   float cx, float cy, float r);
                               
int rendu1_get_nb_students(void);

void rendu1_get_sciper_ids(int student_sciper_ids[]);
#endif
