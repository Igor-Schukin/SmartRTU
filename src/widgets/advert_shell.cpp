#include"advert_shell.h"




AdvertShell::~AdvertShell() {
    if(advert_!=nullptr){
        delete advert_;
    }
}

AdvertShell::AdvertShell(int rect_left, int rect_top, 
                         int screen_width, int screen_height, 
                         const std::string&pic_path, const std::string&pic_name,
                         std::time_t show_time)
:rect_left_(rect_left),rect_top_(rect_top),
screen_width_(screen_width),screen_height_(screen_height),
advert_path_(pic_path),advert_name_(pic_name),
show_time_(show_time)
{
    advert_=nullptr;
    advert_=new Picture((advert_path_ + "/" + advert_name_).c_str());

          
      picture_scale_width_ = static_cast<float>(screen_width_) /
                               static_cast<float>(advert_->Get_width());
      picture_scale_height_ = static_cast<float>(screen_height_) /
                                static_cast<float>(advert_->Get_height());
}

void AdvertShell::RenderAdvert() {
    if(advert_!=nullptr){
        advert_->render(rect_left_, rect_top_,
                       picture_scale_width_, picture_scale_height_, 0, 0,
                       0);    
    }
}
