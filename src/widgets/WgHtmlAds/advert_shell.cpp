#include"advert_shell.h"




AdvertShell::~AdvertShell() {
    if(advert_picture_!=nullptr){
        delete advert_picture_;
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
    advert_pid_txt_name_=advert_picture_name_+".txt";

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
std::system(
    ("xvfb-run -a --server-args=\"-screen 0, 1920x1080x24\" cutycapt --url="+
    advert_url_ +"--out="+adverts_dest_+'/'+advert_picture_name_+
    " & echo $! >"+adverts_dest_+'/'+advert_pid_txt_name_).c_str()
    );
}
