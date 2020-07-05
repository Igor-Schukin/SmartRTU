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
	//FIXME two times thread calls at start
	
	std::time_t ft = WgHtmlAds::m_GetFileTime();
	if ((ft != 0) && (ft != m_file_time))
	//if ((ft != 0) && (ft != m_file_time)&&(m_file_time!=0))
	{
		m_file_time = ft;
		//printf("%s", asctime(gmtime(&fileTime))); //this is proof why two times thread cals at start
		return true;
	}
	return false;
}


void WgHtmlAds::m_CutyCaptRequest() {

	//remember white spaces are important for cutycapt!!!
	std::string request{ "xvfb-run --server-args=\"-screen 0, 1920x1080x24\" cutycapt  --url=file:"
	+ m_full_path_to_project_exe + "/" + m_local_html_input_file_dest + "/" + m_html_name
	+ " --out=" + m_full_path_to_project_exe + "/" + m_local_ad_path + "/" + m_ad_name
	};

	std::system(request.c_str());

#ifdef DEBUG_THREAD_MSG
	std::cout << "DEBUG_THREAD_MSG:~~~~~~requested CUTYCAPT do its bussines~~~~~~" << '\n';//more logical expxression must be
#endif //DEBUG_THREAD_MSG
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


	m_is_advert_on_screen = false;
	m_stub_displayed_once = false;

	m_advert_pic = nullptr;
	m_file_time=m_GetFileTime();

	//run async cutycapt request
	m_future = std::async(std::launch::async, &WgHtmlAds::m_CutyCaptRequest, this);

#ifdef DEBUG_THREAD_MSG
	std::cout << "DEBUG_THREAD_MSG:~~~~~~LAUNCHED CUTYCAPT THREAD IN CONSTRUCTOR OF WGHTMLADS~~~~~~" << '\n';
#endif //DEBUG_THREAD_MSG

	std::cout << strNow() << "\t" << "WgHtmlsAds widget object was created\n";
}

WgHtmlAds::~WgHtmlAds()
{
	//if something inside delete it
	if (m_advert_pic != nullptr) {
		delete m_advert_pic;
		m_advert_pic = nullptr;
	}
}

bool WgHtmlAds::update() {
	//get status of thread//it actually freezes it for under 1 milisecond to get status of thread
	m_thread_status = m_future.wait_for(std::chrono::milliseconds(0));
	//check if thread finished
	if (m_thread_status == std::future_status::ready) {
		
		//needed if thread done its job 
		if (m_is_advert_on_screen == false) {
			return true;
		}

		//check if file was edited
		if (m_NeedRenew() == true) {

			std::cout << strNow() << "\t" << "Detected what advert must be updated,Cutycapt lauched\n";

			//run Cytycapt stuff in async thread
			m_future = std::async(std::launch::async, &WgHtmlAds::m_CutyCaptRequest, this);

			#ifdef DEBUG_THREAD_MSG
						std::cout << "DEBUG_THREAD_MSG:~~~~~~NEEDRENEW() PASSED AND LAUNCHED CUTYCAPT REQUEST ASYNC THREAD~~~~~~" << '\n';
			#endif //DEBUG_THREAD_MSG

			//in case thread finished fast
			m_is_advert_on_screen = false;
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
		//std::cout << "Thread finished" << std::endl;
		#ifdef DEBUG_THREAD_MSG
				std::cout << "DEBUG_THREAD_MSG:~~~~~~PASSED THREAD STATUS CHECK IN RENDER()~~~~~~" << '\n';
		#endif //DEBUG_THREAD_MSG

		//check if it was already uploaded advert 
		if (m_is_advert_on_screen == false) {
			m_is_advert_on_screen = true;
			m_stub_displayed_once = true;

			#ifdef DEBUG_THREAD_MSG
						std::cout << "DEBUG_THREAD_MSG:~~~~~~LOADED ADVERT PICTURE ~~~~~~" << '\n';
			#endif //DEBUG_THREAD_MSG

			//cleare m_advert_pic
			if (m_advert_pic != nullptr) {
				delete m_advert_pic;
				m_advert_pic = nullptr;
			}

			// if something get bad with loading advert then load stub instead
			try
			{
				//creates new Picture 
				m_advert_pic = new Picture(
					(m_local_ad_path + "/" + m_ad_name).c_str()
				);//create advert 
			}
			catch (...)
			{

				std::cerr << strNow() << "\t" << "Something bad happened  with loading advert, STUB placed instead!!! \n";

				//clean what migth be in m_advert_pic
				if (m_advert_pic != nullptr) {
					delete m_advert_pic;
					m_advert_pic = nullptr;
				}
				m_advert_pic = new Picture(
					(m_local_stub_path + "/" + m_stub_name).c_str()
				);//create advert //take stub in place of advert
			}

			
			m_image_scale_by_width = static_cast<float>(rectClient.width) / static_cast<float>(m_advert_pic->Get_width());
			m_image_scale_by_height = static_cast<float>(rectClient.height) / static_cast<float>(m_advert_pic->Get_height());

			std::cout << strNow() << "\t" << "Advert was placed on the widget screen \n";

			//!!DEBUG STUFF!!
			#ifdef DEBUG_ADVERTS_PRM_SHOW
						std::cout << '\n';
						std::cout << "DEBUG_ADVERTS_PRM_SHOW:~~~~~~INSIDE ADVERT SCOPE~~~~~~" << '\n';
						std::cout << "Pictures original: width -> " << m_advert_pic->Get_width() << " \theigth -> " << m_advert_pic->Get_height() << '\n';
						std::cout << "Pictures scale by: width -> " << m_scale_by_width << " \theight -> " << m_scale_by_height<< '\n';
						std::cout << "WgHtmlAds area     width -> " << rectClient.width << " \theight -> " << rectClient.height << '\n';
						std::cout << '\n';
			#endif //DEBUG_ADVERTS_PRM_SHOW
		}
	}
	else {

		#ifdef DEBUG_THREAD_MSG
				std::cout << "DEBUG_THREAD_MSG:~~~~~~ASYNC THREAD IS STILL  RUNNING INSIDE STUB SCOPE NOW ~~~~~~" << '\n';
		#endif //DEBUG_THREAD_MSG

		//check if it is advert and already uploaded into widget
		//and checks if Stub was once Displayed 
		if ( (m_stub_displayed_once == false)) {
			//m_is_advert_on_screen = true;//change flag what it is not advert uploaded into widget
			m_stub_displayed_once = true; //sets what stub displayed once

			//FIXME 
			//problem appiered i do not understand why derp.png will appier as lines
			//but cnn.png works fine
			//Pi have brain shortage?
			//I run this from my vscode on windows maybe dats why?
			//cleare m_advert_pic

			//delete old stuff inside m_advert_pic
			if (m_advert_pic != nullptr) {
				delete m_advert_pic;
				m_advert_pic = nullptr;
			}
			//probably need try cath this 
			m_advert_pic = new Picture(
				(m_local_stub_path + "/" + m_stub_name).c_str()
			);//create advert //take stub in place of advert

			//calc scales of image
			m_image_scale_by_width = static_cast<float>(rectClient.width) / static_cast<float>(m_advert_pic->Get_width());
			m_image_scale_by_height = static_cast<float>(rectClient.height) / static_cast<float>(m_advert_pic->Get_height());

			std::cout << strNow() << "\t" << "Stub was placed on the widget screen \n";

			//~~~DEBUG STUFF
		#ifdef DEBUG_ADVERTS_PRM_SHOW
					std::cout << '\n';
					std::cout << "DEBUG_ADVERTS_PRM_SHOW:~~~~~~INSIDE STUB SCOPE~~~~~~" << '\n';
					std::cout << "Pictures original: width -> " << m_advert_pic->Get_width() << " \theigth -> " << m_advert_pic->Get_height() << '\n';
					std::cout << "Pictures scale by: width -> " << m_scale_by_width << " \theight -> " << m_image_scale_by_height << '\n';
					std::cout << "WgHtmlAds area     width -> " << rectClient.width << " \theight -> " << rectClient.height << '\n';
					std::cout << '\n';
		#endif //DEBUG_ADVERTS_PRM_SHOW
		}
		else {
			m_is_advert_on_screen = false;
		}
	}

	//render Advert
	m_advert_pic->render(rectClient.left, rectClient.bottom, m_image_scale_by_width, m_image_scale_by_height, 0, 0, 0);

	//~~~~~ render shadows
	WgBackground::RenderOnlyShadows();
}
