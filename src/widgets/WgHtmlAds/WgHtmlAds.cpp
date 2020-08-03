#include "WgHtmlAds.h"

// C
#include <sys/stat.h>  // /* stat */ function
#include <sys/types.h> //needed for stat fucntion
#include <unistd.h>//usleep()

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
  config->Get("ADVERT_UPDATE_TIME", update_time);

  if (update_time <= 0) {
    Set_widget_update_time(3000);
  } else {
    Set_widget_update_time(update_time * 1000); // sets update time in seconds
  }

  // advert part
  config->Get("ADVERT_DEST", advert_dest_);

  config->Get("ADVERT_JSON_PATH", adverts_json_path_);
  config->Get("ADVERT_JSON_FILE_NAME", adverts_json_name_);

  config->Get("ADVERT_STUB_PATH", advert_stub_path_);
  config->Get("ADVERT_STUB_NAME", advert_stub_name_);

// get full path to exe
  char buff[PATH_MAX];
  realpath(".", buff);               
  project_root_path_ = buff; 

  current_timestamp_=std::time(0);
  json_file_time_=this->GetJsonFileTime_();

  InitilizeAdverts_();

  current_advert_it=adverts_.begin();

  std::cout << StrNow() << "\t"
            << "WgHtmlsAds widget object was created\n";

}

WgHtmlAds::~WgHtmlAds() {  }

std::time_t WgHtmlAds::GetJsonFileTime_(){
   struct stat buff;
  // check if it can touch file and read last edit time of file
  if (stat(fmt("%s/%s", adverts_json_path_.c_str(),
               adverts_json_name_.c_str()),
           &buff) == 0)
  { 
    return buff.st_mtime;
  }
  else{
    return 0;
  }
}

bool WgHtmlAds::IsNeedRenewAdverts_(){
  std::time_t ft = this->GetJsonFileTime_();
  if ((ft != 0) && (ft != json_file_time_)) {
    json_file_time_ = ft;
    return true;
  }
  else{
  	return false;
  }
}


void WgHtmlAds::CleanAdverts_(){
  adverts_.clear();
  usleep(250);//get some time to destruct all previus ads
  InitilizeAdverts_();
}


void WgHtmlAds::InitilizeAdverts_()
{
  //probably need in try catch statement//  
  std::ifstream i(adverts_json_path_+'/'+adverts_json_name_);
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

  std::time_t current_time=std::time(0);
  if(this->IsNeedRenewAdverts_()==true){
    this->CleanAdverts_();
    //load stub
    std::cout<<"Json was edited\n";
    return true;
  }


  
   //check if advert ready to be shown
    if(current_advert_it->get()->isAdvertReady() && 
      current_advert_it->get()->IsTimeReady(current_timestamp_)&&
      ((current_time-current_timestamp_)<current_advert_it->get()->Get_advert_show_time())
      )
    {
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
