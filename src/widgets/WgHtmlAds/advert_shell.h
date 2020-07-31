#pragma once

#ifndef SMART_RTU_SRC_WIDGETS_WGHTMLADS_ADVERT_SHELL_H_
#define SMART_RTU_SRC_WIDGETS_WGHTMLADS_ADVERT_SHELL_H_

#include<string>//string
#include<ctime>//time_t

#include"Picture.h"//Picture

class AdvertShell{
public:

void RenderAdvert();

AdvertShell(int client_rect_left_pos, int client_rect_bottom_pos,
int widget_screen_width,int widget_screen_height,
const std::string&project_root_path,const std::string adverts_dest,
const std::string&a_url,const std::string &a_title_text,
std::time_t start_ts,std::time_t end_ts,
std::time_t a_watch_time,bool a_hidden_state);

~AdvertShell();

std::time_t Get_advert_show_time(){return advert_show_time_; }
std::string Get_advert_title(){return advert_title_;}

bool IsThreadReady();

private:
bool IsFileExist_(const std::string & a_file_name);
void DeleteFile_(const std::string & a_file_name);
//sets advert picture name 
void SetAdvertPictureName_();
void CutyCaptRequest_();

//Constructor Initializer List
int client_rect_left_pos_;
int client_rect_bottom_pos_;
//area of widget where avert will be placed
int widget_screen_width_;
int widget_screen_height_;
//full path to project root dir neede for cutycapt to dump images there
std::string project_root_path_;
std::string adverts_dest_;
std::string advert_url_;
std::string advert_title_;//also the title of advert
std::time_t advert_start_ts_;
std::time_t advert_end_ts_;
std::time_t advert_show_time_;
bool hidden_;//is advert hidden
//end of Constructor Initializer List

std::string advert_picture_name_;//stores advert name
std::string advert_pid_txt_name_;
pid_t cutycapt_pid;//PID of cutycapt request in system(console)

struct{float width;float height;}PictureScale;

Picture *advert_picture_;

};
#endif /*SMART_RTU_SRC_WIDGETS_WGHTMLADS_ADVERT_SHELL_H_*/