#pragma once

class IWidget
{

protected:
	int updateTime;
	int id;

public:
	virtual ~IWidget() {}
	virtual bool update() = 0; // true if need rerendering
	virtual void render() = 0;
	virtual void getRect(int &x, int &y, int &w, int &h) = 0; 			//getRect
	virtual void setId(int id) { this->id = id; }						//setId
	virtual int getUpdateTime() { return this->updateTime; } 			//getUpdateTime
	virtual int getWidth() { return 0; }  // for custom mode 			//getWidth
	virtual int getHeight() { return 0; } // for custom mode 			//getHeight
	virtual bool IsVisible() { return true; }; //isVisible 				//isVisible +
	virtual bool IsTransparent() { return false; };						//isTransparent 
};
