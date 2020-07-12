#include "WgBackground.h"

#include<cstdlib>//rand()

//libshape stuff probably can cut some not used
/*OpenVG stuff like Rect(),Fill*/
extern "C"
{
#include "VG/openvg.h"
#include "VG/vgu.h"
#include "fontinfo.h"
#include "shapes.h"
}

#include "../engine/desktop.h" /*desktop obj*/
#include "CFontStorage.h"      /*font obj*/
#include "CPicturesStorage.h"  /*picture storage obj*/
#include "configurator.h"      /*config*/


const struct {
  unsigned int r, g, b;
} Colors[] = {
    {255, 255, 255}, // clWhite
    {0, 121, 194},   // clBlue
    {37, 196, 166},  // clCyan
    {139, 209, 93},  // clGreen
    {0, 185, 241},   // clHighBlue
    {139, 91, 164},  // clHighPurple
    {201, 208, 34},  // clLazyYellow
    {240, 115, 30},  // clOrange
    {183, 46, 145},  // clPurple
    {255, 200, 50},  // clYellow
    {0, 85, 81}      // clHaki
};


WgBackground::WgBackground(int a_pos_x, int a_pos_y, WgMode Amode) 
: m_pos_x(a_pos_x), // horizontal position in the grid
  m_pos_y(a_pos_y),// vertical position in the grid
  widget_mode_(Amode),
  shadows_on_(true)
{
  widget_update_time_ = 0; // never
  color_ = WgColor(1 + rand() % 10);//????????

  //shadows_on_ = true; // shadows on
  config->Get("BASE_FONT_BASE_NAME", base_font_base_name_);

  // -- select widget size from widget_mode_
  switch (widget_mode_) {
  case md1x1:{
    widget_width_ = 1;
    widget_height_ = 1;
    break;
  }
  case md1x2:{
    widget_width_ = 1;
    widget_height_ = 2;
    break;
  }
  case md1x3:{
    widget_width_ = 1;
    widget_height_ = 3;
    break;
  }
  case md3x8:{
    widget_width_ = 3;
    widget_height_ = 8;
    break;
  }
  default:{
    widget_width_ = Get_width();
    widget_height_ = Get_height();
  }
  }

  ShadowSize.left = PicStorage->WgShadows->l->Get_width();
  ShadowSize.right = PicStorage->WgShadows->r->Get_width();
  ShadowSize.top = PicStorage->WgShadows->t->Get_height();
  ShadowSize.bottom = PicStorage->WgShadows->b->Get_height();

  RectWidget.left = desktop->DwRect.left + desktop->colum_width * m_pos_x;
  RectWidget.right = RectWidget.left + desktop->colum_width * widget_width_;
  RectWidget.top = desktop->DwRect.bottom + desktop->row_height * m_pos_y;
  RectWidget.bottom = RectWidget.top - desktop->row_height * widget_height_;
  RectWidget.width = desktop->colum_width * widget_width_;
  RectWidget.height = desktop->row_height * widget_height_;

  RectHeader = RectWidget;
  RectHeader.bottom = RectWidget.top - desktop->row_height;
  RectHeader.height = desktop->row_height;

  RectClient = RectWidget;
  RectClient.top = RectWidget.top - desktop->row_height;
  RectClient.height = RectWidget.height - desktop->row_height;
}

WgBackground::~WgBackground() {

}

void WgBackground::SetTextColor(WgColor c) {
  
  FontStorage->GetFont(const_cast<char *>(base_font_base_name_.c_str()))
      ->Set_Color(Colors[c].r, Colors[c].g, Colors[c].b);

}

void WgBackground::SetFillColor(WgColor c) {
  Fill(Colors[c].r, Colors[c].g, Colors[c].b, 1);
}

void WgBackground::render() {
  // -- render widget background blocks

  this->SetFillColor(clWhite);
  Rect(RectClient.left, RectClient.bottom, RectClient.width, RectClient.height);
  this->SetFillColor(color_);
  Rect(RectHeader.left, RectHeader.bottom, RectHeader.width, RectHeader.height);

  if (shadows_on_) // -- render widget shadows
  {
    this->RenderOnlyShadows();
  }
}

void WgBackground::GetRect(int &left, int &bottom, int &width, int &height) {
  left = RectWidget.left;
  bottom = RectWidget.bottom;
  width = RectWidget.width;
  height = RectWidget.height;
}

void WgBackground::RenderWidgetHeader(const char *a_header_text) {
  int font_width = RectHeader.width * 0.8;
  TFont *font =
      FontStorage->GetFont(const_cast<char *>(base_font_base_name_.c_str()));
  
  font->Set_Color(255, 255, 255);

  int font_height = RectHeader.height * 0.6;
  font->Set_Size(font_height);

  if (font->TextWidth(a_header_text) > font_width) {
    font_height = (font_height * font_width) / font->TextWidth(a_header_text);
    font->Set_Size(font_height);
  }

  font->TextMid(a_header_text, RectHeader.left + RectHeader.width / 2,
                RectHeader.bottom + (RectHeader.height - font_height) / 2);
}

void WgBackground::RenderOnlyShadows() {
  // -- -- render horizontal shadows
  for (int i = 0; i < RectWidget.width; ++i) {
    PicStorage->WgShadows->t->render(RectWidget.left + i,
                                     RectWidget.top - ShadowSize.top);
    PicStorage->WgShadows->b->render(RectWidget.left + i, RectWidget.bottom);
  }

  // -- -- render vertical shadows
  for (int i = 0; i < RectWidget.height; ++i) {
    PicStorage->WgShadows->l->render(RectWidget.left, RectWidget.top - i);
    PicStorage->WgShadows->r->render(RectWidget.right - ShadowSize.right,
                                     RectWidget.top - i);
  }
}