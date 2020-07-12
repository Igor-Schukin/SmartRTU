#pragma once

#ifndef SMART_RTU_SRC_WIDGETS_WGTIMETABLE_H_
#define SMART_RTU_SRC_WIDGETS_WGTIMETABLE_H_

/*
    restyled by RazdolbayOne
*/
#include <sys/stat.h>/*time_t*/
#include<ctime> //time_t
#include <string>/*string*/

#include "IWidget.h"

class WgTimetable 
: public IWidget 
{
public:
  ~WgTimetable();
  WgTimetable();
  bool update()override;
  void render()override;
  bool IsVisible() override { return false; };
  void GetRect(int &x, int &y, int &w, int &h) override {
    x = 0;
    y = 0;
    w = 0;
    h = 0;
  }
  void Set_widget_id(int a_widget_id) override;
  int Get_widget_update_time() override { return 1000; } // 1000ms = 1 time /
                                                         // sec
private:
  std::time_t GetFileTime_(); // get time then file was edited
  
  int widget_id_;
  std::time_t file_time_;
  std::string timetable_path_;
  std::string timetable_name_;
};

#endif /*SMART_RTU_SRC_WIDGETS_WGTIMETABLE_H_*/