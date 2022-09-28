/**
 * Word Grid Game.
 *
 * Author: Muntashir Al-Islam <muntashirakon@riseup.net>
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#endif

#include "timer.h"
#include "glhelpers.h"
#include "events.h"
#include "resources.h"

#define APP_NAME "Word Grid"

#define ASCII_BACKSPACE '\b'
#define ASCII_DELETE 127
#define ASCII_ENTER 13
#define ASCII_NULL '\0'

#define BACKGROUND_MUSIC_HIGHEST_VALUE 13
#define WINDOW_HEIGHT 650
#define WINDOW_WIDTH 1000

WINDOW_EVENT gEventType = START;
// Word Grid related global variables
char gWordGrid[MAX_BOX_COUNT + 1][MAX_BOX_COUNT + 1]; // 1-indexed
GAME_LEVEL gWordGridLevel = LEVEL_3;
int gWordGridBoxCount = 10;
int gWordGridPositionX;
int gWordGridPositionY;
int gWordGridCurrentRow = 1;
int gWordGridCurrentColumn = 1;
int gWordGridFilledCount = 0;
// Player info
char gPlayer1Name[20];
char gPlayer2Name[20];
int gPlayer1NameLastIndex = 0;
int gPlayer2NameLastIndex = 0;
int gPlayer1Character = 0;
int gPlayer2Character = 0;
bool gPlayerNameInputBoxEnanbled = false;
int gPlayerSelectionTickedCharacter = 0; // 0 = None, 1 = Character 1, 2 = Character 2
// Score info
int gIgnoredScore = 0; // Ignore scores < 2
int gPlayer1Score = 0;
int gPlayer2Score = 0;
// Time
int gInGameTime = 0;
char gInGameTimeChars[10];
// Mouse
int gMouseClickedPositionX = __INT_MAX__;
int gMouseClickedPositionY = __INT_MAX__;
int gMousePointerPositionX;
int gMousePointerPositionY;
// Others
int gBackgroundMusicInterval = 0;
int gBackgroundMusicTimerSlot;
int gSelectedMenu = MENU_COUNT; // Select nothing (meaning select Start Game at the next move)
int gClearDisplay = true;

int getCurrentPlayer()
{
	return gWordGridFilledCount % 2 != 0 ? 1 : 2;
}

int getWordGridBoxCount()
{
	switch (gWordGridLevel)
	{
	case LEVEL_1:
		return 5;
	case LEVEL_2:
		return 6;
	default:
	case LEVEL_3:
		return 10;
	}
}

void incrementInGameTime()
{
	if (gEventType == IN_GAME_WINDOW)
		++gInGameTime;
}

void handleBackgroundMusic()
{
	++gBackgroundMusicInterval;
}

void findMaxWordAndUpdateScores()
{
	char wordCandidate[MAX_WORD_LEN];
	int max = 0;

	// Scan columns (1-indexed, RTL)
	for (int column = gWordGridCurrentColumn; column < gWordGridBoxCount + 1; ++column)
	{
		for (int firstColumn = gWordGridCurrentColumn; firstColumn >= 1; --firstColumn)
		{
			if (gWordGrid[gWordGridCurrentRow][firstColumn] == ASCII_NULL)
			{
				// Empty value encountered, no further word matching is possible
				break;
			}
			// Read LTR
			int t = 0;
			for (int i = firstColumn; i <= column; ++i, ++t)
			{
				if (gWordGrid[gWordGridCurrentRow][i] == ASCII_NULL)
					break;
				wordCandidate[t] = gWordGrid[gWordGridCurrentRow][i];
			}
			wordCandidate[t] = ASCII_NULL;

			for (int i = 0; i < MAX_WORD_SIZE; ++i)
			{
				if (strcmp(wordCandidate, word[i]) == 0)
				{
					if (strlen(wordCandidate) > max)
					{
						max = strlen(wordCandidate);
					}
				}
			}
		}
	}

	// Scan rows (1-indexed, BTT)
	for (int row = gWordGridCurrentRow; row < gWordGridBoxCount + 1; ++row)
	{
		for (int firstRow = gWordGridCurrentRow; firstRow >= 1; --firstRow)
		{
			if (gWordGrid[firstRow][gWordGridCurrentColumn] == ASCII_NULL)
			{
				// Empty value encountered, no further word matching is possible
				break;
			}
			// Read TTB
			int t = 0;
			for (int l = firstRow; l <= row; l++, t++)
			{
				if (gWordGrid[l][gWordGridCurrentColumn] == ASCII_NULL)
					break;
				wordCandidate[t] = gWordGrid[l][gWordGridCurrentColumn];
			}
			wordCandidate[t] = ASCII_NULL;

			for (int i = 0; i < MAX_WORD_SIZE; ++i)
			{
				if (strcmp(wordCandidate, word[i]) == 0)
				{
					if (strlen(wordCandidate) > max)
					{
						max = strlen(wordCandidate);
					}
				}
			}
		}
	}

	// Update score
	if (max > 2)
		gIgnoredScore += max;
	if (getCurrentPlayer() == 1)
		gPlayer1Score += max;
	else
		gPlayer2Score += max;
	// printf("score = %d, gPlayer1Score = %d, gPlayer2Score = %d, max = %d\n", gIgnoredScore, gPlayer1Score, gPlayer2Score, max);
}

void resetWordGrid()
{
	for (int i = 1; i < gWordGridBoxCount + 1; i++)
	{
		for (int j = 1; j < gWordGridBoxCount + 1; j++)
		{
			gWordGrid[i][j] = ASCII_NULL;
		}
	}
}

void printWordGrid()
{
	for (int i = 1; i < gWordGridBoxCount + 1; i++)
	{
		for (int j = 1; j < gWordGridBoxCount + 1; j++)
		{
			if (gWordGrid[i][j] == ASCII_NULL)
				printf("- ");
			else
				printf("%c ", gWordGrid[i][j]);
		}
		printf("\n");
	}
	printf("\n\n");
	return;
}

bool updateWordGridSelectionBox(int x, int y)
{
	int i, j;
	for (i = 25, gWordGridCurrentColumn = 1; i <= 25 + (gWordGridBoxCount - 1) * 600 / gWordGridBoxCount; i += 600 / gWordGridBoxCount, gWordGridCurrentColumn++)
	{
		for (j = 25 + (gWordGridBoxCount - 1) * 600 / gWordGridBoxCount, gWordGridCurrentRow = 1; j >= 25; j -= 600 / gWordGridBoxCount, gWordGridCurrentRow++)
		{
			if (x >= i && x < i + 600 / gWordGridBoxCount && y >= j && y < j + 600 / gWordGridBoxCount)
			{
				gWordGridPositionX = i;
				gWordGridPositionY = j;
				return true;
			}
		}
	}
	return false;
}

void resetMouseClickedPosition()
{
	gMouseClickedPositionX = __INT_MAX__;
	gMouseClickedPositionY = __INT_MAX__;
}

void initWindow()
{
	resetWordGrid();
	gEventType = WELCOME_WINDOW;
	gInGameTime = 0;
	gBackgroundMusicInterval = 0;
}

void welcomeWindow()
{
	if (gBackgroundMusicInterval % BACKGROUND_MUSIC_HIGHEST_VALUE == 0)
	{
		++gBackgroundMusicInterval;
		playBackgroundMusic;
	}

	// Draw menu
	drawBitmap(0, 0, WELCOME_BACKGROUND);
	drawBitmap(860, 550, MENU_START_GAME);
	drawBitmap(860, 495, MENU_LEVEL);
	drawBitmap(860, 440, MENU_HELP);
	drawBitmap(860, 385, MENU_QUIT);

	if (gMousePointerPositionX > 860)
	{
		// Change into expanded state on hovering over the menu items
		if (gMousePointerPositionY < 440)
			drawBitmap(790, 385, MENU_QUIT_EXPANDED);
		else if (gMousePointerPositionY < 495)
			drawBitmap(790, 440, MENU_HELP_EXPANDED);
		else if (gMousePointerPositionY < 550)
			drawBitmap(790, 495, MENU_LEVEL_EXPANDED);
		else if (gMousePointerPositionY < 605)
			drawBitmap(790, 550, MENU_START_GAME_EXPANDED);
	}
	if (gMouseClickedPositionX > 860 && gMouseClickedPositionY >= 350 && gMouseClickedPositionY <= 600)
	{
		// Pause background music
		gBackgroundMusicInterval = 1;
		// stopSound();
		pauseTimer(gBackgroundMusicTimerSlot);
		if (gMouseClickedPositionY > 550 && gMouseClickedPositionY < 600)
		{
			// Start game
			playMouseClickMusic;
			gEventType = PLAYER_1_SELECTION_WINDOW;
			gInGameTime = 0;
			resetWordGrid();
			gPlayer1Score = 0;
			gPlayer2Score = 0;
			gPlayer1Character = 0;
			gPlayer2Character = 0;
			updateWordGridSelectionBox(25, 600);
		}
		else if (gMouseClickedPositionY > 495 && gMouseClickedPositionY < 545)
		{
			// Level selection
			gEventType = LEVEL_SELECTION_WINDOW;
			gWordGridLevel = LEVEL_3;
			playMouseClickMusic;
		}
		else if (gMouseClickedPositionY > 440 && gMouseClickedPositionY < 490)
		{
			// Help
			gEventType = HELP_WINDOW;
			playMouseClickMusic;
		}
		else if (gMouseClickedPositionY > 330 && gMouseClickedPositionY < 435)
		{
			// Quit
			playMouseClickMusic;
			exit(0);
		}
		resetMouseClickedPosition();
	}
}

void helpWindow()
{
	drawBitmap(0, 0, HELP_BACKGROUND);
}

void levelSelectionWindow()
{
	drawBitmap(0, 0, LEVEL_SELECTION_BACKGROUND);
	setColor(241, 225, 163);
	// Level selection
	if (gMouseClickedPositionX >= 375 && gMouseClickedPositionX <= 631)
	{
		if (gMouseClickedPositionY >= 650 - 222 && gMouseClickedPositionY <= 650 - 163)
		{
			// Level 1
			gWordGridLevel = LEVEL_1;
			gWordGridBoxCount = getWordGridBoxCount();
			playMouseClickMusic;
			resetMouseClickedPosition();
		}
		if (gMouseClickedPositionY >= 650 - 293 && gMouseClickedPositionY <= 650 - 234)
		{
			// Level 2
			gWordGridLevel = LEVEL_2;
			gWordGridBoxCount = getWordGridBoxCount();
			playMouseClickMusic;
			resetMouseClickedPosition();
		}
		if (gMouseClickedPositionY >= 650 - 367 && gMouseClickedPositionY <= 650 - 308)
		{
			// Level 3
			gWordGridLevel = LEVEL_3;
			gWordGridBoxCount = getWordGridBoxCount();
			playMouseClickMusic;
			resetMouseClickedPosition();
		}
	}
	// Highlight selected level
	if (gWordGridLevel == LEVEL_1)
	{
		// Level 1
		drawRectangle(375, 650 - 222, 257, 58);
	}
	else if (gWordGridLevel == LEVEL_2)
	{
		// Level 2
		drawRectangle(375, 650 - 293, 257, 58);
	}
	else if (gWordGridLevel == LEVEL_3)
	{
		// Level 3
		drawRectangle(375, 650 - 367, 257, 58);
	}
	// Click OK
	if (gMouseClickedPositionX >= 505 && gMouseClickedPositionX <= 579)
	{
		if (gMouseClickedPositionY >= 0 && gMouseClickedPositionY <= 41)
		{
			gEventType = PLAYER_1_SELECTION_WINDOW;
			resetWordGrid();
			updateWordGridSelectionBox(25, 600);
			gInGameTime = 0;
			gPlayer1Score = 0;
			gPlayer2Score = 0;
			playMouseClickMusic;
			resetMouseClickedPosition();
		}
	}
}

void player1SelectionWindow()
{
	drawBitmap(0, 0, PLAYER_1_SELECTION_BACKGROUND);
	// Observe if player name input box is clicked
	if (gMouseClickedPositionX > 347 && gMouseClickedPositionX < 630)
	{
		if (gMouseClickedPositionY > 650 - 315 && gMouseClickedPositionY < 650 - 243)
		{
			playMouseClickMusic;
			gPlayerNameInputBoxEnanbled = true;
			gMouseClickedPositionX = 0;
			gMouseClickedPositionY = 0;
			resetMouseClickedPosition();
		}
	}
	// Enable player name input box
	if (gPlayerNameInputBoxEnanbled)
	{
		setColor(255, 255, 0);
		drawRectangle(351, 650 - 308, 275, 52);
	}
	// Set player name from user input
	setColor(241, 225, 163);
	drawText(364, 650 - 290, gPlayer1Name, FONT_FAMILY);
	// Observe if character 1 is chosen
	if (gMouseClickedPositionX > 95 && gMouseClickedPositionX < 230)
	{
		if (gMouseClickedPositionY > 650 - 475 && gMouseClickedPositionY < 650 - 167)
		{
			gPlayerSelectionTickedCharacter = 1;
			playMouseClickMusic;
			resetMouseClickedPosition();
		}
	}
	// Check character 1 if it is chosen
	if (gPlayerSelectionTickedCharacter == 1)
	{
		drawBitmap(223, 650 - 240, PLAYER_SELECTION_TICK_MARK);
	}
	// Observe if character 2 is chosen
	if (gMouseClickedPositionX > 778 && gMouseClickedPositionX < 875)
	{
		if (gMouseClickedPositionY > 650 - 481 && gMouseClickedPositionY < 650 - 156)
		{
			gPlayerSelectionTickedCharacter = 2;
			gPlayer1Character = 1;
			playMouseClickMusic;
			resetMouseClickedPosition();
		}
	}
	// Check character 2 if it is chosen
	if (gPlayerSelectionTickedCharacter == 2)
	{
		drawBitmap(872, 650 - 240, PLAYER_SELECTION_TICK_MARK);
	}
	// Observe if OK is clicked
	if (gMouseClickedPositionX > 400 && gMouseClickedPositionX < 485)
	{
		if (gMouseClickedPositionY > 650 - 623 && gMouseClickedPositionY < 650 - 532)
		{
			// OK is clicked, proceed to palyer 2 selection window
			gEventType = PLAYER_2_SELECTION_WINDOW;
			gPlayerNameInputBoxEnanbled = 0;
			gPlayerSelectionTickedCharacter = 0;
			playMouseClickMusic;
			resetMouseClickedPosition();
		}
	}
}

void player2SelectionWindow()
{
	drawBitmap(0, 0, PLAYER_2_SELECTION_BACKGROUND);
	// Observe if player name input box is clicked
	if (gMouseClickedPositionX > 347 && gMouseClickedPositionX < 630)
	{
		if (gMouseClickedPositionY > 650 - 315 && gMouseClickedPositionY < 650 - 243)
		{
			gPlayerNameInputBoxEnanbled = true;
			playMouseClickMusic;
			resetMouseClickedPosition();
		}
	}
	// Enable player name input box
	if (gPlayerNameInputBoxEnanbled)
	{
		setColor(255, 255, 0);
		drawRectangle(351, 650 - 308, 275, 52);
	}
	// Set player name from user input
	setColor(241, 225, 163);
	drawText(364, 650 - 290, gPlayer2Name, FONT_FAMILY);
	// Observe if character 1 is chosen
	if (gMouseClickedPositionX > 95 && gMouseClickedPositionX < 230)
	{
		if (gMouseClickedPositionY > 650 - 475 && gMouseClickedPositionY < 650 - 167)
		{
			gPlayerSelectionTickedCharacter = 1;
			playMouseClickMusic;
			resetMouseClickedPosition();
		}
	}
	// Check character 1 if it is chosen
	if (gPlayerSelectionTickedCharacter == 1)
	{
		drawBitmap(223, 650 - 240, PLAYER_SELECTION_TICK_MARK);
	}
	// Observe if character 2 is chosen
	if (gMouseClickedPositionX > 778 && gMouseClickedPositionX < 875)
	{
		if (gMouseClickedPositionY > 650 - 481 && gMouseClickedPositionY < 650 - 156)
		{
			gPlayerSelectionTickedCharacter = 2;
			gPlayer2Character = 2;
			playMouseClickMusic;
			resetMouseClickedPosition();
		}
	}
	// Check character 2 if it is chosen
	if (gPlayerSelectionTickedCharacter == 2)
	{
		drawBitmap(872, 650 - 240, PLAYER_SELECTION_TICK_MARK);
	}
	// Observe if OK is clicked
	if (gMouseClickedPositionX > 400 && gMouseClickedPositionX < 485)
	{
		if (gMouseClickedPositionY > 650 - 623 && gMouseClickedPositionY < 650 - 532)
		{
			// OK is clicked, load the game
			gEventType = IN_GAME_WINDOW;
			gPlayerNameInputBoxEnanbled = 0;
			gPlayerSelectionTickedCharacter = 0;
			resetWordGrid();
			playMouseClickMusic;
			resetMouseClickedPosition();
		}
	}
}

void inGameWindow()
{
	// printf("gWordGridCurrentRow = %d, gWordGridCurrentColumn = %d\n", gWordGridCurrentRow, gWordGridCurrentColumn);
	setColor(55, 42, 30);
	drawFilledRectangle(0, 0, 1000, 650);

	setColor(35, 31, 29);
	drawFilledRectangle(17, 17, 616, 616);

	setColor(110, 104, 81);
	drawFilledRectangle(25, 25, 600, 600);

	for (int i = 1; i < gWordGridBoxCount + 1; i++)
	{
		for (int j = 1; j < gWordGridBoxCount + 1; j++)
		{
			if (gWordGrid[i][j] != ASCII_NULL)
			{
				int pos = (int)gWordGrid[i][j] - 97;
				if (pos < 26 && pos >= 0)
				{
					if (gWordGridLevel == LEVEL_1)
						drawBitmap((25 + (j - 1) * 600 / gWordGridBoxCount), 25 + ((gWordGridBoxCount - i) * 600 / gWordGridBoxCount), l1Letter[pos]);
					if (gWordGridLevel == LEVEL_2)
						drawBitmap((25 + (j - 1) * 600 / gWordGridBoxCount), 25 + ((gWordGridBoxCount - i) * 600 / gWordGridBoxCount), l2Letter[pos]);
					if (gWordGridLevel == LEVEL_3)
						drawBitmap((25 + (j - 1) * 600 / gWordGridBoxCount), 25 + ((gWordGridBoxCount - i) * 600 / gWordGridBoxCount), l3Letter[pos]);
				}
			}
		}
	}

	for (int i = 25; i <= 25 + (gWordGridBoxCount - 1) * 600 / gWordGridBoxCount; i += 600 / gWordGridBoxCount)
	{
		for (int j = 25; j <= 25 + (gWordGridBoxCount - 1) * 600 / gWordGridBoxCount; j += 600 / gWordGridBoxCount)
		{
			setColor(55, 42, 30);
			drawRectangle(i, j, 600 / gWordGridBoxCount, 600 / gWordGridBoxCount);
		}
	}

	setColor(35, 31, 29);
	drawFilledRectangle(650, 16, 330, 618);
	drawBitmap(658, 24, SCOREBOARD);

	// Player 1's scoreboard
	if (gPlayer1Score <= 9)
	{
		drawBitmap(810, 428, digit[0]);
		drawBitmap(890, 428, digit[gPlayer1Score]);
	}
	else
	{
		char score[5];
		sprintf(score, "%d", gPlayer1Score);
		drawBitmap(810, 428, digit[score[0] - 48]);
		drawBitmap(890, 428, digit[score[1] - 48]);
	}

	// Player 2's Scoreboard
	if (gPlayer2Score <= 9)
	{
		drawBitmap(810, 76, digit[0]);
		drawBitmap(890, 76, digit[gPlayer2Score]);
	}
	else
	{
		char score[5];
		sprintf(score, "%d", gPlayer2Score);
		drawBitmap(810, 76, digit[score[0] - 48]);
		drawBitmap(890, 76, digit[score[1] - 48]);
	}

	setColor(172, 172, 172);
	drawRectangle(gWordGridPositionX, gWordGridPositionY, 600 / gWordGridBoxCount, 600 / gWordGridBoxCount);
	setColor(250, 250, 250);
	drawText(840, 385, gPlayer1Name, FONT_FAMILY);
	drawText(840, 40, gPlayer2Name, FONT_FAMILY);

	int h = gInGameTime / 3600;
	int m = (gInGameTime % 3600) / 60;
	int s = (gInGameTime % 3600) % 60;
	sprintf(gInGameTimeChars, "%02d:%02d:%02d", h, m, s);
	drawText(844, 300, gInGameTimeChars, FONT_FAMILY);

	if (gPlayer1Character == 1)
		drawBitmap(658, 368, CHARACTER_BOY);
	if (gPlayer2Character == 2)
		drawBitmap(658, 25, CHARACTER_GRU);

	setColor(35, 31, 29);
	drawFilledCircle(791, 556, 12, 800);

	setColor(69, 69, 69);
	drawFilledCircle(791, 556, 10, 800);

	setColor(35, 31, 29);
	drawFilledCircle(774, 190, 12, 800);

	setColor(69, 69, 69);
	drawFilledCircle(774, 190, 10, 800);

	if (getCurrentPlayer() == 2)
	{
		setColor(69, 182, 45);
		drawFilledCircle(791, 556, 16, 800);
		setColor(250, 0, 0);
		drawFilledCircle(791, 556, 14, 800);
	}
	else
	{
		setColor(69, 182, 45);
		drawFilledCircle(774, 190, 16, 800);

		setColor(250, 0, 0);
		drawFilledCircle(774, 190, 14, 800);
	}
	// Check if time exceeds or all values are filled in
	if (s >= 5 * 60 || gWordGridFilledCount == gWordGridBoxCount * gWordGridBoxCount)
	{
		gEventType = RESULT_WINDOW;
	}
}

void resultWindow()
{
	gWordGridFilledCount = 0;
	gInGameTime = 0;
	setColor(30, 34, 224);
	drawBitmap(0, 0, RESULT_BACKGROUND);
	if (gPlayer1Score > gPlayer2Score)
		drawText(450, 650 - 65, gPlayer1Name, FONT_FAMILY);
	else if (gPlayer2Score > gPlayer1Score)
		drawText(450, 650 - 65, gPlayer2Name, FONT_FAMILY);
	else
	{
		drawText(350, 650 - 65, gPlayer1Name, FONT_FAMILY);
		drawText(450, 650 - 65, "and", FONT_FAMILY);
		drawText(500, 650 - 65, gPlayer2Name, FONT_FAMILY);
	}
}

void displayHandler()
{
	// printf("Current event = %d\n", gEventType);
	switch (gEventType)
	{
	case START:
		initWindow();
		break;
	case WELCOME_WINDOW:
		welcomeWindow();
		break;
	case HELP_WINDOW:
		helpWindow();
		break;
	case LEVEL_SELECTION_WINDOW:
		levelSelectionWindow();
		break;
	case PLAYER_1_SELECTION_WINDOW:
		player1SelectionWindow();
		break;
	case PLAYER_2_SELECTION_WINDOW:
		player2SelectionWindow();
		break;
	case IN_GAME_WINDOW:
		inGameWindow();
		break;
	case RESULT_WINDOW:
		resultWindow();
	}
	glutSwapBuffers();
}

void mouseClickHandler(int button, int state, int mx, int my)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		gMouseClickedPositionX = mx;
		gMouseClickedPositionY = glutGet(GLUT_WINDOW_HEIGHT) - my;
		if (gEventType == IN_GAME_WINDOW && updateWordGridSelectionBox(gMouseClickedPositionX, gMouseClickedPositionY))
		{
			playMouseClickMusic;
		}
	}
	glFlush();
}

void mouseHoverHandler(int mx, int my)
{
	gMousePointerPositionX = mx;
	gMousePointerPositionY = glutGet(GLUT_WINDOW_HEIGHT) - my;
	glFlush();
}

void keyboardHandler(unsigned char key, int x, int y)
{
	if (gEventType == WELCOME_WINDOW)
	{
		if (key == ASCII_ENTER)
		{
			gMouseClickedPositionX = gMousePointerPositionX;
			gMouseClickedPositionY = gMousePointerPositionY;
			glutPostRedisplay();
		}
		return;
	}
	if (gEventType == LEVEL_SELECTION_WINDOW)
	{
		if (key == ASCII_ENTER)
		{
			gMouseClickedPositionX = 550;
			gMouseClickedPositionY = 20;
			glutPostRedisplay();
		}
		return;
	}
	if (key == ASCII_BACKSPACE && gEventType != PLAYER_1_SELECTION_WINDOW && gEventType != PLAYER_2_SELECTION_WINDOW)
	{
		// Go back to the main window
		resetMouseClickedPosition();
		gEventType = WELCOME_WINDOW;
		gBackgroundMusicInterval = 0;
		resumeTimer(gBackgroundMusicTimerSlot);
		glutPostRedisplay();
		return;
	}
	if (gEventType == PLAYER_1_SELECTION_WINDOW)
	{
		if (key == ASCII_BACKSPACE || key == ASCII_DELETE)
		{
			gPlayer1NameLastIndex--;
			gPlayer1Name[gPlayer1NameLastIndex] = ASCII_NULL;
			playKeyboardMusic;
		}
		else if (key == ASCII_ENTER)
		{
			gEventType = PLAYER_2_SELECTION_WINDOW;
			gPlayerNameInputBoxEnanbled = 0;
			gPlayerSelectionTickedCharacter = 0;
			playMouseClickMusic;
		}
		else
		{
			gPlayer1Name[gPlayer1NameLastIndex] = key;
			gPlayer1NameLastIndex++;
			playKeyboardMusic;
		}
		glutPostRedisplay();
		return;
	}
	if (gEventType == PLAYER_2_SELECTION_WINDOW)
	{
		if (key == ASCII_BACKSPACE || key == ASCII_DELETE)
		{
			gPlayer2NameLastIndex--;
			gPlayer2Name[gPlayer2NameLastIndex] = ASCII_NULL;
			playKeyboardMusic;
		}
		else if (key == ASCII_ENTER)
		{
			gEventType = IN_GAME_WINDOW;
			gPlayerNameInputBoxEnanbled = 0;
			gPlayerSelectionTickedCharacter = 0;
			resetWordGrid();
			playMouseClickMusic;
		}
		else
		{
			gPlayer2Name[gPlayer2NameLastIndex] = key;
			gPlayer2NameLastIndex++;
			playKeyboardMusic;
		}
		glutPostRedisplay();
		return;
	}
	if (gWordGrid[gWordGridCurrentRow][gWordGridCurrentColumn] == ASCII_NULL && key >= 'a' && key <= 'z')
	{
		// Insert a letter only when the grid value is empty
		gWordGrid[gWordGridCurrentRow][gWordGridCurrentColumn] = key;
		// printf("Position(%d, %d) => %c\n", gWordGridCurrentRow, gWordGridCurrentColumn, key);
		// printWordGrid();
		playKeyboardMusic;
		++gWordGridFilledCount;
		findMaxWordAndUpdateScores();
		glutPostRedisplay();
	}
}

void inGameNavigationHandler(int key, int x, int y)
{
	if (gEventType == WELCOME_WINDOW)
	{
		if (key == GLUT_KEY_UP)
		{
			if (gSelectedMenu < MENU_COUNT - 1)
			{
				++gSelectedMenu;
			}
			gMousePointerPositionX = 861;
			gMousePointerPositionY = (int)(430 + 42 * gSelectedMenu);
			glutPostRedisplay();
		}
		else if (key == GLUT_KEY_DOWN)
		{
			if (gSelectedMenu > 0)
			{
				--gSelectedMenu;
			}
			gMousePointerPositionX = 861;
			gMousePointerPositionY = (int)(430 + 42 * gSelectedMenu);
			glutPostRedisplay();
		}
		return;
	}
	if (gEventType == LEVEL_SELECTION_WINDOW)
	{
		if (key == GLUT_KEY_UP)
		{
			if (gWordGridLevel > 0)
			{
				gWordGridLevel = (GAME_LEVEL)(gWordGridLevel - 1);
			}
			gMouseClickedPositionX = gMousePointerPositionX = 375;
			gMouseClickedPositionY = gMousePointerPositionY = (int)(650 - 222 - 49 * gWordGridLevel);
			glutPostRedisplay();
		}
		else if (key == GLUT_KEY_DOWN)
		{
			if (gWordGridLevel < LEVEL_COUNT - 1)
			{
				gWordGridLevel = (GAME_LEVEL)(gWordGridLevel + 1);
			}
			gMouseClickedPositionX = gMousePointerPositionX = 375;
			gMouseClickedPositionY = gMousePointerPositionY = (int)(650 - 222 - 49 * gWordGridLevel);
			glutPostRedisplay();
		}
		return;
	}
	if (gEventType == IN_GAME_WINDOW)
	{
		if (key == GLUT_KEY_RIGHT)
		{
			if (gWordGridPositionX < 25 + (gWordGridBoxCount - 1) * 600 / gWordGridBoxCount)
			{
				playNavigationMusic;
				gWordGridPositionX += 600 / gWordGridBoxCount;
				++gWordGridCurrentColumn;
				glutPostRedisplay();
			}
		}
		else if (key == GLUT_KEY_LEFT)
		{
			if (gWordGridPositionX > 25)
			{
				playNavigationMusic;
				gWordGridPositionX -= 600 / gWordGridBoxCount;
				--gWordGridCurrentColumn;
				glutPostRedisplay();
			}
		}
		else if (key == GLUT_KEY_UP)
		{
			if (gWordGridPositionY < 25 + (gWordGridBoxCount - 1) * 600 / gWordGridBoxCount)
			{
				playNavigationMusic;
				gWordGridPositionY += 600 / gWordGridBoxCount;
				--gWordGridCurrentRow;
				glutPostRedisplay();
			}
		}
		else if (key == GLUT_KEY_DOWN)
		{
			if (gWordGridPositionY > 25)
			{
				playNavigationMusic;
				gWordGridPositionY -= 600 / gWordGridBoxCount;
				++gWordGridCurrentRow;
				glutPostRedisplay();
			}
		}
	}
}

void animateCallback(void)
{
	if (gClearDisplay)
	{
		gClearDisplay = false;
		clearDisplay();
	}
	glutPostRedisplay();
}

void initialize(int width, int height, char *title)
{
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(width, height);
	glutInitWindowPosition(10, 10);
	glutCreateWindow(title);
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, width, 0.0, height, -1.0, 1.0);

	clearDisplay();

	glutDisplayFunc(displayHandler);
	glutKeyboardFunc(keyboardHandler);
	glutSpecialFunc(inGameNavigationHandler);
	glutMouseFunc(mouseClickHandler);
	glutPassiveMotionFunc(mouseHoverHandler);
	glutIdleFunc(animateCallback);

	glutMainLoop();
}

int main(int argc, char **argv)
{
	soundInit();
	int slotTime = startTimer(1, incrementInGameTime);
	gBackgroundMusicTimerSlot = startTimer(1, handleBackgroundMusic);
	glutInit(&argc, argv);
	initialize(WINDOW_WIDTH, WINDOW_HEIGHT, APP_NAME);
	stopTimer(slotTime);
	stopTimer(gBackgroundMusicTimerSlot);
	soundClose();
	return 0;
}
