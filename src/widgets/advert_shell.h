#include<string>
#include"Picture.h"
#include<ctime>

class AdvertShell{
public:

void RenderAdvert();

AdvertShell(int rect_left,int rect_top,
            int screen_width,int screen_height,
            const std::string&pic_path,const std::string&pic_name,
            std::time_t show_time
            );
~AdvertShell();

std::time_t Get_show_time(){return show_time_; }


private:

int rect_left_;
int rect_top_;

int screen_width_;
int screen_height_;

std::string advert_path_;
std::string advert_name_;

std::time_t show_time_;



//struct{float width;float height}ImageScale;
//struct{int width;int height}Display;
float picture_scale_width_;
float picture_scale_height_;


Picture *advert_;

};