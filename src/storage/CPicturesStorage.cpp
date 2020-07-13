
#include "CPicturesStorage.h"
#include<string>

#include "configurator.h"


CPicturesStorage *PicStorage;

CPicturesStorage::CPicturesStorage()
{
	//adds needed paths
	config->Get("PIC_SHADOW_PATH",shadows_path_);
	config->Get("PIC_PATH",pictures_path_);
	config->Get("PIC_BACKGROUND",background_picture_name_);
	config->Get("PIC_TITLE",title_picture_name_);


	this->CreatPictures_();
}

CPicturesStorage::~CPicturesStorage()
{
	this->CleanStorage_();
}

void CPicturesStorage::CreatPictures_()
{
	Logo = new Picture((pictures_path_+"/"+title_picture_name_).c_str());
	
	ScreenBackgroud = new Picture(
		(pictures_path_+"/"+background_picture_name_).c_str()
	);
	Arrow = new Picture((pictures_path_+"/"+"arrow_sm.png").c_str());
	
	WgShadows = new WgShadowPictures;
	WgShadows->t = new Picture((shadows_path_+"/"+"sTop.png").c_str());
	WgShadows->lt = new Picture((shadows_path_+"/"+"sLeftTop.png").c_str());
	WgShadows->rt = new Picture((shadows_path_+"/"+"sRightTop.png").c_str());
	WgShadows->b = new Picture((shadows_path_+"/"+"sBot.png").c_str());
	WgShadows->lb = new Picture((shadows_path_+"/"+"sLeftBot.png").c_str());
	WgShadows->rb = new Picture((shadows_path_+"/"+"sRightBot.png").c_str());
	WgShadows->l = new Picture((shadows_path_+"/"+"sLeft.png").c_str());
	WgShadows->r = new Picture((shadows_path_+"/"+"sRight.png").c_str());
}

void CPicturesStorage::CleanStorage_()
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
