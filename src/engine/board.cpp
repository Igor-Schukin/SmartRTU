#include "board.h"

#include "desktop.h"/*desktop obj*/

#include "CPicturesStorage.h"/*picstorage obj*/

#include "Timer.h"/*strnow*/

/*OpenVG stuff like VgInit*/
extern "C"
{
#include "VG/openvg.h"
#include "VG/vgu.h"
#include "fontinfo.h"
#include "shapes.h"
}

//widgets

#include "WgBackground.h"//testing 

#include "WgClock.h"
#include "WgCalendar.h"
#include "WgForecast.h"
//#include "WgAds.h"
#include "WgSockets.h"
#include "WgTimetable.h"
#include "WgWatchdog.h"

#include "../widgets/WgHtmlAds.h"  

//#define MAX_WIDGETS 50
constexpr int MAX_WIDGETS = 50;

Board::Board()
{
	widgets = nullptr;
	current = nullptr;

	//AddWidget(new WgAds(0, 8, md3x8)); // 1, 8
	//this parts couses 26 line in engine CMakeList
	AddWidget(
		new WgHtmlAds(0, 8,md3x8)
		);
	 //m_AddWidget( widgets, new WgHtmlAds(0, 8, md3x8));

	AddWidget(new WgForecast(3, 8, md1x2));
	AddWidget(new WgClock(3, 6, md1x3));
	AddWidget(new WgCalendar(3, 3, md1x3));
	AddWidget(new WgSockets());
	AddWidget(new WgTimetable());
	AddWidget(new WgWatchdog());
}


Board::~Board()
{
	CleanWidgets();
}

void Board::update(bool Forced)
{
	LongTimeMs time = timer.GetTime();
	for (WidgetInfo *w = widgets; w; w = w->next)
	{
		int uprd = static_cast<int>(w->widget->Get_widget_update_time());
		if (Forced || ((uprd > 0) && ((time - w->lastUpdate) > static_cast<long long unsigned int>(uprd))))
		{
			
			w->needRender = w->widget->update();
			w->lastUpdate = time;
		}
	}
}

void Board::render(bool Forced)
{
	VGint screenRect[4] = {0, 0, desktop->screen_width, desktop->screen_height};
	VGint clipRects[MAX_WIDGETS * 4]; // (left, bottom, width, height) x count
	int count = 0, wx, wy, ww, wh;
	for (WidgetInfo *w = widgets; w; w = w->next)
		if ((w->needRender || Forced) && w->widget->IsVisible())
		{
			if (!w->widget->IsTransparent())
			{
				continue;
			}
			w->widget->GetRect(wx, wy, ww, wh);
			clipRects[count * 4 + 0] = (VGint)wx;
			clipRects[count * 4 + 1] = (VGint)wy;
			clipRects[count * 4 + 2] = (VGint)ww;
			clipRects[count * 4 + 3] = (VGint)wh;
			count++;
		}

	vgSeti(VG_SCISSORING, VG_TRUE);

	if (Forced || (count != 0))
	{
		if (Forced){
			vgSetiv(VG_SCISSOR_RECTS, 4, screenRect);
		}
		else{
			vgSetiv(VG_SCISSOR_RECTS, count * 4, clipRects);
		}

		float sbx = (float)desktop->screen_width / PicStorage->ScreenBackgroud->Get_width();
		float sby = (float)desktop->screen_height / PicStorage->ScreenBackgroud->Get_height();
		PicStorage->ScreenBackgroud->render(0, 0, sbx, sby, 0, 0, 0);

		float logo_scale = 0.9;
		Picture *logo = PicStorage->Logo;
		int h = desktop->screen_height - desktop->DwRect.top;
		int x = desktop->DwRect.left;
		int y = desktop->DwRect.top + h * (1 - logo_scale) / 2;
		float sc = (float)h / logo->Get_height() * logo_scale;
		logo->render(x, y, sc, sc, 0, 0, 0);
	}

	
	for (WidgetInfo *w = widgets; w; w = w->next)
		if ((w->needRender || Forced) && (w->widget->IsVisible()))
		{
			// vgSetiv(VG_SCISSOR_RECTS, 4, clipRects + i++ * 4);

			w->widget->GetRect(wx, wy, ww, wh);
			clipRects[0] = (VGint)wx;
			clipRects[1] = (VGint)wy;
			clipRects[2] = (VGint)ww;
			clipRects[3] = (VGint)wh;
			vgSetiv(VG_SCISSOR_RECTS, 4, clipRects);

			w->widget->render();
			w->needRender = false;
		}

	vgSeti(VG_SCISSORING, VG_FALSE);
}

void Board::m_AddWidget(WidgetInfo* & list, IWidget * w) {
    if (list){ 
		m_AddWidget(list->next, w);
	} 
	else{ 
		list = new WidgetInfo(w);
	}
}

void Board::m_FreeWidgets(WidgetInfo* & list) {
    if (list) {
		 m_FreeWidgets(list->next); 
		 delete(list); 
		 list = nullptr; 
	}
}

int Board::m_CntWidgets(WidgetInfo* list) {
    if (list){
		 return m_CntWidgets(list->next) + 1;
	} 
	else{
		 return 0;
	}
}

IWidget *Board::FindNext() {
    if ( current ){ 
		current = current->next;
	} 
	return current ? current->widget : nullptr;
}

IWidget *Board::FindFirst() {
     	current = widgets;
		return current ? current->widget : nullptr; 
}
