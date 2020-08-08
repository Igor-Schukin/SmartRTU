
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
#include<vector>//vector
#include <memory>//unique_ptr

// a11y libs

// my headers
#include "WgBackground.h"     //inheritance

#include"advert_shell.h"//here are stored adverts

class WgHtmlAds 
: public WgBackground 
{
public:
  bool update() override; // check if need update widget
  void render() override; // renders advert into screen

  WgHtmlAds(int Ax, int Ay, WgMode Amode);
  ~WgHtmlAds();

private:
  std::time_t GetJsonFileTime_(); // gets last time then edited 
  bool IsNeedRenewAdverts_(); // check if file(.json) was changed/edited

  void CleanAdverts_();//cleans adverts and runs initilizeAdverts_


  void InitilizeAdverts_();
  //~~~stored strings
  std::string advert_dest_;
  std::string project_root_path_; 

  std::string adverts_json_path_;
  std::string adverts_json_name_;

  std::string advert_stub_name_;
  std::string advert_stub_path_;
  std::string advert_stub_title_;

  bool on_start_stub_showed_;

  std::time_t widget_update_time_;
  std::time_t current_timestamp_;//stores last time then entered update
  std::time_t json_file_time_; // last timestamp then json file was edited

  std::vector<std::unique_ptr<AdvertShell>>::iterator current_advert_;
  std::vector<std::unique_ptr<AdvertShell>> adverts_;

};

#endif /*SMART_RTU_SRC_WIDGETS_WGHTMLADS_WGHTMLADS_H_*/