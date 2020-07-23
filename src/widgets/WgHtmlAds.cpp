#include "WgHtmlAds.h"

// C
//#include <dirent.h> // in cpp ??? probably need to remove
#include <sys/stat.h>  // /* stat */ function
#include <sys/types.h> //needed for stat fucntion

// C++
#include <chrono>                 /*for milisecons for thread stuff */
#include <climits> /* PATH_MAX */ //
#include <cstdlib> // /*realpath*/ funtion for cutycapt also needed PATH_MAX from limits.h
#include <iostream> // /*cout*/

// A11Y libs

// own headers
#include "Engine.h" // from here we need only "fmt" stuff
#include "Timer.h"  ///* StrNow()*/

#include "configurator.h" //config



WgHtmlAds::WgHtmlAds(int Ax, int Ay, WgMode Amode)
    : WgBackground(Ax, Ay, Amode) 
{
  shadows_on_ = false; // default render of shadows off
  
  int update_time;
  config->Get("ADVERT_UPDATE_TIME", update_time); // converts string into int

  if (update_time <= 0) {
    Set_widget_update_time(3000);
   // widget_update_time_ = 3000; // sets 3 seconds update time  //int data type
  } else {
    Set_widget_update_time(update_time * 1000); // sets update time in seconds
  }

  // string part
  config->Get("HEADER_TEXT", header_text_);

  // advert part
  config->Get("ADVERT_PATH", local_ad_path_);
 


// get full path to exe
  char buff[PATH_MAX];
  realpath(".", buff);               
  full_path_to_project_exe_ = buff; 

  adverts_.reserve(3);
  adverts_.push_back(new AdvertShell(RectClient.left,RectClient.bottom,
                                   RectClient.width,RectClient.height,
                                   local_ad_path_,"HtmlAd.html.png",(18-update_time)));

  adverts_.push_back(new AdvertShell(RectClient.left,RectClient.bottom,
                                   RectClient.width,RectClient.height,
                                   local_ad_path_,"derp.png",(27-update_time)));
                                   
  adverts_.push_back(new AdvertShell(RectClient.left,RectClient.bottom,
                                   RectClient.width,RectClient.height,
                                   local_ad_path_,"cnn.png",(36-update_time)));


  timestamp_=std::time(0);
  current_advert_index_=0;
  std::cout << StrNow() << "\t"
            << "WgHtmlsAds widget object was created\n";
}

WgHtmlAds::~WgHtmlAds() {  }

bool WgHtmlAds::update() {
  std::time_t current_time;
  current_time=std::time(0);
  std::cout<<" "<<std::asctime(std::localtime(&current_time))<<current_time<<std::endl;
  if((current_time-timestamp_)>adverts_.at(current_advert_index_)->Get_show_time()){
   
    std::cout<<"Advert changed "<<current_time-timestamp_<<std::endl;
   
    timestamp_=current_time;
    current_advert_index_++;
    if(current_advert_index_>static_cast<int>(adverts_.size()-1)){
      current_advert_index_=0;
    }
   
    return true;
  }
 return false;
}

void WgHtmlAds::render() {
  WgBackground::render(); // if commented @ header and advert  block @ is
                          // tranperent

  //~~~ render header
  RenderWidgetHeader(header_text_.c_str());


  adverts_.at(current_advert_index_)->RenderAdvert();


  //~~~~~ render shadows
  WgBackground::RenderOnlyShadows();
}
