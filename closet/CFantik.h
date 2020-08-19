#pragma once
#include <thread>
#include <future>

#include <iostream>

#include<fstream>


#include <string>
#include<ctime>

#include "Picture.h"//Picture type


class Fantik
{
public:


	void RenderAdvert();
	//true if it started cutycapt request false thread is still doing its stuff
	bool ForceTransformSelf();

	bool IsThreadReady();//check if Cutycapt thread is ready or not //ready means its finished //true if ready

	//if a_new_time is diferent from edit_time if so then Force update self
	void CheckEditTime(int a_my_time);

	//setter/getters

	int Get_advert_show_time() { return this->advert_show_time_; }
	int Get_start_date() { return start_date_; }
	int Get_end_date() { return end_date_; }

	float Get_picture_width_scale() { return picture_width_scale_; }
	void Set_picture_width_scale(float a_picture_width_scale) { this->picture_width_scale_ = a_picture_width_scale; }

	float Get_picture_height_scale() { return picture_height_scale_; }
	void Set_picture_height_scale(float a_heght_scale) { this->picture_height_scale_ = a_heght_scale; }

	bool IsHidden() { return this->hidden_; }
	void Set_hidden(bool a_state) { this->hidden_ = a_state; }

	void Set_header_text(const std::string&a_header_text) {
		this->header_text_.clear();
		this->header_text_ = a_header_text;
	}

	void Set_advert_url(const std::string& a_advert_url);

	//and what aboout rule of 5???
	//Rule of 5 means if you are usising own destructor || constructor|| copy constructor you need to implement all of them
	//rule 5 means same but you must also add assigment constructor and anotherone what i forget name of it

	//maybe need more reasoning Constructor for this
	
	Fantik(int a_rect_client_left,int a_rect_client_bottom,
    int a_widget_area_width,int a_widget_area_height,
    const std::string &a_realpath,const std::string &a_advert_dest,
    const std::string &a_advert_url,const std::string& a_header_text,
    std::time_t a_start_date,std::time_t a_end_date,
    int a_advert_show_time,bool is_hidden 
		);
	~Fantik();
private:

	void CutyCaptRequest_();//run cutycapt request

	void CleanPicture_();// cleans what inside advert_pic_ and sets to nullptr



	//position where to draw advert
	int rect_client_left_;
	int rect_client_bottom_;

	int display_width_;
	int display_height_;
	
	std::string project_root_path_;//stroes full path to exe//neded for cutycapt
	std::string advert_dest_;//where picture will be stored


	std::string advert_url_;
	std::string header_text_;

	std::time_t start_date_;
	std::time_t end_date_;

	int advert_pos_;//position where fantik must be placed into  list

	std::time_t advert_show_time_;//how long to show on screen

	bool hidden_;

	float picture_width_scale_ = 1;
	float picture_height_scale_ = 1;

	std::string advert_picture_name_;//its name //what about its name its url? or urls part from end untill matches first slash?

	 // last time when file was edited 
	// run CutyCaptRequest and change file_time to file_time in json if time do not match else do nothing
	std::time_t file_last_edit_time_ = 0; 


	//thread stuff
	std::future<void> future_; // is handle actualy object  of  new async thread 
 	// stored status of thread //probably can avoid it
	std::future_status thread_status_; 

	Picture *advert_pic_;

};