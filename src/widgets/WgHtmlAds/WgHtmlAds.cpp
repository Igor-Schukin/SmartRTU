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
#include <memory>
// A11Y libs

// own headers
#include "Engine.h" // from here we need only "fmt" stuff
#include "Timer.h"  ///* StrNow()*/

#include "configurator.h" //config



#include <sys/types.h>
#include <signal.h>
#include<cstdlib>


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

  // advert part
  config->Get("ADVERT_PATH", local_ad_path_);
 


// get full path to exe
  char buff[PATH_MAX];
  realpath(".", buff);               
  full_path_to_project_exe_ = buff; 

  /*adverts_.reserve(3);
  adverts_.push_back(std::unique_ptr<AdvertShell>(new AdvertShell(RectClient.left,RectClient.bottom,
                                   RectClient.width,RectClient.height,
                                   local_ad_path_,"HtmlAd.html.png",
                                   (243-update_time),"first advert"))
                      );

  adverts_.push_back(std::unique_ptr<AdvertShell>(new AdvertShell(RectClient.left,RectClient.bottom,
                                   RectClient.width,RectClient.height,
                                   local_ad_path_,"derp.png",
                                   (81-update_time),"second advert")));
                                   
  adverts_.push_back(std::unique_ptr<AdvertShell>(new AdvertShell(RectClient.left,RectClient.bottom,
                                   RectClient.width,RectClient.height,
                                   local_ad_path_,"cnn.png",
                                   (27-update_time),"third advert")));

*/
  timestamp_=std::time(0);
current_advert_it=adverts_.begin();
  std::cout << StrNow() << "\t"
            << "WgHtmlsAds widget object was created\n";

}



WgHtmlAds::~WgHtmlAds() {  }

bool WgHtmlAds::update() {
 /* std::time_t current_time;
  current_time=std::time(0);
  //std::cout<<" "<<std::asctime(std::localtime(&current_time))<<current_time<<std::endl;
  if((current_time-timestamp_)>adverts_.at(current_advert_index_)->Get_show_time()){
   
    
   
    timestamp_=current_time;
    current_advert_index_++;
    if(current_advert_index_>static_cast<int>(adverts_.size()-1)){
      current_advert_index_=0;
    }
   std::cout<<"Advert changed advert is"<<current_advert_index_<<std::endl;
    return true;
  }*/
 return false;
}

void WgHtmlAds::render() {
  return;
  WgBackground::render(); // if commented @ header and advert  block @ is
                          // tranperent

  //~~~ render header
  RenderWidgetHeader((current_advert_it->get()->Get_advert_title()).c_str());

  current_advert_it->get()->RenderAdvert();


  //~~~~~ render shadows
  WgBackground::RenderOnlyShadows();
}
