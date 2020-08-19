/*CPicturesStorage
 * --This is a Picture Storage
 * 		You can add here pictures and
 * 		and use it anywhere in project,
 * 		just add #include "CPicturesStorage.h"
 * --Here uses library Picture.h frow Denisovs Maksims 
 */
#pragma once
#ifndef SMART_RTU_SRC_STORAGE_CPICTURES_STORAGE_H_
#define SMART_RTU_SRC_STORAGE_CPICTURES_STORAGE_H_

#include<string>

#include "Picture.h"//Picture class



struct WgShadowPictures
{
	Picture *t;
	Picture *b;
	Picture *l;
	Picture *r;
	Picture *lt;
	Picture *lb;
	Picture *rb;
	Picture *rt;
};

class CPicturesStorage
{
public:
	CPicturesStorage();
	~CPicturesStorage();

	Picture *ScreenBackgroud;
	Picture *Logo;
	Picture *Arrow;
	WgShadowPictures *WgShadows;
private:
	void CreatPictures_();
	void CleanStorage_();

	std::string shadows_path_; //path to where shadows are stored
	std::string pictures_path_;// path to where pictures are stored
	std::string background_picture_name_;
	std::string title_picture_name_;


};

extern CPicturesStorage *PicStorage;

#endif /*SMART_RTU_SRC_STORAGE_CPICTURES_STORAGE_H_*/