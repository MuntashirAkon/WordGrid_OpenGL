/**
 * Workaround for playing sound in non-Windows using SDL2.
 * It uses https://github.com/jakebesworth/Simple-SDL2-Audio library.
 * 
 * Author: Muntashir Al-Islam <muntashirakon@riseup.net>
 */

#ifndef _H_PLAY_SOUND
#define _H_PLAY_SOUND

#ifndef __WINDOWS__
#define SND_FILENAME 0
#define SND_ASYNC 0
#endif

int soundInit();

void soundClose();

int playWav(char *filename, char *mod, int flags);

void stopWav();

#endif // _H_PLAY_SOUND
