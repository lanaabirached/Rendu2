/*
 * main.c
 * Main file of the project.
 * created by Lana Abi Rached and Vianney Rousset
 *
 * version:			  1.1
 * last modification: 2014-03-16
 * responsable:		  R. Boulic
 */

#include <string.h>
#include <stdlib.h>
#include <GLUI/GLUI.h>

#include "disques.h"

extern "C" {
#include "jeu.h"
}

int main(int argc, const char * argv[])
{
    disque a;
    
	if (argc > 1)
		if (!jeu_parseGameFile(argv[1]))
			return EXIT_FAILURE;
	return EXIT_SUCCESS;
}