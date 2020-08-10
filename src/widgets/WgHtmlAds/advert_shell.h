#pragma once

/*
//Author:Dainis Verdins DF RTU
//Year: 2020
//Description:
//is shell of Picture class,used to store as a container adverts
// uses cutycapt and XVFB to work + async threads
*/




#ifndef SMART_RTU_SRC_WIDGETS_WGHTMLADS_ADVERT_SHELL_H_
#define SMART_RTU_SRC_WIDGETS_WGHTMLADS_ADVERT_SHELL_H_

#include <signal.h>//for pid_t()
#include <unistd.h>//pid_t

#include<string>//string
#include<ctime>//time_t
#include <future> //future
#include <thread> //std::launc::async

#include"Picture.h"//Picture

//at witch timestamp always show advert 
#define ALWAYS_SHOW_TIMESTAMP 0 

class AdvertShell{
public:

/**
 * @brief renders advert on widget screen
 * 
 * Detailed:first check if advert_picture_ is nullptr if so it 
 * means pic is empty, try catch statement trys to init it if so
 * also calculates PictureScale width and height and return true,if not 
 * sends error into console, cleans(delete) advert_picture and return false.  
 * If advert already exist(advert_picture_!=nullptr) trys to render it if so
 * return true otherwise returns false. 
 *
 * @return true if succesfully rendered picture
 * @return false some errors appiered  on initializng advert picture or
 * rendering picture->render() something got bad 
 */
bool RenderAdvert();

//This constructor if for stub not for adverts
AdvertShell(int client_rect_left_pos, int client_rect_bottom_pos,
int widget_screen_width,int widget_screen_height,
const std::string&a_stub_path,const std::string&a_stub_name,
const std::string&a_stub_title,std::time_t show_time);

AdvertShell(int client_rect_left_pos, int client_rect_bottom_pos,
int widget_screen_width,int widget_screen_height,
const std::string&project_root_path,const std::string adverts_dest,
const std::string&a_url,const std::string &a_title_text,
std::time_t start_ts,std::time_t end_ts,
std::time_t a_watch_time,bool a_hidden_state,
bool is_valid);

~AdvertShell();

std::time_t Get_advert_show_time(){return advert_show_time_; }
std::string Get_advert_title(){return advert_title_;}

/**
 * @brief check if advert ready to be rendered or not
 * 
 * @return true if Cutycapt done its bussines, not hidden and ad picture exist
 * @return false 
 */
bool IsAdvertReady();

/**
 * @brief detects if time to come to show advert
 * 
 * @param a_time_stamp current system time
 * @return true if a_time_stamp is between start_ts and end_ts
 * @return false  if a_time_stamp is not between start_ts and end_ts
 * @note if advert_start_ts and advert_ts ar equels with ALWAYS_SHOW_TIMESTAMP
 * will always return true
 */
bool IsTimeReady(const std::time_t a_time_stamp);

/**
 * @brief detects if advert is valid or not
 * 
 * @return true is valid
 * @return false is not valid
 * @note valid means no errors(wrong type,wrong input type e.tc) appiered 
 * on initilizng advert, or is stub/
 */
bool IsAdvertValid();

private:

/**
 * @brief Detects if file exist or not
 * 
 * Detailed: using stat() gets data from file on succes return 0
 *
 * @param a_file_name file name
 * @return true if file exists
 * @return false if file do not exist,stat() do not detected file
 * @note uses library #include<sys\stat.h>, and have alternatives check ref
 * @ref https://stackoverflow.com/questions/12774207/fastest-way-to-check-if-a-file-exist-using-standard-c-c11-c 
 */
bool IsFileExist_(const std::string & a_file_name);

/**
 * @brief deletes file
 * 
 * Detailed: uses std::system() to delete file
 * @param a_file_name file name what will be deleted
 */
void DeleteFile_(const std::string & a_file_name);

/**
 * @brief Sets ads picture name 
 *
 *Detailed: cuts from string ending until stops on /,&,\,=, or ? 
 *and adds ".png" to ending of cuted string and sets to advert_picture_name_
 * 
 */
void SetAdvertPictureName_();

/**
 * @brief Runs Cutycapt and XVFB to transform curl string into picture
 * 
 * First check if advert is hidden or is_valid if so return,thread finished.
 * if all okey, runs std::system call of Xvfb server and cutycatp request to
 * transform url(webpage) into image, uses '&' to not stop thread,and writes
 * its PID(cutycapt and XVFB) into file(advert_pid_txt_name_),
 * then is parsing of the file to get its PID and PID
 * is written into cutycapt_pid_.After this starts while loop with kill()
 * what detects if thread finished or not,if not usleeps method on 1 milisecond
 * and reapets itself until thread is finished or dead/broken
 *
 * @note  kill sends a signal to a process or a group of processes.
          The process or group of processes to which the signal is to
          be sent is specified by pid.  The signal that is to be sent
          is specified by sig and is either one from the list given in
          signal(2), or 0.  If sig is 0 (the null signal), error
          checking is performed but no signal is actually sent.  This
          can be used to check the validity of pid.
    
 */
void CutyCaptRequest_();

/**
 * @brief Detects if CutyCaptRequest_ method finished or not
 * 
 * Detailed: freezes CutyCaptRequest_ method under one milisecond
 * to get its status into std::future_status variable and checks 
 * its ready or not
 *
 * @return true cutycapt thread finished a.k.a ready
 * @return false if it still active/working
 */
bool IsAdvertThreadReady_();

//Constructor Initializer List
int client_rect_left_pos_;
int client_rect_bottom_pos_;
//area of widget where avert will be placed
int widget_screen_width_;
int widget_screen_height_;
//full path to project root dir neede for cutycapt to dump images there
std::string project_root_path_;
std::string advert_picture_dest_;
std::string advert_url_;
std::string advert_title_;//also the title of advert
std::time_t advert_start_ts_;
std::time_t advert_end_ts_;
std::time_t advert_show_time_;
bool hidden_;//is advert hidden
//state  of advert is broken one(wrong initializng parameters) or not
bool is_valid_;

//end of Constructor Initializer List

std::string advert_picture_name_;//stores advert name
std::string advert_pid_txt_name_;
pid_t cutycapt_pid_;//PID of cutycapt request in system(console)

struct{float width;float height;}PictureScale;

//~thread variables
std::future<void> cutycapt_thread_; // is obj of  new async thread 
// stored status of thread //probably can avoid it
std::future_status cutycapt_thread_status_; 

Picture *advert_picture_;

};
#endif /*SMART_RTU_SRC_WIDGETS_WGHTMLADS_ADVERT_SHELL_H_*/
