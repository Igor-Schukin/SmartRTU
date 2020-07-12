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
#ifndef SMART_RTU_SRC_WIDGETS_WGCLOCK_H_
#define SMART_RTU_SRC_WIDGETS_WGCLOCK_H_

#include <string>/*string*/

#include "WgBackground.h"

class WgClock :
public WgBackground
{
public:
	WgClock(int AposX, int AposY, WgMode Amode);
	~WgClock();

	bool update()override;
	void render()override;
private:
	int hour_, min_, second_; // last update time
	char str_time_[10], str_lecture_[20], str_info_[100], str_timer_[15];
	std::string base_font_base_name_;//mean name of font without extension

	void RenderMode1_();
	void RenderMode2_();
	void RenderMode3_();

};
#endif /*SMART_RTU_SRC_WIDGETS_WGCLOCK_H_*/