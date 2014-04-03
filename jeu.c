/*
 * jeu.c
 * The module jeu.c only parse a gamefile for the moment.
 * created by Lana Abi Rached and Vianney Rousset
 *
 * version:			  1.1
 * last modification: 2014-03-16
 * responsable:		  R. Boulic
 */

#include <math.h>
#include <stdlib.h>

#include "jeu.h"

#define MAX_PLAYER 2
#define MAX_VAL 10
#define MIN_RADIUS 1.414213562
#define MAX_PSEUDO 8
#define MAX_ENERGY 200
#define MAX_TOUR 20
#define MAX_TIME 10
#define MAX_MODELE 100

#define str(x)	# x
#define xstr(x)	str(x)

#define PDEBUG false

// parse player pseudo, score, energy and number of disks
// p: player id (begin with 0), d: disk id
bool readPlayerInfo(char* line, unsigned char p, char* pseudo, short* score,
					unsigned short* energy, unsigned short* nb_disques);

// parse disk position and value
// p: player id (begin with 0), d: disk id
bool readDisksInfo(char* line, unsigned char p, unsigned short d,
				   unsigned short* nDisk, v2d_t** position, unsigned short** value);

bool jeu_parseGameFile(const char* filePath)
{
	// line: recieve the line to read, allocLength: won't be used but is needed
	// for the getline, playerIter: give the id of the read player
	char* line = NULL;
	size_t allocLength;
	unsigned char playerIter = 0;

	// iterator variable
	unsigned short i=0;

	// those informations will be sent to a other function in a next rendu
	char pseudo[MAX_PLAYER][MAX_PSEUDO+1];
	short score[MAX_PLAYER];
	unsigned short energy[MAX_PLAYER], nb_disques[MAX_PLAYER];
	v2d_t* pos_C[MAX_PLAYER];
	unsigned short* val_disque[MAX_PLAYER];


	// open file
    FILE* gameFile = fopen(filePath, "r");
	if (gameFile == NULL)
	{
		if (PDEBUG)
			printf("ERROR: Unable to open game file.\n");
		return false;
	}

	// read file
	while (getline(&line, &allocLength, gameFile) != -1) {
		if (line[0] != '#' && line[0] != '\n' && line[0] != '\r') {
			// read player infos
			if (!readPlayerInfo(line, playerIter, (char*) &pseudo[playerIter],
								&score[playerIter], &energy[playerIter],
								&nb_disques[playerIter]))
				return false;

			if (PDEBUG)
				printf("[%s][%d][%d][%d]\n", pseudo[playerIter],
					   score[playerIter], energy[playerIter],
					   nb_disques[playerIter]);

			// allocations
			pos_C[playerIter] = (v2d_t*) calloc(nb_disques[playerIter],
											  sizeof(v2d_t));
			val_disque[playerIter] = (unsigned short*)
									 calloc(nb_disques[playerIter],
											sizeof(unsigned short));

			if (pos_C[playerIter] == NULL || val_disque[playerIter] == NULL) {
				if (PDEBUG)
					printf("ERROR: allocation failed l."xstr(__LINE__)"\n");
				return false;
			}

			// read disk infos
			for (i=0; i < nb_disques[playerIter]; i++) {
				if (getline(&line, &allocLength, gameFile) != -1) {
					if (!readDisksInfo(line, playerIter, i, nb_disques, pos_C, val_disque))
						return false;
				} else {
					error_missing_disk(playerIter+1);
					return false;
				}
				
				if (PDEBUG)
					printf("\t(%.2f;%.2f)[%d]\n", pos_C[playerIter][i].x,
						   pos_C[playerIter][i].y, val_disque[playerIter][i]);

			}
			
			if (getline(&line, &allocLength, gameFile) != -1 && line[0] != '\n'
				&& line[0] != '\r')
			{
				error_too_many_disks(playerIter+1);
				return false;
			}
			
			playerIter++;
		}
	}

	error_success();

	return true;
}

bool readPlayerInfo(char* line, unsigned char p, char* pseudo, short* score,
					unsigned short* energy, unsigned short* nb_disques)
{
	// cursor: position of the cursor after the pseudo
	int cursor = 0, tmp = 0;
	
	// read pseudo, score, energy and number of disks
	if (sscanf(line, "%"xstr(MAX_PSEUDO)"s%n %hd %d %hd", pseudo, &cursor,
			   score, &tmp, nb_disques) != 4) {

		// check pseudo length
		if (line[cursor] != ' ' && line[cursor] != '\n' && line[cursor] != '\r')
		{
			error_pseudo_is_too_long(p+1);
			return false;
		} else {
			if (PDEBUG)
				printf("ERROR: some player #%d informations missing.\n", p+1);
			return false;
		}
	}

	if (tmp < 0) {
		error_energy_is_negative(p+1);
		return false;
	}

	if (tmp > MAX_ENERGY) {
		error_energy_is_too_big(p+1);
		return false;
	}

	*energy = tmp;
	
	return true;
;}

bool readDisksInfo(char* line, unsigned char p, unsigned short d,
				   unsigned short* nDisk, v2d_t** position, unsigned short** value)
{
	// x, y represent the read disk position to simplifie the code
	float x, y;
	
	// iterator variables
	unsigned short i, j;

	// read position and value
	if (sscanf(line, "%f %f %hd", &x, &y, &value[p][d]) != 3)
	{
		error_missing_disk(p+1);
		return false;
	}
	position[p][d].x = x;
	position[p][d].y = y;
	
	// check boundaries	
	if (x + value[p][d] * MIN_RADIUS > MAX_MODELE ||
		x - value[p][d] * MIN_RADIUS < 0		  ||
		y + value[p][d] * MIN_RADIUS > MAX_MODELE ||
		y - value[p][d] * MIN_RADIUS < 0)
	{
		error_disk_is_out_of_boundaries(p+1, d);
		return false;
	}
	
	// check intersections
	for (i = 0; i < p; i++) {
		for (j = 0; j < nDisk[i]; j++) {
			float sumRadius = MIN_RADIUS * ((float) value[p][d]
											+ (float) value[i][j]);
			float dx = x - position[i][j].x;
			float dy = y - position[i][j].y;
			float distance = sqrtf(dx*dx + dy*dy);
			
			if (sumRadius >= distance)
			{
				error_disks_are_in_contact(i+1, j, p+1, d);
				return false;
			}
		}
	}
	
	for (i = 0; i < d; i++) {
		float sumRadius = MIN_RADIUS * ((float) value[p][d]
										+ (float) value[p][i]);
		float dx = x - position[p][i].x;
		float dy = y - position[p][i].y;
		float distance = sqrtf(dx*dx + dy*dy);
		
		if (sumRadius >= distance)
		{
			error_disks_are_in_contact(p+1, d, p+1, i);
			return false;
		}
	}
	
	return true;
}
