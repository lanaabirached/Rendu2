/*
 * main.cpp
 * The main file only initialize GLUI.
 *
 * created by Lana Abi Rached and Vianney Rousset.
 *
 * version:			  2.1
 * last modification: 2014-04-11
 * responsable:		  R. Boulic
 */

#include <iostream>

#include <OpenGL/OpenGL.h>
#include <GLUT/GLUT.h>
#include <GLUI/GLUI.h>

extern "C"
{
#include "view.h"
}

static void control(int inputId);
static void cleanUp(void);
static void initGlui(int argc, char** arg);
static char* assureTxt(char const * const filePath);

namespace {
    GLUI* mainGLUI;
	
    GLUI_EditText *LoadFileName,  *SaveFileName,
				  *NamePlayer1, *DiskNbrPlayer1, *ScorePlayer1, *EnergyPlayer1,
				  *NamePlayer2, *DiskNbrPlayer2, *ScorePlayer2, *EnergyPlayer2,
				  *PlayerTurn, *RemainingTime, *ScoreChange, *Winner;
    GLUI_Button *LoadGameButton, *QuitButton, *SaveGameButton;
}

enum {
	GLUI_LOAD_BUTTON,
	GLUI_SAVE_BUTTON
};

int main(int argc, char * argv[])
{
	game_t* mainGame = game_parseGameFile(argv[1]);
	if (mainGame == NULL)
		printf("ERROR: Unable to load gamefile %s.\n", argv[1]);
	view_setGame(mainGame);

    view_Init(&argc, argv);
	initGlui(argc, argv);
	
	atexit(cleanUp);
	
	glutMainLoop();
			    
    return EXIT_SUCCESS;
}

void initGlui(int argc, char * argv[])
{
    mainGLUI = GLUI_Master.create_glui("Control");
    
	mainGLUI->set_main_gfx_window(view_getMainWindow());
	
	// load game panel
    GLUI_Panel *load = mainGLUI->add_panel("Load game", GLUI_PANEL_EMBOSSED);
    LoadFileName = mainGLUI->add_edittext_to_panel(load,
											   "File path");
    if (argc == 2)
        LoadFileName->set_text(argv[1]);
    LoadGameButton = mainGLUI->add_button_to_panel(load,
											   "Load Game",
											   GLUI_LOAD_BUTTON,
											   control);
    
	
	
	// save game panel
    GLUI_Panel *save = mainGLUI->add_panel("Save", GLUI_PANEL_EMBOSSED);
    SaveFileName = mainGLUI->add_edittext_to_panel(save,
											   "File path",
											   GLUI_EDITTEXT_TEXT);
	SaveGameButton = mainGLUI->add_button_to_panel(save,
											   "Save Game",
											   GLUI_SAVE_BUTTON,
											   control);
    
	// info panel
    GLUI_Panel *info = mainGLUI->add_panel( "Information" , GLUI_PANEL_EMBOSSED);
    
	
	// player 1 panel
    GLUI_Panel *player1 = mainGLUI->add_panel_to_panel(info, "Player 1",
												   GLUI_PANEL_EMBOSSED);
    NamePlayer1 = mainGLUI->add_edittext_to_panel(player1, "Name",
											  GLUI_EDITTEXT_TEXT);
    DiskNbrPlayer1 = mainGLUI->add_edittext_to_panel(player1, "Nb Disks",
												 GLUI_EDITTEXT_TEXT);
    EnergyPlayer1 = mainGLUI->add_edittext_to_panel(player1, "Energy",
												GLUI_EDITTEXT_TEXT);
    ScorePlayer1 = mainGLUI->add_edittext_to_panel(player1, "Score",
											   GLUI_EDITTEXT_TEXT);


	// player 2 panel
    GLUI_Panel *player2 = mainGLUI->add_panel_to_panel(info, "Player 2",
												   GLUI_PANEL_EMBOSSED);
    NamePlayer2 = mainGLUI->add_edittext_to_panel(player2, "Name",
											  GLUI_EDITTEXT_TEXT);
    DiskNbrPlayer2 = mainGLUI->add_edittext_to_panel(player2, "Nb Disks",
												 GLUI_EDITTEXT_TEXT);
    EnergyPlayer2 = mainGLUI->add_edittext_to_panel(player2, "Energy",
												GLUI_EDITTEXT_TEXT);
    ScorePlayer2 = mainGLUI->add_edittext_to_panel(player2, "Score",
											   GLUI_EDITTEXT_TEXT);
    
    // current panel
    GLUI_Panel *current = mainGLUI->add_panel("Current Turn",
										  GLUI_PANEL_EMBOSSED);
    PlayerTurn = mainGLUI->add_edittext_to_panel(current, "Player Turn",
											 GLUI_EDITTEXT_TEXT);
    RemainingTime = mainGLUI->add_edittext_to_panel(current, "Remaining Time",
												GLUI_EDITTEXT_TEXT);
    ScoreChange = mainGLUI->add_edittext_to_panel(current, "Score Change",
											  GLUI_EDITTEXT_TEXT);
    Winner = mainGLUI->add_edittext ("Winner", GLUI_EDITTEXT_TEXT);
    QuitButton = mainGLUI->add_button ("Quit", 0, (GLUI_Update_CB)exit );
}

void control(int inputId)
{   
	game_t* game;
	char* filePath;
    switch (inputId)
    {
		case GLUI_LOAD_BUTTON:
			filePath = assureTxt(LoadFileName->get_text());
			printf("Load: %s\n", filePath);
			game = game_parseGameFile(filePath);
			view_setGame(game);
			view_redraw();
			free(filePath);
			break;
			
		case GLUI_SAVE_BUTTON:
					filePath = assureTxt(LoadFileName->get_text());
			SaveFileName->get_text();
			printf("Save: %s\n", assureTxt(SaveFileName->get_text()));
			game_saveGameFile(view_getGame(), assureTxt(SaveFileName->get_text()));
			break;
        default:
            printf("Unknown command\n");
            break;
    }
}

void cleanUp(void)
{
	game_t* game = view_getGame();
	if (game != NULL)
		game_destroyGame(game);
}

char* assureTxt(char const * const filePath)
{
	// strLength: string lengtth of filePath, filePathTxt: file path with .txt
	// assured
	unsigned short strLength = strlen(filePath);
	char* filePathTxt = (char*) malloc((strLength + 5) * sizeof(char));
	filePathTxt = strcpy(filePathTxt, filePath);

	// check extension
	if (filePath[strLength-1] != 't' || filePath[strLength-2] != 'x' ||
		filePath[strLength-3] != 't' || filePath[strLength-4] != '.' )
	{
		// set extension as ".txt"
		filePathTxt[strLength]   = '.';
		filePathTxt[strLength+1] = 't';
		filePathTxt[strLength+2] = 'x';
		filePathTxt[strLength+3] = 't';
		filePathTxt[strLength+4] = '\0';
	}
	
	return filePathTxt;
}
