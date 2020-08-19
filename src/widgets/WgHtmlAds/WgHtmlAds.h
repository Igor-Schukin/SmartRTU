
#pragma once
#ifndef SMART_RTU_SRC_WIDGETS_WGHTMLADS_WGHTMLADS_H_
#define SMART_RTU_SRC_WIDGETS_WGHTMLADS_WGHTMLADS_H_

/*
//Author:Dainis Verdins DF RTU
//Year: 2020
//Description:
// Widget what rotate adverts(controls their status e.t.c) and renders them
// 
*/


//
// btw example of new code style of project
//
//


// C (more precisely: headers in angle brackets with the .h extension), e.g.
// <unistd.h>, <stdlib.h>

// C++
#include <ctime>  // for std::time_t type
#include <string>
#include<list>//list
#include <memory>//unique_ptr

// a11y libs

// my headers
#include "WgBackground.h"     //inheritance

#include"advert_shell.h"//here are stored adverts

class WgHtmlAds 
: public WgBackground 
{
public:

  /**
   * @brief checks if need rerender widget
   * 
   * Detailed: Check if json file was edited if so return true;
   * Checks colection contains adverts if not show stub until adverts update;
   * Loops thru adverts(cycling) to find working one
   * (except first advert because it's stub) 
   * if found sets it as current_advert return true
   * if loop passed places as current_advert_ the stub return true 
   *
   * @return true if adverts json file was edited,
   * found working ad, or stub must be placed
   * @return false adverts show time still do not expired or zero adverts in 
   * colection
   */
  bool update() override; // check if need update widget
  
  /**
   * @brief renders advert on the widget screen
   * 
   * Detailed: first renders adverts header block ,
   * second trys to render advert(picture) to widget,
   * if false then renders libshape msg about error and renders error header 
   * if true renders also current adverts header
   * and last renders shadows of all widgets (RenderOnlyShadows()) 
   *
   * @note libshape text is not done ,just prints in console about error.
   * also RenderOnlyShadows later will be fixed its engine problem not widget
   */
  void render() override; // renders advert into screen

  WgHtmlAds(int Ax, int Ay, WgMode Amode);
  ~WgHtmlAds();

private:

  /**
    * @brief Get the Json File Time object
    * 
    * @return std::time_t  last edit time of file
    * @note uses fmt() from Engine.h and UNIX stat() func
    */
  std::time_t GetJsonFileTime_(); // gets last time then edited 
  
  /**
   * @brief Detects if json containing adverts was edited
   * 
   * Detailed: Calls GetJsonFileTime_() method to get json file  time
   *
   * @return true if json's file time != json_file_time_
   * @return false they are equels
   */
  bool IsNeedRenewAdverts_(); // check if file(.json) was changed/edited

  /**
   * @brief cleans adverts what are stored in adverts container
   * 
   * Detailed: erases all adverts except first one (because it is stub) and
   * usleeps main thread on 250 microseconds (to get time to kill all threads)
   * and avoiding what new thread has pid of not deleted advert
   */
  void CleanAdverts_();//cleans adverts 

  /**
   * @brief init adverts 
   * 
   * Detailed: upload json file(adverts_json_path+/+adverts_json_name_) 
   * what stores adverts into json object j. 
   * then loops thru all ads in json object ,also checking if types are okey
   * if not sets is_valid to false and sends message to console 
   * where error appiered and advert is not valid, not valid advert 
   * is pushed into container, if all okey valid advert pusht into container
   */
  void InitilizeAdverts_();
  
  /**
   * @brief init stub and places it in first pos in colection
   * 
   */
  void InitStub_();

  //~~~stored strings
  std::string advert_dest_;
  std::string project_root_path_; 

  std::string adverts_json_path_;
  std::string adverts_json_name_;

  std::string advert_stub_name_;
  std::string advert_stub_path_;
  std::string advert_stub_title_;

  std::time_t widget_update_time_;
  std::time_t current_timestamp_;//stores last time then entered update
  std::time_t json_file_time_; // last timestamp then json file was edited

  std::list<std::unique_ptr<AdvertShell>>::iterator current_advert_;
  //colection
  std::list<std::unique_ptr<AdvertShell>> adverts_;

};

#endif /*SMART_RTU_SRC_WIDGETS_WGHTMLADS_WGHTMLADS_H_*/