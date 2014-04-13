/*
 * jeu.c
 * The game module give the possibility to parse a gamefile and to save a game
 * in a gamefile.
 *
 * created by Lana Abi Rached and Vianney Rousset
 *
 * version:			  2.1
 * last modification: 2014-03-16
 * responsable:		  R. Boulic
 */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <time.h>

#include "game.h"
#include "config.h"
#include "error.h"

// struct game stock each player pointer and the player turn.
struct game {
	player_t* players[MAX_PLAYER];
	unsigned char playerTurn;
};

game_t* game_parseGameFile(const char* filePath)
{
	// line: recieve the line to read, allocLength: won't be used but is needed
	// for the getline, playerIter: give the id of the read player,
	// game: the created game
	char* line = NULL;
	size_t allocLength;
	unsigned char playerIter = 0;
	game_t* game = malloc(sizeof(game_t));

	// game
	if (game == NULL)
	{
		error("Unable to allocate");
		return NULL;
	}
	
	// open file
    FILE* gameFile = fopen(filePath, "r");
	if (gameFile == NULL)
	{
		printf("ERROR: Unable to open file.\n");
		free(game);
		return NULL;
	}
	
	
	// read file
	while (getline(&line, &allocLength, gameFile) != -1) {
		if (line[0] != '#' && line[0] != '\n' && line[0] != '\r') {
			// read player infos
			game->players[playerIter] = player_createPlayer(playerIter);
			if (game->players[playerIter] == NULL)
			{
				printf("ERROR: Unable to create player %d.\n", playerIter+1);
				free(game);
				free(line);
				return NULL;
			}
			if (!player_parsePlayer(game->players[playerIter], game, gameFile,
									line))
			{
				printf("ERROR: Unable to parse player %d.\n", playerIter+1);
				free(game);
				free(line);
				return NULL;
			}
			playerIter++;
		}
	}

	error_success();
	
	game->playerTurn = 0;
	free(line);
	return game;
}

bool game_saveGameFile(game_t const * const game, char * filePath)
{
	// i: iterator variable, gameFile: the created file for the saving,
	// strLength: the size of the string filePath (for the extension),
	// tm: for the localTime, filePathF: the final filePath
	unsigned short i = 0;
	FILE* gameFile;
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);
	
	if (game == NULL)
	{
		error("Corrupted game.");
		return false;
	}
	
	gameFile = fopen(filePath, "w");
	if (gameFile == NULL)
	{
		error("Unable to create game file.")
		fclose(gameFile);
		remove(filePath);
		return false;
	}
	
	fprintf(gameFile, "# created at %d:%d:%d the %d-%d-%d.\n", tm.tm_hour,
			tm.tm_min, tm.tm_sec, tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday);
	
	for(i = 0; i < MAX_PLAYER; i++)
	{
		if (player_savePlayer(gameFile, game->players[i]) == false)
		{
			error("Unable to save game.\n");
			fclose(gameFile);
			remove(filePath);
		} else
			fprintf(gameFile, "\n");
	}
	if (gameFile != NULL)
		fclose(gameFile);
	return true;
}

/// getters ///

player_t* game_getPlayer(game_t const * const game,
						unsigned char const playerId)
{
	if (playerId >= MAX_PLAYER || playerId < 0)
		return NULL;
	else
		return game->players[playerId];
}

/// destructors ///

void game_destroyGame(game_t* game)
{
	unsigned char i=0;
	
	if (game != NULL)
		for (i = 0; i < MAX_PLAYER; i++)
			player_destroyPlayer(game->players[i]);
}

/// DEBUG ///

void game_printInfo(game_t const * const game)
{
	unsigned char i = 0;

	for (i = 0; i < MAX_PLAYER; i++) {
		player_printInfo(game->players[i]);
	}
}
