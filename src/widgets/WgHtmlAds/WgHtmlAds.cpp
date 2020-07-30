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
  current_advert_index_=0;
  std::cout << StrNow() << "\t"
            << "WgHtmlsAds widget object was created\n";


int a;
int b;
//std::cout<<"thread id is "<<system2("xvfb-run --server-args=\"-screen 0, 1920x1080x24\" cutycapt --url=http://www.google.com --out=google.png &",&a,&b)<<std::endl;

//std::cout<<"exec way "<<std::system("./scipt.sh")<<std::endl;
//std::cout<<"exec way "<<exec("./scipt.sh")<<std::endl;
//usleep(2000);
//std::cout<<"exec way "<<std::system("./scipt.sh")<<std::endl;

std::cout<<"exec "<<std::system("xvfb-run -a --server-args=\"-screen 0, 1920x1080x24\" cutycapt --url=http://www.google.com --out=google.png & echo $! >pid.txt")<<std::endl;
 std::cout <<std::ifstream("pid.txt").rdbuf();
 //usleep(500);
 //std::cout<<"exec2 "<<std::system("cutycapt --url=http://www.google.com --out=google1.png & echo $! >pid1.txt")<<std::endl;
 std::cout<<"exec "<<std::system("xvfb-run -a --server-args=\"-screen 0, 1920x1080x24\" cutycapt --url=http://www.google.com --out=google1.png & echo $! >pid1.txt")<<std::endl;

 std::cout <<std::ifstream("pid1.txt").rdbuf();

  std::cout<<"exec "<<std::system("xvfb-run -a --server-args=\"-screen 0, 1920x1080x24\" cutycapt --url=http://www.typingme.com/touch-typing-amateur/typing-lesson-10.php --out=google2.png & echo $! >pid2.txt")<<std::endl;

 std::cout <<std::ifstream("pid2.txt").rdbuf();

  std::cout<<"exec "<<std::system("xvfb-run -a --server-args=\"-screen 0, 1920x1080x24\" cutycapt --url=http://www.google.com --out=google3.png & echo $! >pid3.txt")<<std::endl;

 std::cout <<std::ifstream("pid3.txt").rdbuf();

  std::cout<<"exec "<<std::system("xvfb-run -a --server-args=\"-screen 0, 1920x1080x24\" cutycapt --url=http://politeh.lv/home/index.php --out=google4.png & echo $! >pid4.txt")<<std::endl;

 std::cout <<std::ifstream("pid4.txt").rdbuf();

  std::cout<<"exec "<<std::system("xvfb-run -a --server-args=\"-screen 0, 1920x1080x24\" cutycapt --url=http://www.google.com --out=google5.png & echo $! >pid5.txt")<<std::endl;

 std::cout <<std::ifstream("pid5.txt").rdbuf();

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
 /* WgBackground::render(); // if commented @ header and advert  block @ is
                          // tranperent

  //~~~ render header
  RenderWidgetHeader(adverts_.at(current_advert_index_)->Get_advert_title().c_str());


  adverts_.at(current_advert_index_)->RenderAdvert();


  //~~~~~ render shadows
  WgBackground::RenderOnlyShadows();*/
}
