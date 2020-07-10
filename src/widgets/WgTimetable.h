#pragma once

#ifndef SMART_RTU_SRC_WIDGETS_WGTIMETABLE_H_
#define SMART_RTU_SRC_WIDGETS_WGTIMETABLE_H_

/*
    restyled by RazdolbayOne
*/
#include <sys/stat.h>/*time_t*/

#include <string>/*string*/

#include "IWidget.h"

class WgTimetable : public IWidget {
public:
  ~WgTimetable();
  WgTimetable();
  bool update()override;
  void render()override;
  bool IsVisible() override { return false; };
  void GetRect(int &x, int &y, int &w, int &h) {
    x = 0;
    y = 0;
    w = 0;
    h = 0;
  }
  void Set_widget_id(int m_widget_id) override {
    this->m_widget_id = m_widget_id;
  }
  int Get_widget_update_time() override { return 1000; } // 1000ms = 1 time /
                                                         // sec
private:
  time_t m_GetFileTime(); // get time then file was edited
  int m_widget_id;
  time_t m_file_time;
  std::string m_timetable_dest;
  std::string m_timetable_name;
};

#endif /*SMART_RTU_SRC_WIDGETS_WGTIMETABLE_H_*/