#include"advert_shell.h"

#include <sys/stat.h>//stat()
#include <signal.h>//kill()
#include <unistd.h>//usleep()

#include <string>//string
#include <fstream>//ifstream
#include <iostream>//cerr
#include<chrono>//for miliseconds

AdvertShell::~AdvertShell() {
    if(advert_picture_!=nullptr){
        delete advert_picture_;
    }
    if(IsAdvertThreadReady_()!=true){
     std::system(("kill "+std::to_string(cutycapt_pid_)).c_str());
     usleep(500);
    }

    // check if .txt exist if so delete it
    if(this->IsFileExist_(
        project_root_path_+'/'+advert_picture_dest_+'/'+advert_pid_txt_name_
                         )              
      )
    {
        this->DeleteFile_(
            project_root_path_+'/'+advert_picture_dest_+'/'+advert_pid_txt_name_
            );
    }

    //check if .png exist if so delete it
    if(this->IsFileExist_(
        project_root_path_+'/'+advert_picture_dest_+'/'+advert_picture_name_
                        )
      )
    {
        this->DeleteFile_(
            project_root_path_+'/'+advert_picture_dest_+'/'+advert_picture_name_
            );
    }
    //reliese future object if it was not reliesed
    if(cutycapt_thread_.valid()){
        cutycapt_thread_.get();
    }

}


bool AdvertShell::RenderAdvert() {
   
  if(advert_picture_==nullptr)
  {
       try 
       {
        advert_picture_ = new Picture((advert_picture_dest_ + "/" + advert_picture_name_).c_str());
        PictureScale.width = static_cast<float>(widget_screen_width_) /
                               static_cast<float>(advert_picture_->Get_width());
        PictureScale.height = static_cast<float>(widget_screen_height_) /
                                static_cast<float>(advert_picture_->Get_height());
        
         advert_picture_->render(client_rect_left_pos_, client_rect_bottom_pos_,
                     PictureScale.width, PictureScale.height, 0, 0,
                      0);
        return true;
      } 
      catch (...) 
      {

          //what to do if something bad will happen??
          //now on next render try it will try again
            std::cerr <<  "\t"
            << "Something bad happened with initialising advert_picture_ \n";

            if(advert_picture_)
            {
              delete advert_picture_;
              advert_picture_=nullptr;
            }
        return false;
      }
   }
  
    advert_picture_->render(client_rect_left_pos_, client_rect_bottom_pos_,
                     PictureScale.width, PictureScale.height, 0, 0,
                      0);
    return true;  
}

AdvertShell::AdvertShell(int client_rect_left_pos, int client_rect_bottom_pos, 
    int widget_screen_width, int widget_screen_height, 
    const std::string&project_root_path, const std::string adverts_dest, 
    const std::string&a_url, const std::string &a_title_text, 
    std::time_t start_ts, std::time_t end_ts, 
    std::time_t a_show_time, bool a_hidden_state,
    bool is_valid) 
 :client_rect_left_pos_(client_rect_left_pos),
 client_rect_bottom_pos_(client_rect_bottom_pos),
 widget_screen_width_(widget_screen_width),
 widget_screen_height_(widget_screen_height),
 project_root_path_(project_root_path),
 advert_picture_dest_(adverts_dest),
 advert_url_(a_url),
 advert_title_(a_title_text),
 advert_start_ts_(start_ts),
 advert_end_ts_(end_ts),
 advert_show_time_(a_show_time),
 hidden_(a_hidden_state),
 is_valid_(is_valid)
{
    advert_picture_=nullptr;
    this->SetAdvertPictureName_();
    advert_pid_txt_name_=advert_picture_name_+"_pid.txt";

 //launch cutycapt asinc stuff
 if(hidden_!=true && is_valid_==true){
 cutycapt_thread_=std::async(
    std::launch::async, &AdvertShell::CutyCaptRequest_, this);
 }
}

//stub constructor
AdvertShell::AdvertShell(int client_rect_left_pos, int client_rect_bottom_pos,
                int widget_screen_width,int widget_screen_height,
                const std::string&a_stub_path,const std::string&a_stub_name,
                const std::string&a_stub_title,std::time_t show_time)
:client_rect_left_pos_(client_rect_left_pos),
 client_rect_bottom_pos_(client_rect_bottom_pos),
 widget_screen_width_(widget_screen_width),
 widget_screen_height_(widget_screen_height),
 advert_picture_dest_(a_stub_path),
 advert_title_(a_stub_title),
 advert_show_time_(show_time)
{
    this->advert_picture_name_=a_stub_name;
    advert_picture_=nullptr;
    project_root_path_="";//must be emty to not delete stub picture
     advert_url_="";
    advert_start_ts_=0;
    advert_end_ts_=0;
    hidden_=false;
    is_valid_=false;//stub is always not valid
    cutycapt_thread_status_=std::future_status::ready;
}




void AdvertShell::SetAdvertPictureName_() {
	int pos = advert_url_.length();
	for (auto i = advert_url_.crbegin(); i < advert_url_.crend(); ++i)
	{
		if (*i == '/' || *i == '&' || *i == '\\' || *i == '='||*i=='?')
        {
            break;
        }
		pos--;
		
	}
    advert_picture_name_= advert_url_.substr(pos)+".png";
}

void AdvertShell::CutyCaptRequest_() {
 //runn cutycapt transformation stuff in system and writes its pid into txt file
    std::system(
        ("xvfb-run -a --server-args=\"-screen 0, 1920x1080x24\" cutycapt --url="+
        advert_url_ +" --out="+advert_picture_dest_+'/'+advert_picture_name_+
        " & echo $! >"+advert_picture_dest_+'/'+advert_pid_txt_name_).c_str()
        );

    //parse pid_txt_name file to get pid of process
    std::string line;
    std::ifstream myfile ((advert_picture_dest_+'/'+advert_pid_txt_name_));
    if (myfile.is_open())
    {
            myfile>>line;

        myfile.close();
    }
    else{
        std::cerr<<"Cutycapt transformation command pid was now written into or found in "
        <<advert_picture_dest_+'/'+advert_pid_txt_name_<<"can not get PID!!! RETURN!\n";
        return;  
    }

    this->cutycapt_pid_=std::stoi(line);

    //about kill()
    /*
           kill sends a signal to a process or a group of processes.
          The process or group of processes to which the signal is to
          be sent is specified by pid.  The signal that is to be sent
          is specified by sig and is either one from the list given in
          signal(2), or 0.  If sig is 0 (the null signal), error
          checking is performed but no signal is actually sent.  This
          can be used to check the validity of pid.
    */

    //check if thread is still valid/active 
    //output <0 means its dead/finished its work or troble happened
    while(kill(this->cutycapt_pid_,0)==0){
        usleep(1000);//sleep thraed on one milisecond
    }
}

bool AdvertShell::IsFileExist_(const std::string & a_file_name) {
    //check this for alternatives
    //https://stackoverflow.com/questions/12774207/fastest-way-to-check-if-a-file-exist-using-standard-c-c11-c    

    //function stat() filling data into statbuf struct
    // on pointer of filename info about file uses  #include<sys\stat.h>
    //on succes filling data into struct return 0(means also what file exist),
    //on failure returns -1 and errno becomes ENOENT 


  struct stat buffer;   
  return (stat (a_file_name.c_str(), &buffer) == 0); 

}

void AdvertShell::DeleteFile_(const std::string & a_file_name) {
    std::system(("rm "+a_file_name).c_str());
}

bool AdvertShell::IsAdvertThreadReady_() {
    // get status of thread//it actually freezes it for under 1 milisecond to get
  // status of thread
cutycapt_thread_status_ = cutycapt_thread_.wait_for(
                                                std::chrono::milliseconds(0)
                                                );

  return (cutycapt_thread_status_ == std::future_status::ready);
}

bool AdvertShell::IsAdvertReady() {
    if(this->IsAdvertThreadReady_()&&
    hidden_!=true&&
    this->IsFileExist_(advert_picture_dest_+'/'+advert_picture_name_)){
        return true;
    }
    else{
        return false;
    }
}

bool AdvertShell::IsAdvertValid() {
    return is_valid_;
}


bool AdvertShell::IsTimeReady(std::time_t a_time_stamp) {
    return true;//temporary
    if(a_time_stamp>=advert_start_ts_ && a_time_stamp<advert_end_ts_){
        return true;
    }
    else{
        return false;
    }
}
