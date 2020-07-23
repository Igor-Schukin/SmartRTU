
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
#include<vector>
// a11y libs

// my headers
#include "CPicturesStorage.h" //for Picture type
#include "WgBackground.h"     //inheritance

#include"advert_shell.h"

class WgHtmlAds 
: public WgBackground 
{
public:
  bool update() override; // check if need update widget
  void render() override; // renders advert into screen

  WgHtmlAds(int Ax, int Ay, WgMode Amode);
  ~WgHtmlAds();

private:
  //~~~stored strings
  std::string header_text_; 
  std::string local_ad_path_;
  std::string full_path_to_project_exe_; // cutycapt need full path to exe
                                          // otherwise it wont work

  int current_advert_index_;//what advert is now on screen its index in vector
  std::vector<AdvertShell*> adverts_;

  std::time_t timestamp_;

};

#endif /*SMART_RTU_SRC_WIDGETS_WGHTMLADS_H_*/