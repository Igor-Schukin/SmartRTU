#pragma once
#ifndef SMART_RTU_SRC_WIDGETS_WGWATCHDOG_H_
#define SMART_RTU_SRC_WIDGETS_WGWATCHDOG_H_

#include <string>

#include "IWidget.h"

class WgWatchdog : public IWidget {
public:
  ~WgWatchdog();
  WgWatchdog();
  bool update()override;
  void render()override;
  bool IsVisible() override { return false; };
  void GetRect(int &x, int &y, int &w, int &h) {
    x = 0;
    y = 0;
    w = 0;
    h = 0;
  }
  void Set_widget_id(int a_widget_id) override;
  int Get_widget_update_time() override { return 10 * 60 * 1000; } // 10min

private:
  int widget_id_;
  std::string watchdog_name_;
  std::string watchdog_path_;
};
#endif /*SMART_RTU_SRC_WIDGETS_WGWATCHDOG_H_*/