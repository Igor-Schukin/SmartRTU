#include "WgTimetable.h"

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

    fprintf(stdout,"%s\tWgTimetable widget object is created\n", strNow());
}

WgTimetable::~WgTimetable()
{
    fprintf(stdout,"%s\tWgTimetable widget object is deleted\n", strNow());
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
