/* WgBackground Author: Igors Kolcins
*-- This is visual widget.
*		This widget render only backgroud of widget with shadows
*		and have empety update.
*/

#pragma once

#include "IWidget.h"
#include <string>

enum wgColor
{
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
enum wgMode
{
	md1x1 = 1,
	md1x2,
	md1x3,
	md3x8,
	mdCustom
};

class WgBackground : 
public IWidget
{
public:
	WgBackground(int pos_x, int pos_y, wgMode Amode);
	~WgBackground();

	void SetFillColor(wgColor c); //set color of block with command Fill
	void SetTextColor(wgColor c); //set color of text

	void GetRect(int &left, int &bottom, int &width, int &height);
	void render()override;
	bool update() override { return false; };
	bool IsVisible()override { return true; };

protected:
	int m_pos_x, m_pos_y;	  // position in the grid
	wgMode mode;	  // widget mode
	int sizeX, sizeY; // widget size in the grid, example: sizeX=1; sizeY=1; fill only one block in the grid
	wgColor color;
	bool shadows_on; // on/off shadows
	std::string m_base_font_name;//mean name of font without extension

	struct
	{
		int left, right, top, bottom, width, height;
	} rectWidget, rectHeader, rectClient;
	struct
	{
		int left, right, top, bottom;
	} shadowSize;

	void RenderHeader(const char *header_text);
	void RenderOnlyShadows(); //renders only all shadows //kastil
};
