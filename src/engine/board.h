#pragma once

#include "IWidget.h"/*interface*/
#include "Timer.h"/*LongTimeMs*/

struct WidgetInfo {
	IWidget * widget;
	LongTimeMs lastUpdate;
	bool needRender;
	WidgetInfo * next;
	WidgetInfo(IWidget * w) { widget = w; next = nullptr;  lastUpdate = 0; needRender = true; }
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
	
	IWidget *FindFirst() { 	current = widgets;	return current ? current->widget : nullptr; }
	IWidget *FindNext() { if ( current ) current = current->next; return current ? current->widget : nullptr; }
	WidgetInfo * CurrentWidget() { return current; }
	
	int CountWidgets() { return m_CntWidgets( widgets ); }

private:

	WidgetInfo *widgets, *current;
	//m_AddWidget
	void m_AddWidget(WidgetInfo* & list, IWidget * w) { if (list) m_AddWidget(list->next, w); else list = new WidgetInfo(w); }
	void m_FreeWidgets(WidgetInfo* & list) { if (list) { m_FreeWidgets(list->next); delete(list); list = nullptr; } }
	
	int m_CntWidgets(WidgetInfo* list) { if (list) return m_CntWidgets(list->next) + 1; return 0; }
	
	
};
