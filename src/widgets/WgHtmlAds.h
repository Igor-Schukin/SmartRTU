
#pragma once
#ifndef SMART_RTU_SRC_WIDGETS_WGHTMLADS_H_
#define SMART_RTU_SRC_WIDGETS_WGHTMLADS_H_

/*
Restyled by RazdolbayOne
*/

/*
// MAIN PURPOSE TO ASYNC WAY TO CONVERT HTML PAGE INTO PIC/ADVERT
// SHOW IT ON THE WIDGET SCREEN
// DETECT IF .HTML PAGE WAS EDITED ASYNC WAY CONVERT IT TO ADVERT AND REPLACE
NEW ADVERT WITH NEW ONE
//
// btw example of new code style of project
//
//
*/

// C (more precisely: headers in angle brackets with the .h extension), e.g.
// <unistd.h>, <stdlib.h>

// C++
#include <ctime>  // for time_t type
#include <future> //thread stuff
#include <string>
#include <thread> //thread stuff
// a11y libs

// my headers
#include "CPicturesStorage.h" //for Picture type
#include "WgBackground.h"     //inheritance

// DEBUG PURPOSE UNCOMMENT NEEDED STUF AND RECOMPILE WIDGET

/*about threads what are curently working//dumps into console message about they
 * status*/
//#define DEBUG_THREAD_MSG

/*to get all data(width,height,scale,widget where will be rendered area) about
 * advert*/
//#define DEBUG_ADVERTS_PRM_SHOW

class WgHtmlAds 
: public WgBackground 
{
public:
  bool update() override; // check if need update widget
  void render() override; // renders advert into screen

  WgHtmlAds(int Ax, int Ay, WgMode Amode);
  ~WgHtmlAds();

private:
  void m_CutyCaptRequest(); // run in another thread combining strings to make
                            // request and transform .html page into png

  //~~detect if advert.html file was changed
  std::time_t m_GetFileTime(); // gets last edited time of file(.html)
  bool m_NeedRenew();          // check if file(.html) was changed/edited
  void m_CleanPicture(); // cleans what inside m_advert_pic and sets nullptr
  
  //~~~stored strings
  std::string m_header_text; 
  std::string m_local_html_input_file_dest;
  std::string m_html_name;
  std::string m_local_ad_path;
  std::string m_ad_name;
  std::string m_stub_name;
  std::string m_local_stub_path;
  std::string m_full_path_to_project_exe; // cutycapt need full path to exe
                                          // otherwise it wont work

  Picture *m_advert_pic;       
  std::time_t m_file_time = 0; // last timestamp then file was edited

  float m_image_scale_by_width = 0;
  float m_image_scale_by_height = 0;

  //~thread variables
  std::future<void> m_future; // is handle of  new async thread //not so good to
                              // use void but....
                              
  // stored status of thread //probably can avoid it
  std::future_status m_thread_status; 

  bool m_advert_on_screen;
};

#endif /*SMART_RTU_SRC_WIDGETS_WGHTMLADS_H_*/