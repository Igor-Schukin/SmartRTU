
#pragma once
#ifndef WGHTMLADS_H
#define WGHTMLADS_H

#include <iostream>
#include <string>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>

#include<string>//stored strings probably need to go into char pointers

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

class WgHtmlAds : public WgBackground
{
public:

    WgHtmlAds(int Ax, int Ay, wgMode Amode);
    ~WgHtmlAds();
    bool update();//check if need update widget
    void render();//renders advert into screen

private:

    //~~~stored strings
    std::string m_HeaderText;//stores header text
    std::string m_FullPath;//stores full path to exe

    void cutyCaptRequest();//run in another thread combining strings to make request and transform .html page into png
   
   //~~detect if advert.html file was changed
    time_t getFileTime();//gets last edited time of .html
	bool needRenew();//check if .html was changed/edited

    Picture *m_HtmlPic=NULL;//Pointer where image will be stored
    time_t fileTime=0;//last timestamp then file was edited
    float m_ScaleByX=0;//width Scale of image to fit into widget
    float m_ScaleByY=0;//height Scale of image to fit into widget
    
    //~thread variables
    std::future<void>m_Future;//is handle of  new async thread 
    std::future_status m_Status; // stored status of thread //probably can avoid it
   
    bool m_IsAdvertOnScreen=false; // 
    bool m_StubDisplayedOnce=false;//to make stub appier once at the start of program //stub from english is zaglushka
};

#endif /*WGHTMLADS_H*/