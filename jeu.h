/*
 * jeu.h
 * The module jeu.h only parse a gamefile for the moment.
 * created by Lana Abi Rached and Vianney Rousset
 *
 * version:			  1.1
 * last modification: 2014-03-16
 * responsable:		  R. Boulic
 */

#ifndef JEU_H
#define JEU_H

#include <stdbool.h>
#include <stdio.h>

#include "V2D.h"

/**
 * load a game configuration from a game file.
 *
 * \param filePath the file to read.
 * \return true in case of success, false in case of failure
 */
bool jeu_parseGameFile(const char* filePath);

#endif
