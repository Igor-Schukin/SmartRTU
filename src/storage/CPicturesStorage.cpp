#include "iostream"
#include "CPicturesStorage.h"

#include "configurator.h"
using namespace std; // brr

CPicturesStorage *PicStorage;

CPicturesStorage::CPicturesStorage()
{
	//adds needed paths
	config->Get("PIC_SHADOW_PATH",m_shadows_path);
	config->Get("PIC_PATH",m_pictures_path);
	config->Get("PIC_BACKGROUND",m_background_pic_name);
	config->Get("PIC_TITLE",m_title_pic_name);


	this->addPic();
	//arialBold = new TFont("lib/TFont/ArialBold.ttf");
}

CPicturesStorage::~CPicturesStorage()
{
	this->cleanStorage();
}

void CPicturesStorage::addPic()
{
	Logo = new Picture((m_pictures_path+"/"+m_title_pic_name).c_str());
	ScreenBackgroud = new Picture((m_pictures_path+"/"+m_background_pic_name).c_str());
	Arrow = new Picture((m_pictures_path+"/"+"arrow_sm.png").c_str());
	WgShadows = new wgShadowPictures;
	WgShadows->t = new Picture((m_shadows_path+"/"+"sTop.png").c_str());
	WgShadows->lt = new Picture((m_shadows_path+"/"+"sLeftTop.png").c_str());
	WgShadows->rt = new Picture((m_shadows_path+"/"+"sRightTop.png").c_str());
	WgShadows->b = new Picture((m_shadows_path+"/"+"sBot.png").c_str());
	WgShadows->lb = new Picture((m_shadows_path+"/"+"sLeftBot.png").c_str());
	WgShadows->rb = new Picture((m_shadows_path+"/"+"sRightBot.png").c_str());
	WgShadows->l = new Picture((m_shadows_path+"/"+"sLeft.png").c_str());
	WgShadows->r = new Picture((m_shadows_path+"/"+"sRight.png").c_str());
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
