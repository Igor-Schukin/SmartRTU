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

std::time_t WgHtmlAds::GetFileTime_() {
  struct stat buff;
  // check if it can touch file and read last edit time of file
  if (stat(fmt("%s/%s", local_html_input_file_dest_.c_str(),
               html_name_.c_str()),
           &buff) == 0) 
    return buff.st_mtime;
  return 0;
}

bool WgHtmlAds::NeedRenew_() {
  std::time_t ft = WgHtmlAds::GetFileTime_();
  if ((ft != 0) && (ft != file_time_)) {
    file_time_ = ft;
    return true;
  }
  else{
  	return false;
  }
}

void WgHtmlAds::CleanPicture_() {
  if (advert_pic_) {
    delete advert_pic_;
    advert_pic_ = nullptr;
  }
}

void WgHtmlAds::CutyCaptRequest_() {

  // remember white spaces are important for cutycapt!!!
  std::system(("xvfb-run --server-args=\"-screen 0, 1920x1080x24\" "
                      "cutycapt  --url=file:" +
                      full_path_to_project_exe_ + "/" +
                      local_html_input_file_dest_ + "/" + html_name_ +
                      " --out=" + full_path_to_project_exe_ + "/" +
                      local_ad_path_ + "/" + ad_name_).c_str()
              );
}

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
  config->Get("header_text_", header_text_);
  // .html part
  config->Get("ADVERT_INPUT_FILE_DEST", local_html_input_file_dest_);
  config->Get("ADVERT_INPUT_FILE", html_name_);
  // advert part
  config->Get("ADVERT_PATH", local_ad_path_);
  config->Get("ADVERT_NAME", ad_name_);
  // stub part
  config->Get("ADVERT_PATH",local_stub_path_); 
  config->Get("ADVERT_STUB_NAME", stub_name_);

// get full path to exe
  char buff[PATH_MAX];
  realpath(".", buff);               
  full_path_to_project_exe_ = buff; 

  advert_on_screen_ = false;

  advert_pic_ = nullptr;
  file_time_ = GetFileTime_();

  // run async cutycapt request
  future_ =std::async(std::launch::async, &WgHtmlAds::CutyCaptRequest_, this);

  std::cout << StrNow() << "\t"
            << "WgHtmlsAds widget object was created\n";
}

WgHtmlAds::~WgHtmlAds() { this->CleanPicture_(); }

bool WgHtmlAds::update() {
  // get status of thread//it actually freezes it for under 1 milisecond to get
  // status of thread
  thread_status_ = future_.wait_for(std::chrono::milliseconds(0));

  // check if thread finished
  if (thread_status_ == std::future_status::ready) {

    // needed if thread done its job
    if (advert_on_screen_ == false) {
      return true;
	  
    } else if (NeedRenew_() == true) {
      std::cout << StrNow() << "\t"
                << "Detected what advert's ->" << ad_name_
                << "<- .html was edited\n";

      future_ =
          std::async(std::launch::async, &WgHtmlAds::CutyCaptRequest_, this);
      std::cout << StrNow() << "\t"
                << "Cutycapt successfully lauched\n";

      advert_on_screen_ = false;

      return true;

    } else {
      return false;
    }
  } else {
    return false;
  }
}

void WgHtmlAds::render() {
  WgBackground::render(); // if commented @ header and advert  block @ is
                          // tranperent

  //~~~ render header
  RenderWidgetHeader(header_text_.c_str());

  // Use wait_for() with zero milliseconds to check thread status.
  thread_status_ =
      future_.wait_for(std::chrono::milliseconds(0)); // get status of thread

  // check if thread finished.
  if (thread_status_ == std::future_status::ready) {
    std::cout << StrNow() << "\t"
              << "Cutycapt finished its work\n";
    if (advert_on_screen_ != true) {
      // std::cout << StrNow() << "\t" << "Cutycapt finished its work\n";
      this->CleanPicture_();
      try {
        advert_pic_ = new Picture((local_ad_path_ + "/" + ad_name_).c_str());
      } catch (...) {
        std::cerr << StrNow() << "\t"
                  << "Something bad happened  with loading advert, STUB placed "
                     "instead!!! \n";
        this->CleanPicture_();
        // stub placed instead
        advert_pic_ =
            new Picture((local_stub_path_ + "/" + stub_name_).c_str());
      }

      image_scale_by_width_ = static_cast<float>(RectClient.width) /
                               static_cast<float>(advert_pic_->Get_width());
      image_scale_by_height_ = static_cast<float>(RectClient.height) /
                                static_cast<float>(advert_pic_->Get_height());

      advert_on_screen_ = true;
      std::cout << StrNow() << "\t"
                << "Advert was placed on the advert widget screen \n";
    }
  } else {
    if (advert_pic_ == nullptr) {
      advert_pic_ =
          new Picture((local_stub_path_ + "/" + stub_name_).c_str());
      image_scale_by_width_ = static_cast<float>(RectClient.width) /
                               static_cast<float>(advert_pic_->Get_width());
      image_scale_by_height_ = static_cast<float>(RectClient.height) /
                                static_cast<float>(advert_pic_->Get_height());

      std::cout << StrNow() << "\t"
                << "Stub was placed on the widget screen \n";
    }
  }

  // render Advert
  advert_pic_->render(RectClient.left, RectClient.bottom,
                       image_scale_by_width_, image_scale_by_height_, 0, 0,
                       0);

  //~~~~~ render shadows
  WgBackground::RenderOnlyShadows();
}
