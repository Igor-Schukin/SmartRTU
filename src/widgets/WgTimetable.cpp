#include "WgTimetable.h"

#include <sys/types.h>/*stat sctruct*/
#include "Engine.h"/*engine obj*/
#include "timetable.h"/*tiemtable obj*/

#include "Timer.h"/*strNow()*/

#include"configurator.h"/*config*/


time_t WgTimetable::getFileTime()
{
    struct stat buff;
    if (stat((m_timetable_dest+"/"+m_timetable_name).c_str(), &buff) == 0)
        return buff.st_mtime;
    return 0;
}

WgTimetable::WgTimetable()
{
    fileTime = getFileTime();

    config->Get("TIME_TABLE_DEST",m_timetable_dest);
    config->Get("TIME_TABLE_NAME",m_timetable_name);

    std::cout<<strNow()<<"\tWgTimetable widget object was created\n";
}

WgTimetable::~WgTimetable()
{
    std::cout<<strNow()<<"\tWgTimetable widget object was deleted\n";
}

bool WgTimetable::update()
{
    if (fileTime != getFileTime())
    {
        if (timetable)
            delete timetable;
        try
        {
            timetable = new Timetable;
        }
        catch (...)
        {
            timetable = NULL;
        }
        fileTime = getFileTime();
        engine->forcedUpdate();
    }
    return false;
}
