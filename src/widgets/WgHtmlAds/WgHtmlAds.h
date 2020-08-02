
#pragma once
#ifndef SMART_RTU_SRC_WIDGETS_WGHTMLADS_WGHTMLADS_H_
#define SMART_RTU_SRC_WIDGETS_WGHTMLADS_WGHTMLADS_H_

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
#include <ctime>  // for std::time_t type
#include <string>
#include<vector>//vector
#include <memory>//unique_ptr

// a11y libs

// my headers
#include "CPicturesStorage.h" //for Picture type
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

  void InitilizeAdverts_();
//json name,root_path,advert_dest,width,height,client top client buttom adcert//11/13
  //~~~stored strings
  std::string advert_dest_;
  std::string project_root_path_; 

  int current_advert_index_;//what advert is now on screen its index in vector
  
  
  std::time_t current_timestamp_;

  std::vector<std::unique_ptr<AdvertShell>>::iterator current_advert_it;
  std::vector<std::unique_ptr<AdvertShell>> adverts_;

//TODO
/*
1.MAKE INITIZEADVERTS METHOD
2.MAKE CYCLIC ITERATOR STUFF
2.1 ROTATION OF ADVERRTS TEST
3.DETECTION WHAT IF .JSON WAS EDITED

*/


};

#endif /*SMART_RTU_SRC_WIDGETS_WGHTMLADS_WGHTMLADS_H_*/