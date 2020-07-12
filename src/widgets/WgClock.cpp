#include "WgClock.h"

#include <cstdio>            /*sprintf*/
#include <cstring>/*strcpy*/ //probably need to go to c++ string
#include <ctime>             /*time() e.t.c*/
#include <iostream>          /*cout*/

#include "CFontStorage.h" /*FontStorage obj*/
#include "Timer.h"        /*StrNow()*/
#include "configurator.h" /*config*/
#include "desktop.h"      /*desktop*/
#include "timetable.h"    /*need timetable obj*/

#define STR_TIME_EMPTY "--:--"

#define STR_TIMER_EMPTY "- - : - -"
#define STR_TIMER_LONG "> stunda"

#define STR_LECT_EMPTY "- - - - - -"
#define STR_LECT_LECTURE "%d. lekcija"
#define STR_LECT_SHORTBRAKE "starpbrīdis"
#define STR_LECT_BRAKE "pārtraukums"
#define STR_LECT_FREETIME "brīvlaiks"
#define STR_LECT_SESSION "sessija"

//FIXME WHAT TO DO IN tsUnknown
#define STR_LECT_ERROR "defaultErrr"


#define STR_INFO_EMPTY "saraksts nav ielādēts"
#define STR_INFO_ERROR "saraksts ir kļūdains"
#define STR_INFO_HOUREND "līdz starpbrīdim"
#define STR_INFO_LECTEND "līdz lekcijas beigām"
#define STR_INFO_BRAKEEND "līdz starpbrīža beigām"
#define STR_INFO_LECTBEG "līdz lekcijas sākumām"
#define STR_INFO_DAYBEG "līdz lekciju sākumām"
#define STR_INFO_EMPTYDAY "šodien lekciju nav"



WgClock::WgClock(int Ax, int Ay, WgMode Amode) 
: WgBackground(Ax, Ay, Amode) 
{
  widget_update_time_ = 100; // 10 times per sec

  hour = -1;
  min = -1;
  sec = -1;
  std::strcpy(strTime, STR_TIME_EMPTY);
  std::strcpy(strLect, STR_LECT_EMPTY);
  std::strcpy(strInfo, STR_INFO_EMPTY);
  std::strcpy(strTimer, STR_TIMER_EMPTY);

  config->Get("BASE_FONT_NAME", base_font_name_);

  std::cout << StrNow() << "\t"
            << "WgClock widget object was created\n";
}

WgClock::~WgClock() {
  std::cout << StrNow() << "\t"
            << "WgClock widget object was deleted\n";
}

//~~~ update ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

bool WgClock::update() {
  std::time_t _now = time(nullptr);
  struct tm *now = localtime(&_now);
  if (now->tm_hour == hour && now->tm_min == min && now->tm_sec == sec)
    return false;
  hour = now->tm_hour;
  min = now->tm_min;
  sec = now->tm_sec;

  std::sprintf(strTime, "%02d:%02d", now->tm_hour, now->tm_min);

  int end, lect;
  TimeState ts;
  if (timetable)
    ts = timetable->GetCurrentTimeState(end, lect);
  else {
    ts = tsUnknown;
    end = -1;
    lect = -1;
  }

  if (ts == tsUnknown) {
    std::strcpy(strLect, STR_LECT_EMPTY);
    std::strcpy(strInfo, STR_INFO_ERROR);
    std::strcpy(strTimer, STR_TIMER_EMPTY);
    return true;
  }

  switch (ts) {
  case tsLecture1h:
  case tsLecture2h:
    std::sprintf(strLect, STR_LECT_LECTURE, lect);
    break;
  case tsShortBreak:
    std::sprintf(strLect, STR_LECT_SHORTBRAKE);
    break;
  case tsBreak:
    std::sprintf(strLect, STR_LECT_BRAKE);
    break;
  case tsFree:
    std::sprintf(strLect, STR_LECT_FREETIME);
    break;
  case tsSession:
    std::sprintf(strLect, STR_LECT_SESSION);
    break;
  case tsUnknown:
    std::sprintf(strLect, "It's me the UNKNOWN!");
    break;
  default:
    std::sprintf(strLect, STR_LECT_ERROR);
    break;
  }

  switch (ts) {
  case tsLecture1h:
    std::strcpy(strInfo, STR_INFO_HOUREND);
    break;
  case tsLecture2h:
    std::strcpy(strInfo, STR_INFO_LECTEND);
    break;
  case tsShortBreak:
    std::strcpy(strInfo, STR_INFO_BRAKEEND);
    break;
  case tsBreak:
    std::strcpy(strInfo, STR_INFO_LECTBEG);
    break;
  case tsSession:
    break;
  case tsFree:
    std::strcpy(strInfo, end >= 0 ? STR_INFO_DAYBEG : STR_INFO_EMPTYDAY);
    break;
  case tsUnknown:
     std::strcpy(strInfo, "UFO stole the lecture");
    break;
  default:
  std::strcpy(strInfo, "Undefined behavoir");
    break;
  }

  if (end < 0)
    std::strcpy(strTimer, STR_TIMER_EMPTY);
  else if (end > 60 * 60)
    std::strcpy(strTimer, STR_TIMER_LONG);
  else
    std::sprintf(strTimer, "%02d:%02d", end / 60, end % 60);

  return true;
}

//~~~ rendering  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void WgClock::RenderMode1_() { 
  RenderWidgetHeader(strTime); 
}

void WgClock::RenderMode2_() {
  SetTextColor(clHaki);
  FontStorage->GetFont(const_cast<char *>(base_font_name_.c_str()))
      ->Set_Size(desktop->row_height / 3);

  FontStorage->GetFont(const_cast<char *>(base_font_name_.c_str()))
      ->TextMid(strLect, RectClient.left + (RectClient.width / 2),
                RectClient.top - desktop->row_height / 16 * 11 //?
      );
}

void WgClock::RenderMode3_() {
  SetTextColor(clHaki);
  FontStorage->GetFont(const_cast<char *>(base_font_name_.c_str()))
      ->Set_Size(desktop->row_height / 4.5);

  FontStorage->GetFont(const_cast<char *>(base_font_name_.c_str()))
      ->TextMid(
          strInfo, RectClient.left + (RectClient.width / 2),
          RectClient.top - desktop->row_height - (desktop->row_height / 5 / 2) //?
      );

  SetTextColor(color_);
  FontStorage->GetFont(const_cast<char *>(base_font_name_.c_str()))
      ->Set_Size(desktop->row_height / 2.2);

  FontStorage->GetFont(const_cast<char *>(base_font_name_.c_str()))
      ->TextMid(
          strTimer, RectClient.left + (RectClient.width / 2),
          RectClient.top - desktop->row_height - (desktop->row_height / 4) * 3 //?
      );
}

void WgClock::render() {
  WgBackground::render();
  switch (widget_mode_) {
  case md1x1: {
    RenderMode1_();
    break;
  }
  case md1x2: {
    RenderMode1_();
    RenderMode2_();
    break;
  }
  case md1x3: {
    RenderMode1_();
    RenderMode2_();
    RenderMode3_();
    break;
  }
  case md3x8: {
    // probably need to delete
    break;
  }
  case mdCustom: {
    // probably need to delete
    break;
  }
  default: {
    std::cerr
        << StrNow() << "\t"
        << "Something bad happened in WgClock render widget_mode_ used default one\n";
    break;
  }
  }
}
