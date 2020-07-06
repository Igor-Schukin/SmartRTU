#include "board.h"
#include "CPicturesStorage.h"

#include "WgClock.h"
#include "WgCalendar.h"
#include "WgForecast.h"
//#include "WgAds.h"
#include "WgSockets.h"
#include "WgTimetable.h"
#include "WgWatchdog.h"
#include "desktop.h"

#include "WgHtmlAds.h"

//#define MAX_WIDGETS 50
constexpr int MAX_WIDGETS = 50;

Board::Board()
{
	widgets = nullptr;
	current = nullptr;

	//addWidget(new WgAds(0, 8, md3x8)); // 1, 8

	addWidget(new WgHtmlAds(0, 8, md3x8));

	addWidget(new WgForecast(3, 8, md1x2));
	addWidget(new WgClock(3, 6, md1x3));
	addWidget(new WgCalendar(3, 3, md1x3));
	addWidget(new WgSockets);
	addWidget(new WgTimetable);
	addWidget(new WgWatchdog);
}

Board::~Board()
{
	cleanWidgets();
}

void Board::update(bool Forced)
{
	LongTimeMs time = timer.GetTime();
	for (WidgetInfo *w = widgets; w; w = w->next)
	{
		int uprd = (int)w->widget->Get_widget_update_time();
		if (Forced || ((uprd > 0) && ((time - w->lastUpdate) > static_cast<long long unsigned int>(uprd))))
		{
			
			w->needRender = w->widget->update();
			w->lastUpdate = time;
		}
	}
}

void Board::render(bool Forced)
{
	VGint screenRect[4] = {0, 0, desktop->scrWidth, desktop->scrHeight};
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

		float sbx = (float)desktop->scrWidth / PicStorage->ScreenBackgroud->Get_width();
		float sby = (float)desktop->scrHeight / PicStorage->ScreenBackgroud->Get_height();
		PicStorage->ScreenBackgroud->render(0, 0, sbx, sby, 0, 0, 0);

		float logo_scale = 0.9;
		Picture *logo = PicStorage->Logo;
		int h = desktop->scrHeight - desktop->dwRect.top;
		int x = desktop->dwRect.left;
		int y = desktop->dwRect.top + h * (1 - logo_scale) / 2;
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
