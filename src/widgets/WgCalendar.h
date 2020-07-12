/*WgCalendar Author: Igors Kolcins
 *--This visual widget
 *
 */
#pragma once

#ifndef SMART_RTU_SRC_WIDGETS_WGCALENDAR_H_
#define SMART_RTU_SRC_WIDGETS_WGCALENDAR_H_

#include "WgBackground.h"
#include <string>/*string*/

class WgCalendar
 : public WgBackground 
 {

public:
  WgCalendar(int AposX, int AposY, WgMode Amode);
  ~WgCalendar();

  bool update() override;
  void render() override;

private:
  char bufer_for_date_[32], buffer_week_day_[32];
  char buffer_week_info_[50], bufer_week_[32];

  const char *ConvertWeekDayFromInt_(int a_week_day);
  const char *ConvertMonthFromInt_(int a_month);

  std::string BASE_FONT_BASE_NAME; // mean name of font without extension

  void RenderMode1_();
  void RenderMode2_();
  void RenderMode3_();
};
#endif /*SMART_RTU_SRC_WIDGETS_WGCALENDAR_H_*/