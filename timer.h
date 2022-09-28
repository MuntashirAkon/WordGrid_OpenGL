/**
 * Cross platform timer functions.
 * 
 * Author: Muntashir Al-Islam <muntashirakon@riseup.net>
 */

#ifndef _H_TIMER
#define _H_TIMER

#define MAX_TIMER_COUNT 10

enum TIMER_STATE
{
    TIMER_UNSET,
    TIMER_STARTED,
    TIMER_PAUSED,
    TIMER_STOPPED
};

int startTimer(int delaySeconds, void (*callback)(void));

void pauseTimer(int slot);

void resumeTimer(int slot);

void stopTimer(int slot);

#endif // _H_TIMER
