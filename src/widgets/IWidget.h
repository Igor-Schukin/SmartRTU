#pragma once
#ifndef SMART_RTU_SRC_WIDGETS_IWIDGET_H_
#define SMART_RTU_SRC_WIDGETS_IWIDGET_H_


class IWidget
{

protected:
	int m_widget_update_time;
	int m_widget_id;

public:
	virtual ~IWidget() {};
	virtual bool update() = 0; // true if need rerendering
	virtual void render() = 0;

	
	//	x,y->lower left  corner of widget
	virtual void GetRect(
		int &x, int &y, int &widget_width, int &widget_height) = 0; 			
	
	virtual void Set_widget_id(int m_widget_id) { this->m_widget_id = m_widget_id; }						
	virtual int Get_widget_update_time() { return this->m_widget_update_time; } 			
	virtual int Get_width() { return 0; }  // for custom mode 			
	virtual int Get_height() { return 0; } // for custom mode 			
	virtual bool IsVisible() { return true; };  				
	virtual bool IsTransparent() { return false; };						
};

#endif /*SMART_RTU_SRC_WIDGETS_IWIDGET_H_*/