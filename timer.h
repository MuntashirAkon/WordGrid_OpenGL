/**
 * Cross platform timer functions.
 * 
 * Author: Muntashir Al-Islam <muntashirakon@riseup.net>
 */

#ifndef _H_TIMER
#define _H_TIMER

#include <stdio.h>
#ifdef __WINDOWS__
#include <windows.h>
#include <GL/glaux.h>
#else
#include <unistd.h>
#include <pthread.h>
#endif

#define MAX_TIMER_COUNT 10

enum TIMER_STATE
{
    TIMER_UNSET,
    TIMER_STARTED,
    TIMER_PAUSED,
    TIMER_STOPPED
};

void (*timerCallbacks[MAX_TIMER_COUNT])(void) = {0};
int timerState[MAX_TIMER_COUNT] = {0};

#ifdef __WINDOWS__
static void __stdcall timerCallback0(HWND, unsigned int, unsigned int, unsigned long)
{
    if (timerState[0] == TIMER_STARTED)
        timerCallbacks[0]();
}
static void __stdcall timerCallback1(HWND, unsigned int, unsigned int, unsigned long)
{
    if (timerState[1] == TIMER_STARTED)
        timerCallbacks[1]();
}
static void __stdcall timerCallback2(HWND, unsigned int, unsigned int, unsigned long)
{
    if (timerState[2] == TIMER_STARTED)
        timerCallbacks[2]();
}
static void __stdcall timerCallback3(HWND, unsigned int, unsigned int, unsigned long)
{
    if (timerState[3] == TIMER_STARTED)
        timerCallbacks[3]();
}
static void __stdcall timerCallback4(HWND, unsigned int, unsigned int, unsigned long)
{
    if (timerState[4] == TIMER_STARTED)
        timerCallbacks[4]();
}
static void __stdcall timerCallback5(HWND, unsigned int, unsigned int, unsigned long)
{
    if (timerState[5] == TIMER_STARTED)
        timerCallbacks[5]();
}
static void __stdcall timerCallback6(HWND, unsigned int, unsigned int, unsigned long)
{
    if (timerState[6] == TIMER_STARTED)
        timerCallbacks[6]();
}
static void __stdcall timerCallback7(HWND, unsigned int, unsigned int, unsigned long)
{
    if (timerState[7] == TIMER_STARTED)
        timerCallbacks[7]();
}
static void __stdcall timerCallback8(HWND, unsigned int, unsigned int, unsigned long)
{
    if (timerState[8] == TIMER_STARTED)
        timerCallbacks[8]();
}
static void __stdcall timerCallback9(HWND, unsigned int, unsigned int, unsigned long)
{
    if (timerState[9] == TIMER_STARTED)
        timerCallbacks[9]();
}
int timerPointer[MAX_TIMER_COUNT] = {0};
#else
int timerDelay[MAX_TIMER_COUNT] = {0};
pthread_t threadId[MAX_TIMER_COUNT] = {0};

static void *threadCallbackExecutor(int slot)
{
    while (timerState[slot] != TIMER_STOPPED)
    {
        sleep(timerDelay[slot]);
        if (timerState[slot] == TIMER_STARTED)
            timerCallbacks[slot]();
    }
    return 0;
}

static void *threadCallback0(void *arg)
{
    return threadCallbackExecutor(0);
}
static void *threadCallback1(void *arg)
{
    return threadCallbackExecutor(1);
}
static void *threadCallback2(void *arg)
{
    return threadCallbackExecutor(2);
}
static void *threadCallback3(void *arg)
{
    return threadCallbackExecutor(3);
}
static void *threadCallback4(void *arg)
{
    return threadCallbackExecutor(4);
}
static void *threadCallback5(void *arg)
{
    return threadCallbackExecutor(5);
}
static void *threadCallback6(void *arg)
{
    return threadCallbackExecutor(6);
}
static void *threadCallback7(void *arg)
{
    return threadCallbackExecutor(7);
}
static void *threadCallback8(void *arg)
{
    return threadCallbackExecutor(8);
}
static void *threadCallback9(void *arg)
{
    return threadCallbackExecutor(9);
}
#endif

int startTimer(int delaySeconds, void (*callback)(void))
{
    // Find a slot for this callback
    int slot = 0;
    for (; slot < MAX_TIMER_COUNT; ++slot)
    {
        if (timerCallbacks[slot] == 0)
        {
            break;
        }
    }
    if (slot == MAX_TIMER_COUNT)
    {
        fprintf(stderr, "Reached maximum number of slots\n");
        return -1;
    }
    timerCallbacks[slot] = callback;
    timerState[slot] = TIMER_STARTED;
#ifdef __WINDOWS__
    if (slot == 0)
        timerPointer[0] = SetTimer(0, 0, delaySeconds * 1000, timerCallback0);
    else if (slot == 1)
        timerPointer[1] = SetTimer(0, 0, delaySeconds * 1000, timerCallback1);
    else if (slot == 2)
        timerPointer[2] = SetTimer(0, 0, delaySeconds * 1000, timerCallback2);
    else if (slot == 3)
        timerPointer[3] = SetTimer(0, 0, delaySeconds * 1000, timerCallback3);
    else if (slot == 4)
        timerPointer[4] = SetTimer(0, 0, delaySeconds * 1000, timerCallback4);
    else if (slot == 5)
        timerPointer[5] = SetTimer(0, 0, delaySeconds * 1000, timerCallback5);
    else if (slot == 6)
        timerPointer[6] = SetTimer(0, 0, delaySeconds * 1000, timerCallback6);
    else if (slot == 7)
        timerPointer[7] = SetTimer(0, 0, delaySeconds * 1000, timerCallback7);
    else if (slot == 8)
        timerPointer[8] = SetTimer(0, 0, delaySeconds * 1000, timerCallback8);
    else if (slot == 9)
        timerPointer[9] = SetTimer(0, 0, delaySeconds * 1000, timerCallback9);
#else
    timerDelay[slot] = delaySeconds;
    if (slot == 0)
        pthread_create(&threadId[0], NULL, &threadCallback0, NULL);
    else if (slot == 1)
        pthread_create(&threadId[1], NULL, &threadCallback1, NULL);
    else if (slot == 2)
        pthread_create(&threadId[2], NULL, &threadCallback2, NULL);
    else if (slot == 3)
        pthread_create(&threadId[3], NULL, &threadCallback3, NULL);
    else if (slot == 4)
        pthread_create(&threadId[4], NULL, &threadCallback4, NULL);
    else if (slot == 5)
        pthread_create(&threadId[5], NULL, &threadCallback5, NULL);
    else if (slot == 6)
        pthread_create(&threadId[6], NULL, &threadCallback6, NULL);
    else if (slot == 7)
        pthread_create(&threadId[7], NULL, &threadCallback7, NULL);
    else if (slot == 8)
        pthread_create(&threadId[8], NULL, &threadCallback8, NULL);
    else if (slot == 9)
        pthread_create(&threadId[9], NULL, &threadCallback9, NULL);
#endif
    return slot;
}

void pauseTimer(int slot)
{
    if (slot >= 0 && slot < MAX_TIMER_COUNT)
    {
        timerState[slot] = TIMER_PAUSED;
    }
}

void resumeTimer(int slot)
{
    if (slot >= 0 && slot < MAX_TIMER_COUNT)
    {
        timerState[slot] = TIMER_STARTED;
    }
}

void stopTimer(int slot)
{
    if (slot >= 0 && slot < MAX_TIMER_COUNT)
    {
        timerState[slot] = TIMER_STOPPED;
#ifdef __WINDOWS__
        if (timerPointer[slot])
        {
            KillTimer(0, timerPointer[slot]);
            timerPointer[slot] = 0;
        }
#else
        if (threadId[slot])
        {
            pthread_cancel(threadId[slot]);
            threadId[slot] = 0;
        }
#endif
        timerState[slot] = TIMER_UNSET;
    }
}

#endif // _H_TIMER