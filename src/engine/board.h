#pragma once
#ifndef SMART_RTU_SRC_ENGINE_BOARD_H_
#define SMART_RTU_SRC_ENGINE_BOARD_H_


#include "IWidget.h"/*interface*/
#include "Timer.h"/*LongTimeMs*/
#include "../widgets/WgHtmlAds.h"  //still not working


struct WidgetInfo {
	IWidget * widget;
	LongTimeMs lastUpdate;
	bool needRender;
	WidgetInfo * next;
	WidgetInfo(IWidget * w) { 
		widget = w;
		next = nullptr;  
		lastUpdate = 0;
		needRender = true; 
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
	void CleanWidgets() { FreeWidgets_( widgets ); }
	void AddWidget(IWidget *widget) { AddWidget_( widgets, widget ); }
	
	IWidget *FindFirst(); 
	IWidget *FindNext();
	WidgetInfo * CurrentWidget() { return current; }
	
	int CountWidgets() { return CntWidgets_( widgets ); }

private:

	WidgetInfo *widgets, *current;

	void AddWidget_(WidgetInfo* & list, IWidget * w); 
	void FreeWidgets_(WidgetInfo* & list);
	
	int CntWidgets_(WidgetInfo* list); 
	
	
};

#endif/*SMART_RTU_SRC_ENGINE_BOARD_H_*/