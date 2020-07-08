#include "WgBackground.h"
#include "../engine/desktop.h" /*desktop obj*/
#include "CFontStorage.h"      /*font obj*/
#include "CPicturesStorage.h"  /*picture storage obj*/
#include "configurator.h"      /*config*/

WgBackground::WgBackground(int pos_x, int pos_y, wgMode Amode) {
  m_widget_update_time = 0; // never
  m_pos_x = pos_x;          // horizontal position in the grid
  m_pos_y = pos_y;          // vertical position in the grid
  mode = Amode;
  color = wgColor(1 + rand() % 10);

  shadows_on = true; // shadows on
  config->Get("BASE_FONT_NAME", m_base_font_name);
  // -- select widget size from mode

  switch (mode) {
  case md1x1:
    sizeX = 1;
    sizeY = 1;
    break;
  case md1x2:
    sizeX = 1;
    sizeY = 2;
    break;
  case md1x3:
    sizeX = 1;
    sizeY = 3;
    break;
  case md3x8:
    sizeX = 3;
    sizeY = 8;
    break;
  default:
    sizeX = Get_width();
    sizeY = Get_height();
  }

  shadowSize.left = PicStorage->WgShadows->l->Get_width();
  shadowSize.right = PicStorage->WgShadows->r->Get_width();
  shadowSize.top = PicStorage->WgShadows->t->Get_height();
  shadowSize.bottom = PicStorage->WgShadows->b->Get_height();

  rectWidget.left = desktop->dwRect.left + desktop->colWidth * m_pos_x;
  rectWidget.right = rectWidget.left + desktop->colWidth * sizeX;
  rectWidget.top = desktop->dwRect.bottom + desktop->rowHeight * m_pos_y;
  rectWidget.bottom = rectWidget.top - desktop->rowHeight * sizeY;
  rectWidget.width = desktop->colWidth * sizeX;
  rectWidget.height = desktop->rowHeight * sizeY;

  rectHeader = rectWidget;
  rectHeader.bottom = rectWidget.top - desktop->rowHeight;
  rectHeader.height = desktop->rowHeight;

  rectClient = rectWidget;
  rectClient.top = rectWidget.top - desktop->rowHeight;
  rectClient.height = rectWidget.height - desktop->rowHeight;
}

WgBackground::~WgBackground() {

}

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

void WgBackground::SetTextColor(wgColor c) {
  
  FontStorage->GetFont(const_cast<char *>(m_base_font_name.c_str()))
      ->Set_Color(Colors[c].r, Colors[c].g, Colors[c].b);
  /*
  if (c==clBlue) FontStorage->GetFont((char*)"arialBold")->Set_Color(0,121,194);
  else if (c==clCyan)
  FontStorage->GetFont((char*)"arialBold")->Set_Color(37,196,166); else if
  (c==clGreen) FontStorage->GetFont((char*)"arialBold")->Set_Color(139,209,93);
  else if (c==clHighBlue)
  FontStorage->GetFont((char*)"arialBold")->Set_Color(0,185,241); else if
  (c==clHighPurple)
  FontStorage->GetFont((char*)"arialBold")->Set_Color(139,91,164); else if
  (c==clLazyYellow)
  FontStorage->GetFont((char*)"arialBold")->Set_Color(201,208,34); else if
  (c==clOrange) FontStorage->GetFont((char*)"arialBold")->Set_Color(240,115,30);
  else if (c==clPurple)
  FontStorage->GetFont((char*)"arialBold")->Set_Color(183,46,145); else if
  (c==clYellow) FontStorage->GetFont((char*)"arialBold")->Set_Color(255,200,50);
  else if (c==clHaki) FontStorage->GetFont((char*)"arialBold")->Set_Color(0, 85,
  81);
*/
}

void WgBackground::SetFillColor(wgColor c) {
  Fill(Colors[c].r, Colors[c].g, Colors[c].b, 1);
  /*
  if (c==clWhite) Fill(255,255,255,1);
  else if (c==clBlue) Fill(0,121,194,1);
  else if (c==clCyan) Fill(37,196,166,1);
  else if (c==clGreen) Fill(139,209,93,1);
  else if (c==clHighBlue) Fill(0,185,241,1);
  else if (c==clHighPurple) Fill(139,91,164,1);
  else if (c==clLazyYellow) Fill(201,208,34,1);
  else if (c==clOrange) Fill(240,115,30,1);
  else if (c==clPurple) Fill(183,46,145,1);
  else if (c==clYellow) Fill(255,200,50,1);
*/
}

void WgBackground::render() {
  // -- render widget background blocks

  SetFillColor(clWhite);
  // SetFillColor(clOrange);
  Rect(rectClient.left, rectClient.bottom, rectClient.width, rectClient.height);
  SetFillColor(color);
  Rect(rectHeader.left, rectHeader.bottom, rectHeader.width, rectHeader.height);

  if (shadows_on) // -- render widget shadows
  {
    RenderOnlyShadows();
  }
}

void WgBackground::GetRect(int &left, int &bottom, int &width, int &height) {
  left = rectWidget.left;
  bottom = rectWidget.bottom;
  width = rectWidget.width;
  height = rectWidget.height;
}

void WgBackground::RenderHeader(const char *header_text) {
  int maxw = rectHeader.width * 0.8;
  // FIXME this definetly must be different maybe use of configurator
  TFont *font =
      FontStorage->GetFont(const_cast<char *>(m_base_font_name.c_str()));
  font->Set_Color(255, 255, 255);
  int fh = rectHeader.height * 0.6;
  font->Set_Size(fh);
  if (font->TextWidth(header_text) > maxw) {
    fh = (fh * maxw) / font->TextWidth(header_text);
    font->Set_Size(fh);
  }

  font->TextMid(header_text, rectHeader.left + rectHeader.width / 2,
                rectHeader.bottom + (rectHeader.height - fh) / 2);
}

void WgBackground::RenderOnlyShadows() {
  // -- -- render horizontal shadows
  for (int i = 0; i < rectWidget.width; i++) {
    PicStorage->WgShadows->t->render(rectWidget.left + i,
                                     rectWidget.top - shadowSize.top);
    PicStorage->WgShadows->b->render(rectWidget.left + i, rectWidget.bottom);
  }

  // -- -- render vertical shadows
  for (int i = 0; i < rectWidget.height; i++) {
    PicStorage->WgShadows->l->render(rectWidget.left, rectWidget.top - i);
    PicStorage->WgShadows->r->render(rectWidget.right - shadowSize.right,
                                     rectWidget.top - i);
  }
}