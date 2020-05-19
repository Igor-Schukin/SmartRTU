
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

#include "config.h" //legacy config what soon will be removed
#include "configurator.h" //configurator

//DEBUG PURPOSE UNCOMMENT NEEDED STUF AND RECOMPILE WIDGET
//TODO: debug stuff must be on/off in config . do not need to recompile project

//about threads what are curently working//dumps into console message about they status
//#define DEBUG_THREAD_MSG
//to get all data(width,height,scale,widget where will be rendered area) about advert
//#define DEBUG_ADVERTS_PRM_SHOW 




//STYLE
//avoid "using namespace " keep clean project from namespacing chaos 
// variables_in_lower_snake_style // *
//except geters and setters they starts with lower get or set word like so -> getSmile(); setX() etc  //sporno *
//private methods/variables have prefix "m_"
//methods style is lower first word othres starts with Upercase latter like so MyClass->mySmoothMethod(); //sporno * //maybe all uper? MyClass->MySmoothMethod
//if method only have one word then it in loawercase like so MyClass->method(); //sporno *

//* PROBABLY NEED TO GO FULL ON INTO PYTHON STYLE

//class struct{
    //public part first
        //methods
        //constructors
    //private part last
        //methods
        //variables
//};


class WgHtmlAds : public WgBackground
{
public:
    bool update();//check if need update widget
    void render();//renders advert into screen

    WgHtmlAds(int Ax, int Ay, wgMode Amode);
    ~WgHtmlAds();

private:
    void m_cutyCaptRequest();//run in another thread combining strings to make request and transform .html page into png
   
   //~~detect if advert.html file was changed
    time_t m_getFileTime();//gets last edited time of file(.html) 
	bool m_needRenew();//check if file(.html) was changed/edited 

    //~~~stored strings
    std::string m_header_text;//stores header text
    std::string m_full_path_to_exe;//stores full path to exe//need to change name to more understandable

    Picture *m_advert_pic;//Pointer where image will be stored
    time_t m_file_time=0;//last timestamp then file was edited 
    float m_scale_by_x=0;//width Scale of image to fit into widget                                             
    float m_scale_by_y=0;//height Scale of image to fit into widget
    
    //~thread variables
    std::future<void>m_future;//is handle of  new async thread 
    std::future_status m_status; // stored status of thread //probably can avoid it
   
    bool m_is_advert_on_screen; // IsAdvertOnScreen flag
    bool m_stub_displayed_once;//to make stub appier once at the start of program //stub from english is zaglushka
};

#endif /*WGHTMLADS_H*/