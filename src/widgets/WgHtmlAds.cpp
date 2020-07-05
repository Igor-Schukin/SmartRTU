#include "WgHtmlAds.h"

//C
//#include <dirent.h> // in cpp ??? probably need to remove
#include <sys/stat.h> // /* stat */ function
#include <sys/types.h>//needed for stat fucntion

//C++
#include <iostream> // /*cout*/
#include <chrono> /*for milisecons for thread stuff */  
#include <cstdlib>// /*realpath*/ funtion for cutycapt also needed PATH_MAX from limits.h
#include <climits> /* PATH_MAX */ //
//A11Y libs

//own headers
#include "Engine.h"// from here we need only "fmt" stuff 
#include "Timer.h" ///* strNow()*/
//#include "desktop.h" //well i commented this and all is still working

#include "configurator.h" //config 


std::time_t WgHtmlAds::m_GetFileTime()
{
	struct stat buff;
	//check if it can touch file and read last edit time of file
	if (stat(
		fmt(
			"%s/%s", m_local_html_input_file_dest.c_str(),
			m_html_name.c_str()
		)
		, &buff) == 0) //fmt is not in standart library of C or C++
		return buff.st_mtime;
	return 0;
}


bool WgHtmlAds::m_NeedRenew()
{
	std::time_t ft = WgHtmlAds::m_GetFileTime();
	if ((ft != 0) && (ft != m_file_time))
	{
		m_file_time = ft;
		return true;
	}
	return false;
}

void WgHtmlAds::m_CleanPicture()
{
	if (m_advert_pic != nullptr) {
		delete m_advert_pic;
		m_advert_pic = nullptr;
	}
}


void WgHtmlAds::m_CutyCaptRequest() {

	//remember white spaces are important for cutycapt!!!
	std::string request{ "xvfb-run --server-args=\"-screen 0, 1920x1080x24\" cutycapt  --url=file:"
	+ m_full_path_to_project_exe + "/" + m_local_html_input_file_dest + "/" + m_html_name
	+ " --out=" + m_full_path_to_project_exe + "/" + m_local_ad_path + "/" + m_ad_name
	};

	std::system(request.c_str());


}

WgHtmlAds::WgHtmlAds(int Ax, int Ay, wgMode Amode) 
: WgBackground(Ax, Ay, Amode)
{
	shadows_on = false; //default render of shadows off 
	int update_time;
	config->Get("ADVERT_UPDATE_TIME", update_time); //converts string into int
	
	if (update_time <= 0) {
		m_widget_update_time = 3000;//sets 3 seconds update time  //int data type
	}
	else {
		m_widget_update_time = (update_time * 1000);//sets update time in seconds
	}

	//string part
	config->Get("HEADER_TEXT", m_header_text);
	// .html part
	config->Get("ADVERT_INPUT_FILE_DEST", m_local_html_input_file_dest);
	config->Get("ADVERT_INPUT_FILE", m_html_name);
	//advert part
	config->Get("ADVERT_PATH", m_local_ad_path);
	config->Get("ADVERT_NAME", m_ad_name);
	//stub part
	config->Get("ADVERT_PATH", m_local_stub_path);// probably need diferent prm in config than ADVERT_PATH...
	config->Get("ADVERT_STUB_NAME", m_stub_name);


	char buff[PATH_MAX];
	realpath(".", buff); //get full path to exe
	m_full_path_to_project_exe = buff;//sets full path


	m_advert_on_screen = false;

	m_advert_pic = nullptr;
	m_file_time=m_GetFileTime();

	//run async cutycapt request
	m_future = std::async(std::launch::async, &WgHtmlAds::m_CutyCaptRequest, this);



	std::cout << strNow() << "\t" << "WgHtmlsAds widget object was created\n";
}

WgHtmlAds::~WgHtmlAds()
{
	this->m_CleanPicture();
}

bool WgHtmlAds::update() {
	//get status of thread//it actually freezes it for under 1 milisecond to get status of thread
	m_thread_status = m_future.wait_for(std::chrono::milliseconds(0));
	
	//check if thread finished
	if (m_thread_status == std::future_status::ready) {
		
		//needed if thread done its job 
		if (m_advert_on_screen == false) {
			return true;
		}
		else if (m_NeedRenew() == true) {
			std::cout << strNow() << "\t" << "Detected what advert must be updated,Cutycapt lauched\n";
			
			m_future = std::async(std::launch::async, &WgHtmlAds::m_CutyCaptRequest, this);
			m_advert_on_screen = false;

			return true;
		}
		else {
			return false;
		}
	}
	else {
		return false;
	}
}

void WgHtmlAds::render()
{
	WgBackground::render(); //if commented @ header and advert  block @ is tranperent

	//~~~ render header
	RenderHeader(m_header_text.c_str());

	// Use wait_for() with zero milliseconds to check thread status.
	m_thread_status = m_future.wait_for(std::chrono::milliseconds(0));//get status of thread

	// check if thread finished.
	if (m_thread_status == std::future_status::ready) {
		std::cout << strNow() << "\t" << "Cutycapt finished its work\n";
		if(m_advert_on_screen!=true){
			//std::cout << strNow() << "\t" << "Cutycapt finished its work\n";
			this->m_CleanPicture();
			try
			{
				m_advert_pic = new Picture(
					(m_local_ad_path + "/" + m_ad_name).c_str()
				);
			}
			catch (...)
			{
				std::cerr << strNow() << "\t" << "Something bad happened  with loading advert, STUB placed instead!!! \n";
				this->m_CleanPicture();
				//stub placed instead
				m_advert_pic = new Picture(
					(m_local_stub_path + "/" + m_stub_name).c_str()
				);
			}

			m_image_scale_by_width = static_cast<float>(rectClient.width) / static_cast<float>(m_advert_pic->Get_width());
			m_image_scale_by_height = static_cast<float>(rectClient.height) / static_cast<float>(m_advert_pic->Get_height());

			m_advert_on_screen=true;
			std::cout << strNow() << "\t" << "Advert was placed on the widget screen \n";
		
		}
	}
	else {
		if(m_advert_pic==nullptr){
			m_advert_pic = new Picture(
				(m_local_stub_path + "/" + m_stub_name).c_str()
			);
			m_image_scale_by_width = static_cast<float>(rectClient.width) / static_cast<float>(m_advert_pic->Get_width());
			m_image_scale_by_height = static_cast<float>(rectClient.height) / static_cast<float>(m_advert_pic->Get_height());

			std::cout << strNow() << "\t" << "Stub was placed on the widget screen \n";
		}
	}

	//render Advert
	m_advert_pic->render(rectClient.left, rectClient.bottom, m_image_scale_by_width, m_image_scale_by_height, 0, 0, 0);

	//~~~~~ render shadows
	WgBackground::RenderOnlyShadows();
}
