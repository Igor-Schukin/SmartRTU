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



WgClock::WgClock(int Ax, int Ay, wgMode Amode) : WgBackground(Ax, Ay, Amode) {
  m_widget_update_time = 100; // 10 times per sec

  hour = -1;
  min = -1;
  sec = -1;
  strcpy(strTime, STR_TIME_EMPTY);
  strcpy(strLect, STR_LECT_EMPTY);
  strcpy(strInfo, STR_INFO_EMPTY);
  strcpy(strTimer, STR_TIMER_EMPTY);

  config->Get("BASE_FONT_NAME", m_base_font_name);

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

  sprintf(strTime, "%02d:%02d", now->tm_hour, now->tm_min);

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
    strcpy(strLect, STR_LECT_EMPTY);
    strcpy(strInfo, STR_INFO_ERROR);
    strcpy(strTimer, STR_TIMER_EMPTY);
    return true;
  }

  switch (ts) {
  case tsLecture1h:
  case tsLecture2h:
    sprintf(strLect, STR_LECT_LECTURE, lect);
    break;
  case tsShortBreak:
    sprintf(strLect, STR_LECT_SHORTBRAKE);
    break;
  case tsBreak:
    sprintf(strLect, STR_LECT_BRAKE);
    break;
  case tsFree:
    sprintf(strLect, STR_LECT_FREETIME);
    break;
  case tsSession:
    sprintf(strLect, STR_LECT_SESSION);
    break;
  case tsUnknown:
    sprintf(strLect, "It's me the UNKNOWN!");
    break;
  default:
    sprintf(strLect, STR_LECT_ERROR);
    break;
  }

  switch (ts) {
  case tsLecture1h:
    strcpy(strInfo, STR_INFO_HOUREND);
    break;
  case tsLecture2h:
    strcpy(strInfo, STR_INFO_LECTEND);
    break;
  case tsShortBreak:
    strcpy(strInfo, STR_INFO_BRAKEEND);
    break;
  case tsBreak:
    strcpy(strInfo, STR_INFO_LECTBEG);
    break;
  case tsSession:
    break;
  case tsFree:
    strcpy(strInfo, end >= 0 ? STR_INFO_DAYBEG : STR_INFO_EMPTYDAY);
    break;
  case tsUnknown:
     strcpy(strInfo, "UFO stole the lecture");
    break;
  default:
  strcpy(strInfo, "Undefined behavoir");
    break;
  }

  if (end < 0)
    strcpy(strTimer, STR_TIMER_EMPTY);
  else if (end > 60 * 60)
    strcpy(strTimer, STR_TIMER_LONG);
  else
    sprintf(strTimer, "%02d:%02d", end / 60, end % 60);

  return true;
}

//~~~ rendering  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void WgClock::m_RenderMode1() { 
  RenderHeader(strTime); 
  }

void WgClock::m_RenderMode2() {
  SetTextColor(clHaki);
  FontStorage->GetFont(const_cast<char *>(m_base_font_name.c_str()))
      ->Set_Size(desktop->rowHeight / 3);

  FontStorage->GetFont(const_cast<char *>(m_base_font_name.c_str()))
      ->TextMid(strLect, rectClient.left + (rectClient.width / 2),
                rectClient.top - desktop->rowHeight / 16 * 11 //?
      );
}

void WgClock::m_RenderMode3() {
  SetTextColor(clHaki);
  FontStorage->GetFont(const_cast<char *>(m_base_font_name.c_str()))
      ->Set_Size(desktop->rowHeight / 4.5);

  FontStorage->GetFont(const_cast<char *>(m_base_font_name.c_str()))
      ->TextMid(
          strInfo, rectClient.left + (rectClient.width / 2),
          rectClient.top - desktop->rowHeight - (desktop->rowHeight / 5 / 2) //?
      );

  SetTextColor(color);
  FontStorage->GetFont(const_cast<char *>(m_base_font_name.c_str()))
      ->Set_Size(desktop->rowHeight / 2.2);

  FontStorage->GetFont(const_cast<char *>(m_base_font_name.c_str()))
      ->TextMid(
          strTimer, rectClient.left + (rectClient.width / 2),
          rectClient.top - desktop->rowHeight - (desktop->rowHeight / 4) * 3 //?
      );
}

void WgClock::render() {
  WgBackground::render();
  switch (mode) {
  case md1x1: {
    m_RenderMode1();
    break;
  }
  case md1x2: {
    m_RenderMode1();
    m_RenderMode2();
    break;
  }
  case md1x3: {
    m_RenderMode1();
    m_RenderMode2();
    m_RenderMode3();
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
        << "Something bad happened in WgClock render mode used default one\n";
    break;
  }
  }
}
