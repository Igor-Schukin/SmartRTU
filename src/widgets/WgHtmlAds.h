
#pragma once
#ifndef WGHTMLADS_H
#define WGHTMLADS_H

#include <iostream>
#include <string>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>

#include<thread> //thread stuff
#include<future>//thread stuff
#include <chrono> /*for milisecons */

//~ realPath funtion is in stdlib but PATH_MAX in limits.h
#include <limits.h> /* PATH_MAX */
#include <cstdio>
#include <cstdlib>

//our stuff
#include "WgBackground.h"
#include "Engine.h"// from here we need only fmt stuff
//#include "desktop.h" //well i commented this and all is still working
#include "Timer.h"
#include "CPicturesStorage.h"
#include "CFontStorage.h"

#include "config.h"
//probably legacy crap
#define FLAG_FILE_NAME "flag"
 
class WgHtmlAds : public WgBackground
{
public:

    WgHtmlAds(int Ax, int Ay, wgMode Amode);
    ~WgHtmlAds();
    bool update();
    void render();

private:

    void cutyCaptRequest();//run in another thread combining strings to make request and transform .html page into png
   
   //~~detect if advert.html file was changed
   //Do not understand FLAG purpose
    time_t getFileTime();
	bool renewFlag();
	bool needRenew();
	//bool readFile(char *&text);

    Picture *m_HtmlPic=NULL;//Pointer where image will be stored
    time_t fileTime=0;//last timestamp then file was edited
    char *m_OutputFilePath=NULL;//full path + image name of output 
    float m_ScaleByX=0;//width Scale of image to fit into widget
    float m_ScaleByY=0;//height Scale of image to fit into widget
    //~thread variables
    std::future<void>future;//is handle of  new async thread 
    std::future_status status; // stored status of thread //probably can avoid it
   
    bool m_alreadyUploadedPic=true; // Call Dainis to explain why I am exist
};

#endif /*WGHTMLADS_H*/