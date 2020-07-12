#include "WgCalendar.h"

#include <ctime>/*struct tm*/
#include <iostream>/*cout*/
#include <cstring>/*strcpy*/

#include "CFontStorage.h"/*FontStorage obj*/
#include "timetable.h"/*timetable obj*/
#include "Timer.h"/*StrNow()*/
#include "desktop.h"/*desktop obj*/
#include "configurator.h"/*configurator*/


WgCalendar::WgCalendar(int Ax, int Ay, WgMode Amode) 
: WgBackground(Ax, Ay, Amode)
{
	widget_update_time_ = 60 * 60 * 1000; // 1 hour
	std::strcpy(bufDate, "- -");
	std::strcpy(bufWeekDay, "-");
	std::strcpy(bufWeekInfo, "- - -");
	std::strcpy(bufWeek, "-");

	config->Get("BASE_FONT_NAME",base_font_name_); 

	std::cout<<StrNow()<<"\tWgCalendar widget object was created\n";
}


WgCalendar::~WgCalendar()
{
	std::cout<<StrNow()<<"\tWgCalendar widget object was deleted\n";
}

const char *WgCalendar::ConvertWeekDayFromInt_(int a_week_day)
{
	switch (a_week_day)
	{
	case 0:
		return "svētdiena";
	case 1:
		return "pirmdiena";
	case 2:
		return "otrdiena";
	case 3:
		return "trešdiena";
	case 4:
		return "ceturtdiena";
	case 5:
		return "piektdiena";
	case 6:
		return "sestdiena";
	default:
		return "- - - -";
	}
}

const char *WgCalendar::ConvertMonthFromInt_(int a_month)
{
	switch (a_month)
	{
	case 0:
		return "jan";
	case 1:
		return "feb";
	case 2:
		return "mar";
	case 3:
		return "apr";
	case 4:
		return "mai";
	case 5:
		return "jūn";
	case 6:
		return "jūl";
	case 7:
		return "aug";
	case 8:
		return "sep";
	case 9:
		return "okt";
	case 10:
		return "nov";
	case 11:
		return "dec";
	default:
		return "---";
	}
}

bool WgCalendar::update()
{
	std::time_t lt = std::time(nullptr);
	struct tm *now = std::localtime(&lt);

	std::sprintf(bufDate, "%i.%s", now->tm_mday, ConvertMonthFromInt_(now->tm_mon));

	std::sprintf(bufWeekDay, "%s", ConvertWeekDayFromInt_(now->tm_wday));

	int week = 0;
	switch (timetable->GetCurrentDateState(week))
	{
	case dsSemester:
		std::strcpy(bufWeekInfo, "nedēļa semestrī");
		break;
	case dsSession:
		std::strcpy(bufWeekInfo, "sesijas nedēļa");
		break;
	case dsVacation:
		std::strcpy(bufWeekInfo, "brīvlaika nedēļa");
		break;
	case dsHoliday:
		std::strcpy(bufWeekInfo, "svētki");
		break;
	case dsUnknown:
		std::strcpy(bufWeekInfo, "Nezinams");
		break;
	default:
		std::strcpy(bufWeekInfo, "...");
		break;
	}
	week += 1;

	if (week >= 1)
		std::sprintf(bufWeek, "%d.", week);
	else{
		std::strcpy(bufWeek, "--");
	}
	return true;
}

void WgCalendar::RenderMode1_()
{
	RenderWidgetHeader(bufDate);
}

void WgCalendar::RenderMode2_()
{
	TFont *font = FontStorage->GetFont(
		const_cast<char*>(base_font_name_.c_str())
		);
	SetTextColor(clHaki);
	font->Set_Size(desktop->row_height / 3);
	font->TextMid(
		bufWeekDay,
		RectClient.left + RectClient.width / 2,
		RectClient.top - desktop->row_height / 16 * 11);
}

void WgCalendar::RenderMode3_()
{
	TFont *font = FontStorage->GetFont(
		const_cast<char*>(base_font_name_.c_str())
		);
	font->Set_Size(desktop->row_height / 4.5);
	font->TextMid(
		bufWeekInfo,
		RectClient.left + RectClient.width / 2,
		RectClient.top - desktop->row_height - desktop->row_height / 5 / 2);

	SetTextColor(color_);
	font->Set_Size(desktop->row_height / 2.2);
	font->TextMid(
		bufWeek,
		RectClient.left + RectClient.width / 2,
		RectClient.top - desktop->row_height - desktop->row_height * 3 / 4);
}

void WgCalendar::render()
{
	WgBackground::render();

	switch (widget_mode_)
	{
		case md1x1:
		{
			RenderMode1_();
			break;
		}
		case md1x2:
		{
			RenderMode1_();
			RenderMode2_();
			break;
		}
		case md1x3:
		{
			RenderMode1_();
			RenderMode2_();
			RenderMode3_();
			break;
		}
		case md3x8:
		{
			//probably need to cut it all
			break;
		}
		case mdCustom:{
			//probably need to cut it all
			break;
		}
	}
}
