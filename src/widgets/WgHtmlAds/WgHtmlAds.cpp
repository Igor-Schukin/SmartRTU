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
#include<string>
// A11Y libs

// own headers
#include "Engine.h" // from here we need only "fmt" stuff
#include "Timer.h"  ///* StrNow()*/

#include "configurator.h" //config
#include "json.h"

using json = nlohmann::json;



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
  config->Get("ADVERT_PATH", advert_dest_);
 


// get full path to exe
  char buff[PATH_MAX];
  realpath(".", buff);               
  project_root_path_ = buff; 



  timestamp_=std::time(0);

  InitilizeAdverts_();


  current_advert_it=adverts_.begin();
  std::cout << StrNow() << "\t"
            << "WgHtmlsAds widget object was created\n";

}



WgHtmlAds::~WgHtmlAds() {  }

void WgHtmlAds::InitilizeAdverts_()
{
  //probably need in try catch statement
  std::ifstream i("./res/adverts.json");
	json j;
	i >> j;

  adverts_.reserve(j.size());

  std::string url{};
  std::string title{};
  std::time_t start_ts=0;
  std::time_t end_ts=0;
  std::time_t show_time=0;
  bool hidden=true;
  
  //valid advert means without errors
  bool is_valid_advert=true;

  for (json::iterator it = j.begin(); it != j.end(); ++it) {
    //probably better to just make one if
    //what detects if fields are rigth type
    //if not std::cerr it and set advert as not valid
    if(it[0]["url"].is_string()){
      url=it[0]["url"];
    }
    else{
      std::cerr<<"Do not detected url string!! advert is not valid\n";
      is_valid_advert=false;
    }
    if(it[0]["title"].is_string()){
      title=it[0]["title"];
    }else{
      std::cerr<<"Do not detected title string!! advert is not valid\n";
      is_valid_advert=false;
    }

    if(it[0]["start_ts"].is_number()){
      start_ts=it[0]["start_ts"].get<std::time_t>();
    }
    else{
      std::cerr<<"Do not detected start_ts number!! advert is not valid\n";
      is_valid_advert=false;
    }

    if(it[0]["end_ts"].is_number()){
      end_ts=it[0]["end_ts"].get<std::time_t>();
    }
    else{
      std::cerr<<"Do not detected end_ts number!! advert is not valid\n";
      is_valid_advert=false;
    }

    if(it[0]["show_time"].is_number()){
      show_time=it[0]["show_time"].get<std::time_t>();
    }
    else{
      std::cerr<<"Do not detected show_time number!! advert is not valid\n";
      is_valid_advert=false;
    }

    if(it[0]["hidden"].is_boolean()){
      hidden=it[0]["hidden"];
    }
    else{
      std::cerr<<"Do not detected hidden boolean!! advert is not valid\n";
      is_valid_advert=false;
    }

    adverts_.push_back(std::unique_ptr<AdvertShell>(std::move(new AdvertShell(
      RectClient.left,RectClient.bottom,
      RectClient.width,RectClient.height,
      project_root_path_,advert_dest_,
      url,title,
      start_ts,end_ts,
      show_time,hidden,
      is_valid_advert
    ))));
  }                      
}



bool WgHtmlAds::update() {
  std::cout<<"Inside update\n";
  if(std::time(0)-timestamp_>30)return true;

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
  if(std::time(0)-timestamp_>30){
  adverts_.clear();
  }
  return;
  WgBackground::render(); // if commented @ header and advert  block @ is
                          // tranperent

  //~~~ render header
  RenderWidgetHeader((current_advert_it->get()->Get_advert_title()).c_str());

  current_advert_it->get()->RenderAdvert();


  //~~~~~ render shadows
  WgBackground::RenderOnlyShadows();
}
