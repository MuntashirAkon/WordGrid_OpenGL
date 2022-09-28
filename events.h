/**
 * UI Events.
 * 
 * Author: Muntashir Al-Islam <muntashirakon@riseup.net>
 */

#ifndef _H_EVENTS
#define _H_EVENTS

enum WINDOW_EVENT
{
	START,
	WELCOME_WINDOW,
	HELP_WINDOW,
	LEVEL_SELECTION_WINDOW,
	PLAYER_1_SELECTION_WINDOW,
	PLAYER_2_SELECTION_WINDOW,
	IN_GAME_WINDOW,
	RESULT_WINDOW
};

#define LEVEL_COUNT 3
#define MAX_BOX_COUNT 10

enum GAME_LEVEL {
	LEVEL_1,
	LEVEL_2,
	LEVEL_3
};

#endif _H_EVENTS