/* WgBackground Author: Igors Kolcins
 *-- This is visual widget.
 *		This widget render only backgroud of widget with shadows
 *		and have empety update.
 */

#pragma once
#ifndef SMART_RTU_SRC_WIDGETS_WGBACKGROUND_H_
#define SMART_RTU_SRC_WIDGETS_WGBACKGROUND_H_

#include "IWidget.h"
#include <string>

enum WgColor {
  clWhite = 0,
  clBlue,
  clCyan,
  clGreen,
  clHighBlue,
  clHighPurple,
  clLazyYellow,
  clOrange,
  clPurple,
  clYellow,
  clHaki
};
enum WgMode { md1x1 = 1, md1x2, md1x3, md3x8, mdCustom };

class WgBackground :
 public IWidget 
 {
public:
  WgBackground(int a_pos_x, int a_pos_y, WgMode Amode);
  ~WgBackground();

  void SetFillColor(WgColor c); // set color_ of block with command Fill
  void SetTextColor(WgColor c); // set color_ of text

  void GetRect(int &left, int &bottom, int &width, int &height)override;
  void render() override;
  bool update() override { return false; };
  bool IsVisible() override { return true; };

protected:
  int m_pos_x, m_pos_y; // position in the grid
  WgMode widget_mode_;          // widget_mode
  WgColor color_;
  bool shadows_on_;              // on/off shadows

  // widget size in the grid, example: widget_width_=1; widget_height_=1;
  // fill only one block in the grid
  int widget_width_, widget_height_; 
  
  std::string base_font_base_name_; // mean name of font without extension

  struct {
    int left, right, top, bottom, width, height;
  } RectWidget, RectHeader, RectClient;
  struct {
    int left, right, top, bottom;
  } ShadowSize;

  //renders text at widget header
  void RenderWidgetHeader(const char *a_header_text);
  void RenderOnlyShadows(); // renders only all shadows //kastil
};

#endif /*SMART_RTU_SRC_WIDGETS_WGBACKGROUND_H__*/