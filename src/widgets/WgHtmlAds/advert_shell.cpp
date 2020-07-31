#include"advert_shell.h"

#include <sys/stat.h>//stat()
#include <signal.h>//kill()
#include <unistd.h>//usleep()

#include <string>//string
#include <fstream>//ifstream
#include <iostream>//cerr

AdvertShell::~AdvertShell() {
    if(advert_picture_!=nullptr){
        delete advert_picture_;
    }

    std::system(("kill "+std::to_string(cutycapt_pid)).c_str());
    usleep(500);

    // check if .txt exist if so delete it
    if(this->IsFileExist_(
        project_root_path_+'/'+adverts_dest_+'/'+advert_pid_txt_name_
                        )
      )
    {
        this->DeleteFile_(
            project_root_path_+'/'+adverts_dest_+'/'+advert_pid_txt_name_
            );
    }

    //check if .png exist if so delete it
    if(this->IsFileExist_(
        project_root_path_+'/'+adverts_dest_+'/'+advert_picture_name_
                        )
      )
    {
        this->DeleteFile_(
            project_root_path_+'/'+adverts_dest_+'/'+advert_picture_name_
            );
    }


}


void AdvertShell::RenderAdvert() {
    if(advert_picture_!=nullptr){
        advert_picture_->render(client_rect_left_pos_, client_rect_bottom_pos_,
                       PictureScale.width, PictureScale.height, 0, 0,
                       0);    
    }
}

AdvertShell::AdvertShell(int client_rect_left_pos, int client_rect_bottom_pos, 
    int widget_screen_width, int widget_screen_height, 
    const std::string&project_root_path, const std::string adverts_dest, 
    const std::string&a_url, const std::string &a_title_text, 
    std::time_t start_ts, std::time_t end_ts, 
    std::time_t a_show_time, bool a_hidden_state) 
:client_rect_left_pos_(client_rect_left_pos),
client_rect_bottom_pos_(client_rect_bottom_pos),
widget_screen_width_(widget_screen_width),
widget_screen_height_(widget_screen_height),
project_root_path_(project_root_path),
adverts_dest_(adverts_dest),
advert_url_(a_url),
advert_title_(a_title_text),
advert_start_ts_(start_ts),
advert_end_ts_(end_ts),
advert_show_time_(a_show_time),
hidden_(a_hidden_state)
{
    advert_picture_=nullptr;
    this->SetAdvertPictureName_();
    advert_pid_txt_name_=advert_picture_name_+".pid.txt";

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
    advert_url_ +"--out="+adverts_dest_+'/'+advert_picture_name_+
    " & echo $! >"+adverts_dest_+'/'+advert_pid_txt_name_).c_str()
    );

   //parse pid_txt_name file to get pid of process
   std::string line;
   std::ifstream myfile ((adverts_dest_+'/'+advert_pid_txt_name_));
   if (myfile.is_open())
   {
        myfile>>line;

      myfile.close();
   }
   else{
       std::cerr<<"Cutycapt transformation command pid was now written into or found in "
       <<adverts_dest_+'/'+advert_pid_txt_name_<<"can not get PID!!! RETURN!\n";
       return;  
   }

    cutycapt_pid=std::stoi(line);

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
    while(kill(cutycapt_pid,0)==0){
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

bool AdvertShell::IsThreadReady() {
    
}
