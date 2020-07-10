/*CPicturesStorage
 * --This is a Picture Storage
 * 		You can add here pictures and
 * 		and use it anywhere in project,
 * 		just add #include "CPicturesStorage.h"
 * --Here uses library Picture.h frow Denisovs Maksims 
 */
#pragma once
#include "Picture.h"
#include<string>
//#include "./lib/TFont/TFont.h"

struct wgShadowPictures
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

	std::string m_shadows_path;
	std::string m_pictures_path;
	std::string m_background_pic_name;
	std::string m_title_pic_name;

	//TFont *arialBold;
	Picture *ScreenBackgroud;
	Picture *Logo;
	Picture *Arrow;
	wgShadowPictures *WgShadows;
private:
	void m_AddPic();
	void m_CleanStorage();


};

extern CPicturesStorage *PicStorage;
