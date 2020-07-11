#include "WgBackground.h"

#include<cstdlib>//rand()

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
  m_widget_mode(Amode),
  m_shadows_on(true)
{
  m_widget_update_time = 0; // never
  m_color = WgColor(1 + rand() % 10);//????????

  //m_shadows_on = true; // shadows on
  config->Get("BASE_FONT_NAME", m_base_font_name);

  // -- select widget size from m_widget_mode
  switch (m_widget_mode) {
  case md1x1:
    m_widget_width = 1;
    m_widget_height = 1;
    break;
  case md1x2:
    m_widget_width = 1;
    m_widget_height = 2;
    break;
  case md1x3:
    m_widget_width = 1;
    m_widget_height = 3;
    break;
  case md3x8:
    m_widget_width = 3;
    m_widget_height = 8;
    break;
  default:
    m_widget_width = Get_width();
    m_widget_height = Get_height();
  }

  ShadowSize.left = PicStorage->WgShadows->l->Get_width();
  ShadowSize.right = PicStorage->WgShadows->r->Get_width();
  ShadowSize.top = PicStorage->WgShadows->t->Get_height();
  ShadowSize.bottom = PicStorage->WgShadows->b->Get_height();

  RectWidget.left = desktop->DwRect.left + desktop->colum_width * m_pos_x;
  RectWidget.right = RectWidget.left + desktop->colum_width * m_widget_width;
  RectWidget.top = desktop->DwRect.bottom + desktop->row_height * m_pos_y;
  RectWidget.bottom = RectWidget.top - desktop->row_height * m_widget_height;
  RectWidget.width = desktop->colum_width * m_widget_width;
  RectWidget.height = desktop->row_height * m_widget_height;

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
  
  FontStorage->GetFont(const_cast<char *>(m_base_font_name.c_str()))
      ->Set_Color(Colors[c].r, Colors[c].g, Colors[c].b);

}

void WgBackground::SetFillColor(WgColor c) {
  Fill(Colors[c].r, Colors[c].g, Colors[c].b, 1);
}

void WgBackground::render() {
  // -- render widget background blocks

  SetFillColor(clWhite);
  Rect(RectClient.left, RectClient.bottom, RectClient.width, RectClient.height);
  SetFillColor(m_color);
  Rect(RectHeader.left, RectHeader.bottom, RectHeader.width, RectHeader.height);

  if (m_shadows_on) // -- render widget shadows
  {
    RenderOnlyShadows();
  }
}

void WgBackground::GetRect(int &left, int &bottom, int &width, int &height) {
  left = RectWidget.left;
  bottom = RectWidget.bottom;
  width = RectWidget.width;
  height = RectWidget.height;
}

void WgBackground::RenderWidgetHeader(const char *header_text) {
  int maxw = RectHeader.width * 0.8;
  TFont *font =
      FontStorage->GetFont(const_cast<char *>(m_base_font_name.c_str()));
  font->Set_Color(255, 255, 255);
  int fh = RectHeader.height * 0.6;
  font->Set_Size(fh);
  if (font->TextWidth(header_text) > maxw) {
    fh = (fh * maxw) / font->TextWidth(header_text);
    font->Set_Size(fh);
  }

  font->TextMid(header_text, RectHeader.left + RectHeader.width / 2,
                RectHeader.bottom + (RectHeader.height - fh) / 2);
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