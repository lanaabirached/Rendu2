/*
 * game.h
 * The game module gives the possibility to load and save a game.
 *
 * created by Lana Abi Rached and Vianney Rousset
 *
 * version:			  2.1
 * last modification: 2014-04-11
 * responsable:		  R. Boulic
 */

#ifndef Bubbles_2_game_h
#define Bubbles_2_game_h

typedef struct game game_t;

#include "players.h"

/**
 * load a game from a game file.
 *
 * \param filePath the file to read.
 * \return a pointer to the game.
 */
game_t* game_parseGameFile(char const * const filePath);

/**
 * save a game to a game file.
 *
 * \param game a pointer to the game to save.
 * \param filePath path to the gamefile.
 * \return true in case of success, false in case of failure.					/// still useful?
 */
bool game_saveGameFile(game_t const * const game, char * filePath);

/// getters ///

/**
 * get a player pointer.
 *
 * \param the game to look into.
 * \param playerId the id of the disired player.
 * \return the disired player. return NULL in case of non-existence.			// disired
 */
player_t* game_getPlayer(game_t const * const game,
						unsigned char const playerId);

/// destructor ///
/**
 * free all pointers contained in a game with his "childs" (player and disks).
 *
 * \param game the game to destroy.
 */
void game_destroyGame(game_t* game);

/// DEBUG ///
/**
 * print the players and disks informations of the game.
 *
 * \param game the game to "print".
 */
void game_printInfo(game_t const * const game);

#endif
