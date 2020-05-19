#include "WgHtmlAds.h"



time_t WgHtmlAds::m_getFileTime()
{
	struct stat buff;
	if (stat(fmt("%s/%s", INPUT_FILE_DEST, INPUT_FILE), &buff) == 0)
		return buff.st_mtime;
	return 0;
}


bool WgHtmlAds::m_needRenew()
{
	time_t ft = WgHtmlAds::m_getFileTime();
	if (ft != 0 && ft != m_file_time)
	{
		
		m_file_time = ft;
		//printf("%s", asctime(gmtime(&fileTime))); //this is proof why two times thread cals at start
		return true;
	}
	return false;
}


void WgHtmlAds::m_cutyCaptRequest(){
	char buf[PATH_MAX];//buf for realpath result PATH_MAX is from <limit.h>

	std::string request{RUN_XVFB_SERVER} ;
	request.append(" cutycapt ");
	request.append("--url=file:");
	//sprintf(buf,"%s/%s",m_FullPath.c_str(),INPUT_FILE_DEST);//writes into buf ((full path to .html) + / + INPUT_FILE)
	//printf("\n Input file dest example -> %s\n\n",buf);
	realpath(INPUT_FILE_DEST,buf);//returns into buf (fullpath from exe + INPUT_FILE_DEST)
	//printf(" in cutycapt %s\n",buf);
	sprintf(buf,"%s/%s",buf,INPUT_FILE);//writes into buf ((full path to .html) + / + INPUT_FILE)
	//printf("\nTested example -> %s\n\n",buf);
	request.append(buf);
	request.append(" --out=");
	realpath(OUTPUT_FILE_DEST,buf);//returns into buf (fullpath from exe + OUTPUT_FILE_DEST)
	//printf("%s\n",buf);
	sprintf(buf,"%s/%s",buf,OUTPUT_FILE);//writes into buf ((full path to .png) + / + INPUT_FILE)
	//printf("%s\n",buf);
	request.append(buf);
	
	//m_OutputFilePath=buf;//asign buf  
	std::system(request.c_str());//run request to Cutycapt do its bussines
	
	#ifdef DEBUG_THREAD_MSG
			std::cout<<"DEBUG_THREAD_MSG:~~~~~~CUTYCAPT THREAD FINISHED~~~~~~"<<'\n';
	#endif //DEBUG_THREAD_MSG
	
}

WgHtmlAds::WgHtmlAds(int Ax, int Ay, wgMode Amode) : WgBackground(Ax, Ay, Amode)
{
	char buf[PATH_MAX];
	realpath(".",buf); //get full path to exe
	m_full_path_to_exe=buf;//sets full path
	m_header_text=config->Get("HEADER_TEXT");//header text
	isShadows=false; //default render of shadows off 
	updateTime = 3000;//sets 3 seconds update time  
	
	bool m_is_advert_on_screen=false; 
    bool m_stub_displayed_once=false;

	Picture *m_advert_pic=nullptr;
	
												
	//run async cutycapt request
	m_future=std::async(std::launch::async,&WgHtmlAds::m_cutyCaptRequest,this);

	#ifdef DEBUG_THREAD_MSG
		std::cout<<"DEBUG_THREAD_MSG:~~~~~~LAUNCHED CUTYCAPT THREAD IN CONSTRUCTOR OF WGHTMLADS~~~~~~"<<'\n';
	#endif //DEBUG_THREAD_MSG

	std::cout << strNow() << "\t"<< " WgHtmlsAds widget object is created\n";

}

WgHtmlAds::~WgHtmlAds()
{
	//if something inside delete it
	if(m_advert_pic!=nullptr){
		delete m_advert_pic;
		m_advert_pic=nullptr;
	}
}

bool WgHtmlAds::update(){
	//get status of thread
	m_status = m_future.wait_for(std::chrono::milliseconds(0));
	//check if thread is still working
	if (m_status == std::future_status::ready) {
		//std::cout << "Thread finished" << std::endl;

		//HERE MUST BE THREAD INFO???????

		//needed if thread done its job 
		//but need to say render to RERENDER advert what thread just did
		if(m_is_advert_on_screen==false)return true;

		//check if file need renew
		if(m_needRenew()==true){
			//run Cytycapt stuff in async thread
			m_future=std::async(std::launch::async,&WgHtmlAds::m_cutyCaptRequest,this);

			#ifdef DEBUG_THREAD_MSG
				std::cout<<"DEBUG_THREAD_MSG:~~~~~~NEEDRENEW() PASSED AND LAUNCHED CUTYCAPT REQUEST ASYNC THREAD~~~~~~"<<'\n';
			#endif //DEBUG_THREAD_MSG

			//in case thread finished fast
			m_is_advert_on_screen==false;
			return true;
		}
		else{
			return false;
		}
	}
	else{
		return false;
	}
}

void WgHtmlAds::render()
{

	WgBackground::render(); //if commented @ header and advert  block @ is tranperent

	//~~~ render header
	renderHeader(m_header_text.c_str());


	// Use wait_for() with zero milliseconds to check thread status.
	m_status = m_future.wait_for(std::chrono::milliseconds(0));//get status of thread

	// check if thread finished.
	if (m_status == std::future_status::ready) {
		//std::cout << "Thread finished" << std::endl;
		#ifdef DEBUG_THREAD_MSG
			std::cout<<"DEBUG_THREAD_MSG:~~~~~~PASSED THREAD STATUS CHECK IN RENDER()~~~~~~"<<'\n';
		#endif //DEBUG_THREAD_MSG

		//check if it was already uploaded advert 
		if(m_is_advert_on_screen==false){
			m_is_advert_on_screen=true;

			//cleare m_advert_pic
			if(m_advert_pic!=nullptr){
				delete m_advert_pic;
				m_advert_pic=nullptr;
			}

			//creates new Picture 
			m_advert_pic=new Picture(
				(config->Get("ADVERT_PATH")+"/"+config->Get("ADVERT_NAME")).c_str()
				);//create advert 

			//calc scales of image
			m_scale_by_x = static_cast<float>(rectClient.width) / static_cast<float>(m_advert_pic->getWidth());
	 		m_scale_by_y = static_cast<float>(rectClient.height) / static_cast<float>(m_advert_pic->getHeight());
			 
			 
			 //!!DEBUG STUFF!!
			#ifdef DEBUG_ADVERTS_PRM_SHOW
				std::cout<<'\n';
				std::cout<<"DEBUG_ADVERTS_PRM_SHOW:~~~~~~INSIDE ADVERT SCOPE~~~~~~"<<'\n';
				std::cout<<"Pictures original: width -> "<<m_advert_pic->getWidth()<<" \theigth -> "<<m_advert_pic->getHeight()<<'\n';
				std::cout<<"Pictures scale by: width -> "<<m_scale_by_x<<" \theight -> "<<m_scale_by_y<<'\n';
				std::cout<<"WgHtmlAds area     width -> "<<rectClient.width<<" \theight -> "<<rectClient.height<<'\n';
				std::cout<<'\n';
			#endif //DEBUG_ADVERTS_PRM_SHOW

		}
	}
	else {

		#ifdef DEBUG_THREAD_MSG
			std::cout<<"DEBUG_THREAD_MSG:~~~~~~INSIDE STUB SCOPE~~~~~~"<<'\n';
		#endif //DEBUG_THREAD_MSG

		//check if it is advert and already uploaded into widget
		//and checks if Stub was once Displayed 
		if(m_is_advert_on_screen==false&& m_stub_displayed_once==false){
			m_is_advert_on_screen=true;//change flag what it is not advert uploaded into widget
			m_stub_displayed_once=true; //sets what stub displayed once

			//problem appiered i do not understand why derp.png will appier as lines
			//but cnn.png works fine
			//Pi have brain shortage?
			//I run this from my vscode on windows maybe dats why?
			m_advert_pic=new Picture(
				(config->Get("ADVERT_PATH")+"/"+config->Get("STUB_NAME")).c_str()
				);//create advert //take stub in place of advert
				
			//calc scales of image
			m_scale_by_x = static_cast<float>(rectClient.width) / static_cast<float>(m_advert_pic->getWidth());
	 		m_scale_by_y = static_cast<float>(rectClient.height) / static_cast<float>(m_advert_pic->getHeight());
			

			//~~~DEBUG STUFF
			#ifdef DEBUG_ADVERTS_PRM_SHOW
				std::cout<<'\n';
				std::cout<<"DEBUG_ADVERTS_PRM_SHOW:~~~~~~INSIDE STUB SCOPE~~~~~~"<<'\n';
				std::cout<<"Pictures original: width -> "<<m_advert_pic->getWidth()<<" \theigth -> "<<m_advert_pic->getHeight()<<'\n';
				std::cout<<"Pictures scale by: width -> "<<m_scale_by_x<<" \theight -> "<<m_scale_by_y<<'\n';
				std::cout<<"WgHtmlAds area     width -> "<<rectClient.width<<" \theight -> "<<rectClient.height<<'\n';
				std::cout<<'\n';
			#endif //DEBUG_ADVERTS_PRM_SHOW
		}
		else{
			m_is_advert_on_screen=false;
		}
	}
	
	//render Advert
	m_advert_pic->render(rectClient.left, rectClient.bottom, m_scale_by_x, m_scale_by_y, 0, 0, 0);

	//~~~~~ render shadows
	WgBackground::renderOnlyShadows();
}
