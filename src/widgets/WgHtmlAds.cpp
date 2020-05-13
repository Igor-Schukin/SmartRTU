#include "WgHtmlAds.h"



time_t WgHtmlAds::getFileTime()
{
	struct stat buff;
	if (stat(fmt("%s/%s", INPUT_FILE_DEST, INPUT_FILE), &buff) == 0)
		return buff.st_mtime;
	return 0;
}


bool WgHtmlAds::needRenew()
{
	time_t ft = WgHtmlAds::getFileTime();
	if (ft != 0 && ft != fileTime)
	{
		
		fileTime = ft;
		//printf("%s", asctime(gmtime(&fileTime))); //this is proof why two times thread cals at start
		return true;
	}
	return false;
}


void WgHtmlAds::cutyCaptRequest(){
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
	
	//cout<<"\t I am in thread \n";
	
}

WgHtmlAds::WgHtmlAds(int Ax, int Ay, wgMode Amode) : WgBackground(Ax, Ay, Amode)
{
	char buf[PATH_MAX];
	realpath(".",buf); //get full path to exe
	m_FullPath=buf;
	m_HeaderText=config->Get("HEADER_TEXT");//header text
	isShadows=false; //default render of shadows off
	updateTime = 3000;//3 seconds update time
	//run async cutycapt request
	m_Future=std::async(std::launch::async,&WgHtmlAds::cutyCaptRequest,this);
	std::cout << strNow() << "\t"<< "WgHtmlsAds widget object is created\n";

}

WgHtmlAds::~WgHtmlAds()
{
	if(m_HtmlPic){
	delete m_HtmlPic;
	}
}

bool WgHtmlAds::update(){
	//get status of thread
	m_Status = m_Future.wait_for(std::chrono::milliseconds(0));
	//check if thread is still working
	if (m_Status == std::future_status::ready) {
		//std::cout << "Thread finished" << std::endl;
		
		//needed if thread done its job 
		//but need to say render to RENDER advert what thread just did
		if(m_IsAdvertOnScreen==false)return true;

		//check if file need renew
		if(needRenew()==true){
			//run Cytycapt stuff in async thread
			m_Future=std::async(std::launch::async,&WgHtmlAds::cutyCaptRequest,this);
			//printf("I am inside needRenew if \n");
			//in case thread finished fast
			m_IsAdvertOnScreen==false;
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

	
	WgBackground::render(); //if commented header @ block @ is tranperent

	//~~~ render header

	//renderHeader( "Sludinājums" );
	renderHeader(m_HeaderText.c_str());


	// Use wait_for() with zero milliseconds to check thread status.
	m_Status = m_Future.wait_for(std::chrono::milliseconds(0));//get status of thread

	// check if thread finished.
	if (m_Status == std::future_status::ready) {
		//std::cout << "Thread finished" << std::endl;
		//cout<<"real thread"<<'\n';

		//check if it was already uploaded advert 
		if(m_IsAdvertOnScreen==false){
			m_IsAdvertOnScreen=true;

			//cleare m_HtmlPic
			if(m_HtmlPic){
			delete m_HtmlPic;
			m_HtmlPic=NULL;
			}

			m_HtmlPic=new Picture(
				(config->Get("ADVERT_PATH")+"/"+config->Get("ADVERT_NAME")).c_str()
				);//create advert 
			//scale image
			m_ScaleByX = static_cast<float>(rectClient.width) / static_cast<float>(m_HtmlPic->getWidth());//calc scale
	 		m_ScaleByY = static_cast<float>(rectClient.height) / static_cast<float>(m_HtmlPic->getHeight());//calc scale
		}
	}
	else {
		//std::cout<<"zagluska"<<'\n';

		//check if it is advert and already uploaded into widget
		//and checks if Stub was once Displayed 
		if(m_IsAdvertOnScreen==false&& m_StubDisplayedOnce==false){
			m_IsAdvertOnScreen=true;//change flag what it is not advert uploaded into widget
			m_StubDisplayedOnce=true;

			if(m_HtmlPic){
			delete m_HtmlPic;
			m_HtmlPic=NULL;
			}

			//problem appiered i do not understand why derp.png will appier as lines
			//but cnn.png works fine
			//Pi have brain shortage?
			//I run this from my vscode on windows maybe dats why?
			m_HtmlPic=new Picture(
				(config->Get("ADVERT_PATH")+"/"+config->Get("STUB_NAME")).c_str()
				);//create advert //take stub in place of advert
			m_ScaleByX = static_cast<float>(rectClient.width) / static_cast<float>(m_HtmlPic->getWidth());//calc scale
	 		m_ScaleByY = static_cast<float>(rectClient.height) / static_cast<float>(m_HtmlPic->getHeight());//calc scale
			
			//~~~why stringy pic testing tools
			//std::cout<<"scale width "<<m_ScaleByX<<" heigth scale"<<m_ScaleByY<<'\n';
			//std::cout<<" width "<<m_HtmlPic->getWidth()<<" heigth "<<m_HtmlPic->getHeight()<<'\n';
			//with this render litle bit better cat.png
			//m_HtmlPic->render(rectClient.left, rectClient.bottom, m_ScaleByX, m_ScaleByY, 0, 0, 0);//Render image

		}
		else{
			m_IsAdvertOnScreen=false;
		}
	}

	//std::cout<<fileTime<<'\n';
	//render Advert
	m_HtmlPic->render(rectClient.left, rectClient.bottom, m_ScaleByX, m_ScaleByY, 0, 0, 0);//Render image

	//~~~~~ render back shadows
	WgBackground::renderOnlyShadows();
}
