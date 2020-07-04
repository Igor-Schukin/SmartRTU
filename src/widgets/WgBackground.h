/* WgBackground Author: Igors Kolcins
*-- This is visual widget.
*		This widget render only backgroud of widget with shadows
*		and have empety update.
*/

#pragma once

#include "IWidget.h"
#include "../engine/desktop.h"

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

class WgBackground : public IWidget
{
public:
	WgBackground(int AposX, int AposY, wgMode Amode);
	~WgBackground();

	void setFillColor(wgColor c); //set color of block with command Fill
	void setTextColor(wgColor c); //set color of text

	void getRect(int &left, int &bottom, int &width, int &height);
	void render()override;
	bool update() override { return false; };
	bool IsVisible()override { return true; };

protected:
	int posX, posY;	  // position in the grid
	wgMode mode;	  // widget mode
	int sizeX, sizeY; // widget size in the grid, example: sizeX=1; sizeY=1; fill only one block in the grid
	wgColor color;
	bool isShadows; // on/off shadows

	struct
	{
		int left, right, top, bottom, width, height;
	} rectWidget, rectHeader, rectClient;
	struct
	{
		int left, right, top, bottom;
	} shadowSize;

	void RenderHeader(const char *header_text);
	void renderOnlyShadows(); //renders only all shadows //kastil
};
