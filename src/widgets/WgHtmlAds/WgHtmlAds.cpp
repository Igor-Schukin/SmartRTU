#include "WgHtmlAds.h"

// C
//#include <dirent.h> // in cpp ??? probably need to remove
#include <sys/stat.h>  // /* stat */ function
#include <sys/types.h> //needed for stat fucntion

// C++
#include <climits> /* PATH_MAX */ //
#include <cstdlib> // /*realpath*/ funtion for cutycapt also needed PATH_MAX from limits.h
#include <iostream> // /*cout*/
#include <fstream>//ifstream
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



  current_timestamp_=std::time(0);

  InitilizeAdverts_();


  current_advert_it=adverts_.begin();

  //auto end=adverts_.end();
 // std::cout<<"Size of vector is "<<end->get()->Get_advert_title()<<std::endl;
  std::cout << StrNow() << "\t"
            << "WgHtmlsAds widget object was created\n";

}



WgHtmlAds::~WgHtmlAds() {  }

void WgHtmlAds::InitilizeAdverts_()
{
  //probably need in try catch statement//  
  std::ifstream i("./res/adverts.json");
	json j;
	i >> j;
  std::cout<<"json size: "<<j.size()<<std::endl;
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
  //std::cout<<"Inside update\n";
  
  //TODO
  //FIX ERROR adverts_.end();


  //todo
  //UPDATE CURRENT TIMESTAMP

  //check if show time is okey and is advert ready of advert
    //if all okey return true else:
  //loop to next advert what is fully ready and place it on iterator
    //cyclic loop
  //if full loop i==vector.size() then place stub instead



  std::time_t current_time=std::time(0);

  
   //check if advert ready to be shown
    if(current_advert_it->get()->isAdvertReady() && 
      current_advert_it->get()->IsTimeReady(current_timestamp_)&&
      ((current_time-current_timestamp_)<current_advert_it->get()->Get_advert_show_time())
      )
    {
      //std::cout<<"Advert is shown"<<current_advert_it->get()->Get_advert_title()<<"\n\n";
     return false;
    }



  unsigned int i=0;
  while(i!=adverts_.size()){

    if(current_advert_it==adverts_.end()-1){
      current_advert_it=adverts_.begin();
      
    }
    else{
      ++current_advert_it;
    }

    
    //check if advert ready to be shown
    if(current_advert_it->get()->isAdvertReady() && 
      current_advert_it->get()->IsTimeReady(std::time(0))
      )
    {
    current_timestamp_=std::time(0);
     return true;
    }
  

    ++i;
  }

  if(i==adverts_.size()){
    //load stub or mark it with flag
    current_timestamp_=std::time(0);
    std::cout<<"STUB must be shown now"<<std::endl;
    return false;//false is here tmp
  }
  return false;
}

void WgHtmlAds::render() {
  WgBackground::render(); // if commented @ header and advert  block @ is
                          // tranperent


  //~~~ render header
  RenderWidgetHeader((current_advert_it->get()->Get_advert_title()).c_str());

  current_advert_it->get()->RenderAdvert();


  //~~~~~ render shadows
  WgBackground::RenderOnlyShadows();
}
