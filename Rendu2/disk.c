//
//  disk.c
//  Bubbles 2
//

#include <stdio.h>
#include <stdlib.h>

#include "disk.h"
#include "V2D.h"
#include "config.h"
#include "error.h"
#include "players.h"
#include "math.h"

struct disk {
	// disk id
	unsigned short id;

	// disk position
	v2d_t pos;
	
	// disk value
	unsigned short value;
};

disk_t** disk_createNDisk(unsigned short const n)
{
	unsigned short i=0, j=0;
	
	disk_t** disks = calloc(n, sizeof(disk_t*));
	if (disks == NULL)
	{
		printf("Allocation failed l. "str(__LINE__));
		return NULL;
	}
	
	for (i = 0; i < n; i++) {
		disks[i] = malloc(sizeof(disk_t));
		if (disks[i] == NULL)
		{
			printf("Allocation failed l. "str(__LINE__));
			for (j = 0; j < i; j++)
				free(disks[j]);
			free(disks);
			return NULL;
		}
		
		disks[i]->id = i;
	}

	return disks;
}

bool disk_parseDisk(disk_t* disk, game_t const * const game,
					unsigned char const PlayerId, char const * const line)
{	
	unsigned short i = 0, j = 0; 

	// read position and value
	if (sscanf(line, "%f %f %d", &disk->pos.x, &disk->pos.y,
			   &disk->value) != 3)
	{
		error_missing_disk(PlayerId+1);
		return false;
	}
	
	// check boundaries	
	if (disk->pos.x + disk->value * MIN_RADIUS > MAX_MODELE ||
		disk->pos.x - disk->value * MIN_RADIUS < 0		    ||
		disk->pos.y + disk->value * MIN_RADIUS > MAX_MODELE ||
		disk->pos.y - disk->value * MIN_RADIUS < 0)
	{
		error_disk_is_out_of_boundaries(PlayerId+1, disk->id);
		return false;
	}

	player_t* player = game_getPlayer(game, PlayerId);

	// check intersect with the player p disks
	for (i = 0; i < disk->id; i++)
	{
		disk_t* otherDisk = player_getDisk(player, i);
		
		float dx = otherDisk->pos.x - disk->pos.x;
		float dy = otherDisk->pos.y - disk->pos.y;
		float distance  = sqrtf(dx*dx + dy*dy);
		
		float sumRadius = (float) (disk->value + otherDisk->value) * MIN_RADIUS;
		
		if (sumRadius >= distance)
		{
			error_disks_are_in_contact(PlayerId+1, disk->id, PlayerId+1, i);
			return false;
		}
	}
	
	
	// check intersect with the other players disks
	for (i = 0; i < PlayerId; i++) {
		player_t* otherPlayer = game_getPlayer(game, i);
		for (j = 0; j < player_getNDisks(otherPlayer); j++)
		{
			disk_t* otherDisk = player_getDisk(otherPlayer, j);
			
			float dx = otherDisk->pos.x - disk->pos.x;
			float dy = otherDisk->pos.y - disk->pos.y;
			float distance  = sqrtf(dx*dx + dy*dy);
			
			float sumRadius = (float) (disk->value + otherDisk->value) * MIN_RADIUS;
			
			if (sumRadius >= distance)
			{
				error_disks_are_in_contact(PlayerId+1, disk->id, i+1, j);
				return false;
			}
		}
	}
	return true;
}

bool disk_saveDisk(FILE* gameFile, disk_t* disk)
{
	if (gameFile == NULL)
	{
		error("Corrupted gameFile.");
		return false;
	}
	
	if (disk == NULL)
	{
		error("Corrupted disk.");
		return false;
	}
	
	fprintf(gameFile, "%f %f %hd\n", disk->pos.x, disk->pos.y, disk->value);		// return value ? => check
	
	return true;
}

/// getters ///

v2d_t disk_getPos(disk_t const * const disk)
{
	return disk->pos;
}

unsigned short disk_getValue(disk_t const * const disk)
{
	return disk->value;
}

/// destructors ///
/**
 * free the disk pointer.
 *
 * \param disk the disk to destroy.
 */
void disk_destroyDisk(disk_t* disk)
{
	if (disk != NULL)
		free(disk);
}

/// DEBUG ///

void disk_printInfo(disk_t const * const disk)
{
	printf("\t disk %d: (%.2f, %.2f) %d\n", disk->id, disk->pos.x, disk->pos.y,
		   disk->value);
}
