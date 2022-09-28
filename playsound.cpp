/**
 * Workaround for playing sound in non-Windows using SDL2.
 * It uses https://github.com/jakebesworth/Simple-SDL2-Audio library.
 * 
 * Author: Muntashir Al-Islam <muntashirakon@riseup.net>
 */

#ifdef __WINDOWS__
#include <windows.h>
#else
#include "sdl2_audio/audio.h"
#endif

#include "playsound.h"

int soundInit()
{
#ifndef __WINDOWS__
    if (SDL_Init(SDL_INIT_AUDIO) < 0)
    {
        fprintf(stderr, "Couldn't initialise audio: %s\n", SDL_GetError());
        return 1;
    }
    initAudio();
#endif
    return 0;
}

void soundClose()
{
#ifndef __WINDOWS__
    endAudio();
    SDL_Quit();
#endif
}

int playWav(char *filename, char *mod, int flags)
{
#ifdef __WINDOWS__
    PlaySound(filename, mod, flags);
#else
    pauseAudio();
    playSound(filename, SDL_MIX_MAXVOLUME / 3);
    unpauseAudio();
#endif
    return 0;
}

void stopWav() {
#ifdef __WINDOWS__
    PlaySound(NULL, NULL, 0);
#else
    pauseAudio();
    stopSound();
#endif
}
