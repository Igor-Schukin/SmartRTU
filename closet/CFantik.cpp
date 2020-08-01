#include"CFantik.h"



#include <thread>
#include <future>
#include <chrono> //for miliseconds
#include <string>


Fantik::Fantik(int a_rect_client_left,int a_rect_client_bottom,
    int a_widget_area_width,int a_widget_area_height,
    const std::string &a_realpath,const std::string &a_advert_dest,
    const std::string &a_advert_url,const std::string& a_header_text,
    std::time_t a_start_date,std::time_t a_end_date,
    int a_advert_show_time,bool is_hidden 
)
:rect_client_left_(a_rect_client_left),
    rect_client_bottom_(a_rect_client_bottom),
    display_width_(a_widget_area_width),
    display_height_(a_widget_area_height),
    project_root_path_(a_realpath),
    advert_dest_(a_advert_dest),
    advert_url_(a_advert_url),
    header_text_(a_header_text),
    start_date_(a_start_date),
    end_date_(a_end_date),
    advert_show_time_(a_advert_show_time),
    hidden_(is_hidden)
{
	advert_pic_=nullptr;
		int pos = a_advert_url.length();
		for (auto i = a_advert_url.crbegin(); i < a_advert_url.crend(); ++i)
		{
			if (*i == '/' || *i == '&' || *i == '\\' || *i == '='||*i=='?'){
				break;
			}
			pos--;
		}
		advert_picture_name_ = a_advert_url.substr(pos)+".png";

    //run async thread
    if(is_hidden!=true){
        future_ = std::async(std::launch::async, &Fantik::CutyCaptRequest_, this);
    }
}

Fantik::~Fantik(){
    this->CleanPicture_();
}

void Fantik::CheckEditTime(int a_my_time)
{

	/*if (a_my_time > this->file_last_edit_time_ && this->IsThreadReady() == true) {
		this->file_last_edit_time_ = a_my_time;
		this->ForceTransformSelf(); //it will be async as ussual

	}*/
}

bool Fantik::IsThreadReady(){
    thread_status_ = future_.wait_for(std::chrono::milliseconds(0));
    
    if(thread_status_ == std::future_status::ready){
        return true;
    }
    else{
        return false;
    }

}

bool Fantik::ForceTransformSelf(){
    thread_status_ = future_.wait_for(std::chrono::milliseconds(0));
    
    if(thread_status_ == std::future_status::ready){
        future_ = std::async(std::launch::async, 
                            &Fantik::CutyCaptRequest_, 
                            this);
        return true;
    }
    else{
        return false;
    }
    return false;
}

void Fantik::CutyCaptRequest_(){


     std::system(("xvfb-run --server-args=\"-screen 0, 1920x1080x24\" "
                      "cutycapt  --url=" + advert_url_+
                      " --out=" + project_root_path_ + "/" +
                      advert_dest_ + "/" + advert_picture_name_).c_str()
              );

}



void Fantik::Set_advert_url(const std::string & a_advert_url)
{
	advert_url_.clear();
	advert_url_ = a_advert_url;
}


void  Fantik::CleanPicture_(){
    if (advert_pic_!=nullptr) {
        delete advert_pic_;
        advert_pic_ = nullptr;
    }
}

void Fantik::RenderAdvert(){



   /* if(this->IsThreadReady()&&advert_pic_==nullptr){

         advert_pic_ =
            new Picture((advert_dest_ + "/" + advert_picture_name_).c_str());
      

        picture_width_scale_ = static_cast<float>(display_width_) /
                               static_cast<float>(advert_pic_->Get_width());
        picture_height_scale_ = static_cast<float>(display_height_) /
                                static_cast<float>(advert_pic_->Get_height());
        
         advert_pic_->render(rect_client_left_, rect_client_bottom_,
                       picture_width_scale_, picture_height_scale_, 
                       0, 0,0);
    }*/
    if(advert_pic_){
        advert_pic_->render(rect_client_left_, rect_client_bottom_,
                       picture_width_scale_, picture_height_scale_, 
                       0, 0,0);
        std::cout<<"Picture is rendered\n";
    }
    else{
        

        advert_pic_ =new Picture((advert_dest_ + "/" + advert_picture_name_).c_str());
      

        picture_width_scale_ = static_cast<float>(display_width_) /
                               static_cast<float>(advert_pic_->Get_width());
        picture_height_scale_ = static_cast<float>(display_height_) /
                                static_cast<float>(advert_pic_->Get_height());

    }
    // render Advert
    /*else{
        advert_pic_->render(rect_client_left_, rect_client_bottom_,
                       picture_width_scale_, picture_height_scale_, 
                       0, 0,0);
    }
    */
}