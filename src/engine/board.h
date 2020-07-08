#pragma once

#include "IWidget.h"/*interface*/
#include "Timer.h"/*LongTimeMs*/
#include "../widgets/WgHtmlAds.h"  //still not working


struct WidgetInfo {
	IWidget * widget;
	LongTimeMs lastUpdate;
	bool needRender;
	WidgetInfo * next;
	WidgetInfo(IWidget * w) { 
		widget = w; next = nullptr;  
		lastUpdate = 0; needRender = true; 
		}
	~WidgetInfo() { delete widget; }
};

class Board
{
public:	

	Board();
	~Board();
	void update(bool Forced);
	void render(bool Forced);
	void CleanWidgets() { m_FreeWidgets( widgets ); }
	void AddWidget(IWidget *widget) { m_AddWidget( widgets, widget ); }
	
	IWidget *FindFirst(); 
	IWidget *FindNext();
	WidgetInfo * CurrentWidget() { return current; }
	
	int CountWidgets() { return m_CntWidgets( widgets ); }

private:

	WidgetInfo *widgets, *current;
	//m_AddWidget
	void m_AddWidget(WidgetInfo* & list, IWidget * w); 
	void m_FreeWidgets(WidgetInfo* & list);
	
	int m_CntWidgets(WidgetInfo* list); 
	
	
};
