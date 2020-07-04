#pragma once
/*
    restyled by RazdolbayOne
*/
#include <sys/stat.h>/*time_t*/

#include<string>/*string*/

#include "IWidget.h"

class WgTimetable : public IWidget
{
public:
    ~WgTimetable();
    WgTimetable();
    bool update();
    void render() {}
    bool IsVisible()override { return false; };
    void getRect(int &x, int &y, int &w, int &h)
    {
        x = 0;
        y = 0;
        w = 0;
        h = 0;
    }
    void setId(int id) { this->id = id; }
    int getUpdateTime() { return 1000; } //1000ms = 1 time / sec
private:
    int id;
    time_t fileTime;
    time_t getFileTime();
    std::string m_timetable_dest;
    std::string m_timetable_name;
};