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

  void SetFillColor(WgColor c); // set m_color of block with command Fill
  void SetTextColor(WgColor c); // set m_color of text

  void GetRect(int &left, int &bottom, int &width, int &height);
  void render() override;
  bool update() override { return false; };
  bool IsVisible() override { return true; };

protected:
  int m_pos_x, m_pos_y; // position in the grid
  WgMode m_widget_mode;          // widget_mode
  WgColor m_color;
  bool m_shadows_on;              // on/off shadows

  // widget size in the grid, example: m_widget_width=1; m_widget_height=1;
  // fill only one block in the grid
  int m_widget_width, m_widget_height; 
  
  std::string m_base_font_name; // mean name of font without extension

  struct {
    int left, right, top, bottom, width, height;
  } RectWidget, RectHeader, RectClient;
  struct {
    int left, right, top, bottom;
  } ShadowSize;

  //renders text at widget header
  void RenderWidgetHeader(const char *header_text);
  void RenderOnlyShadows(); // renders only all shadows //kastil
};

#endif /*SMART_RTU_SRC_WIDGETS_WGBACKGROUND_H__*/