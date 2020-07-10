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
	m_widget_update_time = 60 * 60 * 1000; // 1 hour
	strcpy(bufDate, "- -");
	strcpy(bufWeekDay, "-");
	strcpy(bufWeekInfo, "- - -");
	strcpy(bufWeek, "-");
	config->Get("BASE_FONT_NAME",m_base_font_name); 
	std::cout<<StrNow()<<"\tWgCalendar widget object was created\n";
}

WgCalendar::~WgCalendar()
{
	fprintf(stdout,"%s\tWgCalendar widget object was deleted\n", StrNow());
}

const char *WgCalendar::m_ConvertWeekDayFromInt(int wday)
{
	switch (wday)
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

const char *WgCalendar::m_ConvertMonthFromInt(int mon)
{
	switch (mon)
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
	std::time_t lt = time(nullptr);
	struct tm *now = localtime(&lt);

	sprintf(bufDate, "%i.%s", now->tm_mday, m_ConvertMonthFromInt(now->tm_mon));

	sprintf(bufWeekDay, "%s", m_ConvertWeekDayFromInt(now->tm_wday));

	int week = 0;
	switch (timetable->GetCurrentDateState(week))
	{
	case dsSemester:
		strcpy(bufWeekInfo, "nedēļa semestrī");
		break;
	case dsSession:
		strcpy(bufWeekInfo, "sesijas nedēļa");
		break;
	case dsVacation:
		strcpy(bufWeekInfo, "brīvlaika nedēļa");
		break;
	case dsHoliday:
		strcpy(bufWeekInfo, "svētki");
		break;
	case dsUnknown:
		strcpy(bufWeekInfo, "Nezinams");
		break;
	default:
		strcpy(bufWeekInfo, "...");
		break;
	}
	week += 1;

	if (week >= 1)
		sprintf(bufWeek, "%d.", week);
	else
		strcpy(bufWeek, "--");

	return true;
}

void WgCalendar::m_RenderMode1()
{
	RenderWidgetHeader(bufDate);
}

void WgCalendar::m_RenderMode2()
{
	TFont *font = FontStorage->GetFont(
		const_cast<char*>(m_base_font_name.c_str())
		);
	SetTextColor(clHaki);
	font->Set_Size(desktop->row_height / 3);
	font->TextMid(
		bufWeekDay,
		RectClient.left + RectClient.width / 2,
		RectClient.top - desktop->row_height / 16 * 11);
}

void WgCalendar::m_RenderMode3()
{
	TFont *font = FontStorage->GetFont(
		const_cast<char*>(m_base_font_name.c_str())
		);
	font->Set_Size(desktop->row_height / 4.5);
	font->TextMid(
		bufWeekInfo,
		RectClient.left + RectClient.width / 2,
		RectClient.top - desktop->row_height - desktop->row_height / 5 / 2);

	SetTextColor(m_color);
	font->Set_Size(desktop->row_height / 2.2);
	font->TextMid(
		bufWeek,
		RectClient.left + RectClient.width / 2,
		RectClient.top - desktop->row_height - desktop->row_height * 3 / 4);
}

void WgCalendar::render()
{
	WgBackground::render();

	switch (m_widget_mode)
	{
		case md1x1:
		{
			m_RenderMode1();
			break;
		}
		case md1x2:
		{
			m_RenderMode1();
			m_RenderMode2();
			break;
		}
		case md1x3:
		{
			m_RenderMode1();
			m_RenderMode2();
			m_RenderMode3();
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
