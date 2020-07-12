#pragma once
#ifndef SMART_RTU_SRC_WIDGETS_IWIDGET_H_
#define SMART_RTU_SRC_WIDGETS_IWIDGET_H_


class IWidget
{

protected:
	int widget_update_time_;
	int widget_id_;

public:
	virtual ~IWidget() {};
	virtual bool update() = 0; // true if need rerendering
	virtual void render() = 0;

	
	//	x,y->lower left  corner of widget
	virtual void GetRect(
		int &x, int &y, int &widget_width, int &widget_height) = 0; 			
	
	virtual void Set_widget_id(int widget_id_) { this->widget_id_ = widget_id_; }						
	virtual int Get_widget_update_time() { return this->widget_update_time_; } 			
	virtual int Get_width() { return 0; }  // for custom mode 			
	virtual int Get_height() { return 0; } // for custom mode 			
	virtual bool IsVisible() { return true; };  				
	virtual bool IsTransparent() { return false; };						
};

#endif /*SMART_RTU_SRC_WIDGETS_IWIDGET_H_*/