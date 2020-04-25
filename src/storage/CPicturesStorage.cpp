#include "iostream"
#include "CPicturesStorage.h"

#include "config.h"

using namespace std;

CPicturesStorage *PicStorage;

CPicturesStorage::CPicturesStorage()
{
	this->addPic();
	//arialBold = new TFont("lib/TFont/ArialBold.ttf");
}

CPicturesStorage::~CPicturesStorage()
{
	this->cleanStorage();
}

void CPicturesStorage::addPic()
{
	Logo = new Picture(PIC_PATH("title.png"));
	ScreenBackgroud = new Picture(PIC_PATH("Background.jpg"));
	Arrow = new Picture(PIC_PATH("arrow_sm.png"));
	WgShadows = new wgShadowPictures;
	WgShadows->t = new Picture(SHADOW_PATH("sTop.png"));
	WgShadows->lt = new Picture(SHADOW_PATH("sLeftTop.png"));
	WgShadows->rt = new Picture(SHADOW_PATH("sRightTop.png"));
	WgShadows->b = new Picture(SHADOW_PATH("sBot.png"));
	WgShadows->lb = new Picture(SHADOW_PATH("sLeftBot.png"));
	WgShadows->rb = new Picture(SHADOW_PATH("sRightBot.png"));
	WgShadows->l = new Picture(SHADOW_PATH("sLeft.png"));
	WgShadows->r = new Picture(SHADOW_PATH("sRight.png"));
}

void CPicturesStorage::cleanStorage()
{
	delete ScreenBackgroud;
	delete WgShadows->t;
	delete WgShadows->b;
	delete WgShadows->l;
	delete WgShadows->r;
	delete WgShadows->lt;
	delete WgShadows->rb;
	delete WgShadows->lb;
	delete WgShadows->rt;
	delete WgShadows;
	delete Logo;
	delete Arrow;
}
