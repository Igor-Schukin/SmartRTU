/*WgClock Author: Igors Kolcins
*-- This is visual widget.
*		His only update time and render it.
*		Background render parent class WgBackground
* 
*--  -- Modes: it has 3 modes
*			md1x1: show only time
*			md1x2: show time and current lecture
*			md1x3: show time, current lecture and show timer to the next lecture
*/
#pragma once
#include <string>/*string*/

#include "WgBackground.h"

class WgClock : public WgBackground
{
public:
	WgClock(int AposX, int AposY, wgMode Amode);
	~WgClock();

	bool update()override;
	void render()override;
private:
	int hour, min, sec; // last update time
	char strTime[10], strLect[20], strInfo[100], strTimer[15];
	std::string m_base_font_name;//mean name of font without extension

	void m_RenderMode1();
	void m_RenderMode2();
	void m_RenderMode3();

};
