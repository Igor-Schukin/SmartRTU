
#pragma once
#ifndef SMART_RTU_SRC_WIDGETS_WGHTMLADS_H_
#define SMART_RTU_SRC_WIDGETS_WGHTMLADS_H_

/*
// MAIN PURPOSE TO ASYNC WAY TO CONVERT HTML PAGE INTO PIC/ADVERT
// SHOW IT ON THE WIDGET SCREEN
// DETECT IF .HTML PAGE WAS EDITED ASYNC WAY CONVERT IT TO ADVERT AND REPLACE NEW ADVERT WITH NEW ONE
//
// btw example of new code style of project
//
//
*/


//C (more precisely: headers in angle brackets with the .h extension), e.g. <unistd.h>, <stdlib.h>


//C++
#include <string>
#include<thread> //thread stuff
#include<future>//thread stuff
#include<ctime>// for time_t type
//a11y libs

//my headers
#include "WgBackground.h" //inheritance
#include "CPicturesStorage.h" //for Picture type



//DEBUG PURPOSE UNCOMMENT NEEDED STUF AND RECOMPILE WIDGET

/*about threads what are curently working//dumps into console message about they status*/
//#define DEBUG_THREAD_MSG

/*to get all data(width,height,scale,widget where will be rendered area) about advert*/
//#define DEBUG_ADVERTS_PRM_SHOW 



class WgHtmlAds : public WgBackground
{
public:
	bool update();//check if need update widget
	void render();//renders advert into screen

	WgHtmlAds(int Ax, int Ay, wgMode Amode);
	~WgHtmlAds();

private:
	void m_CutyCaptRequest();//run in another thread combining strings to make request and transform .html page into png

   //~~detect if advert.html file was changed
	std::time_t m_GetFileTime();//gets last edited time of file(.html) 
	bool m_NeedRenew();//check if file(.html) was changed/edited 

	//~~~stored strings
	std::string m_header_text;//stores header text

	std::string m_local_html_input_file_dest;
	std::string m_html_name;
	std::string m_local_ad_path;
	std::string m_ad_name;
	std::string m_stub_name;
	std::string m_local_stub_path;

	std::string m_full_path_to_project_exe; //cutycapt need full path to exe otherwise it wont work

	Picture *m_advert_pic;//Pointer where image will be stored
	std::time_t m_file_time = 0;//last timestamp then file was edited 

	float m_image_scale_by_width = 0;
	float m_image_scale_by_height = 0;

	//~thread variables
	std::future<void>m_future;//is handle of  new async thread //not so good to use void but....
	std::future_status m_thread_status; // stored status of thread //probably can avoid it

	bool m_is_advert_on_screen; // purpose: 1. what Picture obj will not be killed and created itch time in render
										  //2.signal what need rerender advert in update() // if is false mean what new advert must be rerendered otherwise its ok
										  //3.signal what something(advert or stub is on the screen)
	bool m_stub_displayed_once;//to make stub appier once at the start of program //stub from english is zaglushka
};

#endif /*SMART_RTU_SRC_WIDGETS_WGHTMLADS_H_*/