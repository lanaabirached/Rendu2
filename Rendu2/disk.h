//
//  disk.h
//  Bubbles 2
//

#ifndef Bubbles_2_disk_h
#define Bubbles_2_disk_h

typedef struct disk disk_t;

#include <stdbool.h>
#include "V2D.h"
#include "game.h"

/**
 * create n disks.
 *
 * \param the number of disks to create.
 * \return an array of n disks pointers.
 */
disk_t** disk_createNDisk(unsigned short const n);

/**
 * parse a disk line and set a disk.
 *
 * \param disk to set.
 * \param game the game that contains the player that contains the disk.
 * \param PlayerId the .
 * \param disk to set.
 * \return an array of n disks pointers.
 */
bool disk_parseDisk(disk_t* disk, game_t const * const game,
					unsigned char const PlayerId, char const * const line);

/**
 * save a disk into a game file.
 *
 * \param gameFile the file to save into.
 * \param disk disk to save.
 * \return true in case of success, false in case of failure.					/// still useful?
 */
bool disk_saveDisk(FILE* gameFile, disk_t* disk);

/// getters ///

v2d_t disk_getPos(disk_t const * const disk);

unsigned short disk_getValue(disk_t const * const disk);

/// destructors ///
/**
 * free the disk pointer.
 *
 * \param disk the disk to destroy.
 */
void disk_destroyDisk(disk_t* disk);

/// DEBUG ///

void disk_printInfo(disk_t const * const disk);

#endif
