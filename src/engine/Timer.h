#pragma once
#ifndef SMART_RTU_SRC_ENGINE_TIMER_H_
#define SMART_RTU_SRC_ENGINE_TIMER_H_


#include <ctime>/*timespec*/


//***********************************************************************************************
//*** Timer: GetTime() returns time in ms from Timer object creation moment (period ~580 years)
//***********************************************************************************************

typedef unsigned long long int LongTimeMs;

class Timer
{
public:
	LongTimeMs GetTime();
	Timer();
private:
	timespec tmStart;
	LongTimeMs TimeToMs(const timespec aTime);

};

extern Timer timer;
extern const char *StrNow();

#endif/*SMART_RTU_SRC_ENGINE_TIMER_H_*/