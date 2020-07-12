#pragma once

#ifndef SMART_RTU_SRC_ENGINE_TIMETABLE_H_
#define SMART_RTU_SRC_ENGINE_TIMETABLE_H_

#include <string>
#include <ctime>/*time_t*/

#include "json.h"//

using json = nlohmann::json;


struct TimetableDate
{
    int y, m, d;
    TimetableDate(json &tt)
    {
        y = tt.value("y", 0);
        if (y <= 0)
        {
            std::time_t t = time(nullptr);
            struct tm *now = localtime(&t);
            y = now->tm_year + 1900;
        }
        if (y < 1000)
            y += 2000;
        m = tt["m"];
        d = tt["d"];
    }
    TimetableDate(struct tm date)
    {
        d = date.tm_mday;
        m = date.tm_mon + 1;
        y = date.tm_year + 1900;
    }
    TimetableDate(const TimetableDate &date)
    {
        d = date.d;
        m = date.m;
        y = date.y;
    }
};

struct TimetableDateRange
{
    enum
    {
        drUnknown,
        drSemester,
        drSession
    } type;
    int number;
    TimetableDate begin, end;
    TimetableDateRange(json &tt) : begin(tt["begin"]), end(tt["end"])
    {
        if (tt["semester"].is_number_integer())
        {
            type = drSemester;
            number = tt["semester"];
        }
        else if (tt["session"].is_number_integer())
        {
            type = drSession;
            number = tt["session"];
        }
        else
        {
            type = drUnknown;
            number = tt["number"];
        }
    }
};

struct TimetableTime
{
    int h, m;
    TimetableTime(json &tt)
    {
        m = tt["m"];
        h = tt["h"];
    }
};

struct TimetableLecture
{
    TimetableTime begin, beginBreak, endBreak, end;
    TimetableLecture(json &tt) : begin(tt["begin"]),
                                 end(tt["end"]),
                                 beginBreak(tt["begin-break"]),
                                 endBreak(tt["end-break"])
    {
    }
    bool IsFinished(struct tm time);
    bool isNotStarted(struct tm time);
    bool IsRunning(struct tm time);
    bool isBreak(struct tm time);
    bool isFirstHour(struct tm time);
    bool isSecondHour(struct tm time);
};

struct TimetableWeekDay
{
    int lectures_count;
    TimetableLecture **lectures;
    TimetableWeekDay(json &tt, json &defs);
    ~TimetableWeekDay();
};

struct TimetableDay : TimetableWeekDay
{
    TimetableDate date;
    TimetableDay(json &tt, json &defs) : TimetableWeekDay(tt["lectures"], defs), date(tt["date"]) {}
    ~TimetableDay() {}
};

struct TimeTableSocketTime
{
    TimetableTime on, off;
    TimeTableSocketTime(json &tt) : on(tt["on"]), off(tt["off"]) {}
    bool isSwitchedOn(struct tm time);
};

struct TimetableSocket
{
    int socket;
    TimeTableSocketTime *weekdays;
    TimeTableSocketTime *sundays;
    TimeTableSocketTime *holidays;
    TimetableSocket(json &tt, int sock)
    {
        socket = sock;
        if (tt["weekdays"].size())
            weekdays = new TimeTableSocketTime(tt["weekdays"]);
        else
            weekdays = nullptr;
        if (tt["sundays"].size())
            sundays = new TimeTableSocketTime(tt["sundays"]);
        else
            sundays = nullptr;
        if (tt["holidays"].size())
            holidays = new TimeTableSocketTime(tt["holidays"]);
        else
            holidays = nullptr;
    }
    ~TimetableSocket()
    {
        if (weekdays){
            delete weekdays;
        }
        if (sundays){
            delete sundays;
        }
        if (holidays){
            delete holidays;
        }
    }
};

enum TimeState
{
    tsUnknown,
    tsLecture1h,
    tsLecture2h,
    tsShortBreak,
    tsBreak,
    tsFree,
    tsSession
};
enum DateState
{
    dsUnknown,
    dsSemester,
    dsSession,
    dsVacation,
    dsHoliday
};

extern struct tm makeNow();

class Timetable
{
public:
    TimeState GetCurrentTimeState(int &secToEnd, int &lectNumber);
    DateState GetCurrentDateState(int &weekNumber);
    bool GetCurrentSocketState(int Socket);

    int getHoliday(struct tm now = makeNow());

    Timetable();
    ~Timetable();
private:

    int m_GetWeekNumber(const TimetableDate &origin, struct tm now = makeNow());
    int m_GetWeeksCount(const TimetableDateRange *dates);

    //all about desyianation/name of timetabl.json
    std::string m_time_table_dest;
    std::string m_time_table_name;

    TimetableWeekDay *Week[7];
    int SinglesCount;
    TimetableDay **Singles;
    int HolidaysCount;
    TimetableDate **Holidays;
    int CalendarCount;
    TimetableDateRange **Calendar;
    int SocketsCount;
    TimetableSocket **Sockets;

};

extern Timetable *timetable;

#endif /*SMART_RTU_SRC_ENGINE_TIMETABLE_H_*/