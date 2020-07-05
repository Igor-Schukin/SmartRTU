#pragma once
#ifndef SMART_RTU_SRC_WIDGETS_IWIDGET_H_
#define SMART_RTU_SRC_WIDGETS_IWIDGET_H_


class IWidget
{

protected:
	int m_widget_update_time;
	int m_widget_id;

public:
	virtual ~IWidget() {}
	virtual bool update() = 0; // true if need rerendering
	virtual void render() = 0;

	
	//	x,y->lower left  corner of widget
	virtual void GetRect(
		int &x, int &y, int &widget_width, int &widget_height) = 0; 			//GetRect+
	
	virtual void Set_widget_id(int m_widget_id) { this->m_widget_id = m_widget_id; }						//Set_widget_id+
	virtual int Get_widget_update_time() { return this->m_widget_update_time; } 			//Get_widget_update_time+
	virtual int Get_width() { return 0; }  // for custom mode 			//Get_width+
	virtual int Get_height() { return 0; } // for custom mode 			//Get_height+
	virtual bool IsVisible() { return true; }; //isVisible 				//isVisible +
	virtual bool IsTransparent() { return false; };						//isTransparent 
};

#endif /*SMART_RTU_SRC_WIDGETS_IWIDGET_H_*/