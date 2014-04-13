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

#ifndef Bubbles_player_h
#define Bubbles_player_h

#include <stdbool.h>

typedef struct player player_t;

#include "disk.h"
#include "game.h"

/**
 * create a player.
 *
 * \param the id of the player.
 * \return the player pointer.
 */
player_t* player_createPlayer(unsigned char const id);

/**
 * parse a gamefile to set a player info (+ disks infos).
 *
 * \param player the player to set.
 * \param game the game where the player is.
 * \param gamefile the file to parse into.
 * \param line the line that contains the player infos.
 * \return false in case of failure, true in case of success
 */
bool player_parsePlayer(player_t* player,
						game_t const * const game,
						FILE* gameFile,
						char* line);

/**
 * save a player into a game file.
 *
 * \param gameFile the file to save into.
 * \param player player to save.
 * \return true in case of success, false in case of failure.					/// still useful?
 */
bool player_savePlayer(FILE* gameFile, player_t* player);

/// getters ///

/**
 * get a disk pointer owned by the player
 *
 * \param player the player that owns the disk.
 * \param diskId the player id.
 * \return a pointer to the player
 */
disk_t* player_getDisk(player_t const * const player,
					   unsigned short const diskId);

/**
 * get the number of disk of a player
 *
 * \param player the player that owns the disk.
 * \return the numbe of disks.
 */
unsigned short player_getNDisks(player_t const * const player);

/// destructor ///
/**
 * free all pointers contained in a player with his "childs" (disks).
 *
 * \param player the player to destroy.
 */
void player_destroyPlayer(player_t* player);

/// DEBUG ///

/**
 * print the players infos and his disks
 *
 * \param player the player to "print".
 */
void player_printInfo(player_t const * const player);

#endif
