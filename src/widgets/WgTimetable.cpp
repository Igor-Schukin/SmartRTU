#include "WgTimetable.h"

#include <sys/types.h>/*stat sctruct*/

#include<iostream>//cout


#include "Engine.h"/*engine obj*/
#include "timetable.h"/*tiemtable obj*/

#include "Timer.h"/*StrNow()*/

#include"configurator.h"/*config*/


std::time_t WgTimetable::GetFileTime_()
{
    struct stat buff;
    if (stat((timetable_path_+"/"+timetable_name_).c_str(), &buff) == 0){
        return buff.st_mtime;
    }
    else{
    return 0;
    }
}

WgTimetable::WgTimetable()
{
    file_time_ = this->GetFileTime_();

    config->Get("TIME_TABLE_PATH",timetable_path_);
    config->Get("TIME_TABLE_NAME",timetable_name_);

    std::cout<<StrNow()<<"\tWgTimetable widget object was created\n";
}

WgTimetable::~WgTimetable()
{
    std::cout<<StrNow()<<"\tWgTimetable widget object was deleted\n";
}

bool WgTimetable::update()
{
    if (file_time_ != GetFileTime_())
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
        file_time_ = GetFileTime_();
        engine->ForceUpdate();
    }
    return false;
}

void WgTimetable::render() {
    //empty
}

void WgTimetable::Set_widget_id(int a_widget_id){
    this->widget_id_ = a_widget_id;
}