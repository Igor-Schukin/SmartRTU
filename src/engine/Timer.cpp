#include "Timer.h"

#include <cstdio>/*sprintf*/
#include <ctime>/*tymespec*/

Timer timer;

Timer::Timer()
{
	clock_gettime(CLOCK_REALTIME, &tmStart);
}

LongTimeMs Timer::TimeToMs(const timespec aTime)
{
	return aTime.tv_sec * 1000LLU + aTime.tv_nsec / 1000000LLU;
}

LongTimeMs Timer::GetTime()
{
	timespec now;
	clock_gettime(CLOCK_REALTIME, &now);
	return TimeToMs(now) - TimeToMs(tmStart);
}

const char *StrNow()
{
	static char buf[75];//changed from 25
	time_t time_now = std::time(nullptr);
	struct tm *now = localtime(&time_now);
	sprintf(
		buf,
		"%02d.%02d.%04d %02d:%02d:%02d",
		now->tm_mday, now->tm_mon, now->tm_year + 1900,
		now->tm_hour, now->tm_min, now->tm_sec);
	return buf;
}

