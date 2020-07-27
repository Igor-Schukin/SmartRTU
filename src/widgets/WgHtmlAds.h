
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
  void CutyCaptRequest_(); // run in another thread combining strings to make
                            // request and transform 
                            //.html page into png using Cutycapt

  //~~detect if advert.html file was changed
  std::time_t GetFileTime_(); // gets last edited time of file(.html)
  bool NeedRenew_();          // check if file(.html) was changed/edited
  void CleanPicture_(); // cleans what inside advert_pic_ and sets nullptr
  
  //~~~stored strings
  std::string header_text_; 
  std::string local_html_input_file_dest_;
  std::string html_name_;
  std::string local_ad_path_;
  std::string ad_name_;
  std::string stub_name_;
  std::string local_stub_path_;
  std::string full_path_to_project_exe_; // cutycapt need full path to exe
                                          // otherwise it wont work

  Picture *advert_pic_;       
  std::time_t file_time_ = 0; // last timestamp then file was edited

  float image_scale_by_width_ = 0;
  float image_scale_by_height_ = 0;

  //~thread variables
  std::future<void> cutycapt_thread_; // is obj of  new async thread //not so good to
                              // use void but....
                              
  // stored status of thread //probably can avoid it
  std::future_status thread_status_; 

  bool advert_on_screen_;
};

#endif /*SMART_RTU_SRC_WIDGETS_WGHTMLADS_H_*/