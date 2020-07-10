#include "WgTimetable.h"

#include <sys/types.h>/*stat sctruct*/

#include<iostream>


#include "Engine.h"/*engine obj*/
#include "timetable.h"/*tiemtable obj*/

#include "Timer.h"/*StrNow()*/

#include"configurator.h"/*config*/


time_t WgTimetable::m_GetFileTime()
{
    struct stat buff;
    if (stat((m_timetable_dest+"/"+m_timetable_name).c_str(), &buff) == 0)
        return buff.st_mtime;
    return 0;
}

WgTimetable::WgTimetable()
{
    m_file_time = m_GetFileTime();

    config->Get("TIME_TABLE_DEST",m_timetable_dest);
    config->Get("TIME_TABLE_NAME",m_timetable_name);

    std::cout<<StrNow()<<"\tWgTimetable widget object was created\n";
}

WgTimetable::~WgTimetable()
{
    std::cout<<StrNow()<<"\tWgTimetable widget object was deleted\n";
}

bool WgTimetable::update()
{
    if (m_file_time != m_GetFileTime())
    {
        if (timetable){
            delete timetable;
        }
        
        try
        {
            timetable = new Timetable;
        }
        catch (...)
        {
            timetable = nullptr;
        }
        m_file_time = m_GetFileTime();
        engine->ForceUpdate();
    }
    return false;
}
