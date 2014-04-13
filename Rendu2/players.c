/*
 * players.h
 *
 * The players module gives the possibility to create players and parse a
 * gamefile.
 *
 * created by Lana Abi Rached and Vianney Rousset
 *
 * version:			  2.1
 * last modification: 2014-03-16
 * responsable:		  R. Boulic
 */

#ifndef JEU_H
#define JEU_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "config.h"
#include "error.h"
#include "V2D.h"
#include "players.h"

struct player {
	disk_t** disks;
  	char pseudo[MAX_PSEUDO+1];
	int score;
	unsigned short nDisks, energy;
	unsigned char id;
};

player_t* player_createPlayer(unsigned char const id)
{
	player_t* player = malloc(sizeof(player_t));
	if (player == NULL)
	{
		printf("ERROR: Unable to alocate l. f.");
		return NULL;
	}

	player->id		 = id;
	
	return player;
}

bool player_parsePlayer(player_t* player,
						game_t const * const game,
						FILE* gameFile,
						char* line)
{
	/** read player info **/

	// cursor: position of the cursor after the pseudo
	unsigned short cursor = 0;
	int tmp = 0;
	unsigned short i = 0;
	size_t allocLength;

	// read pseudo, score, energy and number of disks
	sscanf(line, "%"xstr(MAX_PSEUDO)"s%n %d %d %d", player->pseudo, &cursor,
			   &player->score, &tmp, &player->nDisks);

	if (tmp < 0) {
		error_energy_is_negative(player->id+1);
			return false;
	}

	if (tmp > MAX_ENERGY) {
		error_energy_is_too_big(player->id+1);
			return false;
	}

	player->energy = tmp;
	player->pseudo[cursor] = '\0';
	
	// create player disks
	player->disks = disk_createNDisk(player->nDisks);
	if (player->disks == NULL)
	{
		printf("ERROR: Unable to create disks.\n");
		return false;
	}
	
	/** read disks info **/
	
	for (i = 0; i < player->nDisks; i++) {
		if (getline(&line, &allocLength, gameFile) != -1) {
			if (!disk_parseDisk(player->disks[i], game, player->id, line))
			{
				printf("ERROR: Unable to parse disk %d.\n", i);
				return false;
			}
		} else {
			error_missing_disk(player->id+1);
			return false;
		}
	}
	
	if (getline(&line, &allocLength, gameFile) != -1 && line[0] != '\n'
		&& line[0] != '\r')
	{
		error_too_many_disks(player->id+1);
		return false;
	}
	
	return true;
}

bool player_savePlayer(FILE* gameFile, player_t* player)
{
	unsigned short i = 0;

	if (gameFile == NULL)
	{
		error("Corrupted gameFile.");
		return false;
	}
	
	if (player == NULL)
	{
		error("Corrupted player.");
		return false;
	}
	
	fprintf(gameFile, "%s %d %hd %hd\n", player->pseudo, player->score,
			player->energy, player->nDisks);									// return value ? => check
	
	for(i = 0; i < player->nDisks; i++)
	{
		if (disk_saveDisk(gameFile, player->disks[i]) == false)
		{
			error("Unable to save disk.");
			return false;
		}
	}
	
	return true;
}

/// getters ///

disk_t* player_getDisk(player_t const * const player,
					   unsigned short const diskId)
{
	if (diskId >= player->nDisks || diskId < 0)
		return NULL;
	else
		return player->disks[diskId];
}

unsigned short player_getNDisks(player_t const * const player)
{
	return player->nDisks;
}

/// destructor ///
void player_destroyPlayer(player_t* player)
{
	if (player != NULL)
	{
		unsigned short i = 0, ndisks = player->nDisks;
		for (i = 0; i < ndisks; i++)
			disk_destroyDisk(player->disks[i]);
	}
	
	free(player->disks);
	free(player);
}

/// DEBUG ///

void player_printInfo(player_t const * const player)
{
	unsigned short i = 0;

	printf("DEBUG: player %d %s (score: %d, energy: %d, nDisks: %d)\n",
		   player->id, player->pseudo, player->score,
		   player->energy, player->nDisks);

	for (i = 0; i < player->nDisks; i++)
		disk_printInfo(player->disks[i]);
}

#endif
