#include "WgSockets.h"

WgSockets::WgSockets()
{
    wiringPiSetup();
    for (int i = 0; i < SOCKETS_COUNT; i++)
    {
        curStates[i] = false;
        pinMode(socketsPins[i], OUTPUT);
    }
    fprintf(stdout,"%s\tWgSockets widget object is created\n", strNow());
}

WgSockets::~WgSockets()
{
    fprintf(stdout,"%s\tWgSockets widget object is deleted\n", strNow());
}

bool WgSockets::update()
{
    for (int i = 0; i < SOCKETS_COUNT; i++)
    {
        bool state = timetable->getCurrentSocketState(i + 1);
        digitalWrite(socketsPins[i], state ? HIGH : LOW);
        if (state != curStates[i])
        {
            fprintf(stdout,"%s\tSocket %d is turned %s\n", strNow(), i + 1, state ? "on" : "off");
            curStates[i] = state;
        }
    }
    return false;
}
