#include "WgHtmlAds.h"



time_t WgHtmlAds::getFileTime()
{
	struct stat buff;
	if (stat(fmt("%s/%s", INPUT_FILE_DEST, INPUT_FILE), &buff) == 0)
		return buff.st_mtime;
	return 0;
}

bool WgHtmlAds::renewFlag()
{
	
	struct dirent **namelist;
	int n = scandir(INPUT_FILE_DEST, &namelist, NULL, alphasort);
	if (n < 0)
		perror("scandir");
	else
		while (n--)
		{
			if (strcmp(namelist[n]->d_name, FLAG_FILE_NAME) == 0)
				return true;
		}
	return false;
}

bool WgHtmlAds::needRenew()
{
	time_t ft = WgHtmlAds::getFileTime();
	if (ft != 0 && ft != fileTime || renewFlag())
	{
		system(fmt("rm -rf %s/%s", INPUT_FILE_DEST, FLAG_FILE_NAME));
		fileTime = ft;
		return true;
	}
	return false;
}


void WgHtmlAds::cutyCaptRequest(){
	char buf[PATH_MAX];//buf for realpath result PATH_MAX is from <limit.h>

	std::string request{RUN_XVFB_SERVER} ;
	request.append(" cutycapt ");
	request.append("--url=file:");
	realpath(INPUT_FILE_DEST,buf);//returns into buf (fullpath from exe + INPUT_FILE_DEST)
	sprintf(buf,"%s/%s",buf,INPUT_FILE);//writes into buf ((full path to .html) + / + INPUT_FILE)
	//printf("%s\n",buf);
	request.append(buf);
	request.append(" --out=");
	realpath(OUTPUT_FILE_DEST,buf);//returns into buf (fullpath from exe + OUTPUT_FILE_DEST)
	//printf("%s\n",buf);
	sprintf(buf,"%s/%s",buf,OUTPUT_FILE);//writes into buf ((full path to .png) + / + INPUT_FILE)
	//printf("%s\n",buf);
	request.append(buf);
	
	m_OutputFilePath=buf;//asign buf  
	std::system(request.c_str());//run request to Cutycapt do its bussines
	
	//cout<<"\t I am in thread \n";
	
}

WgHtmlAds::WgHtmlAds(int Ax, int Ay, wgMode Amode) : WgBackground(Ax, Ay, Amode)
{
	updateTime = 3000;//3 seconds update time
	//run async cutycapt request
	future=std::async(std::launch::async,&WgHtmlAds::cutyCaptRequest,this);
	std::cout << strNow() << "\t"<< "WhHtmlsAds widget object is created\n";
}

WgHtmlAds::~WgHtmlAds()
{
	if(m_HtmlPic){
	delete m_HtmlPic;
	}
	if(m_OutputFilePath){
	delete m_OutputFilePath;
	}
	
}

bool WgHtmlAds::update(){
	//get status of thread
	status = future.wait_for(std::chrono::milliseconds(0));
	//check if thread is still working
	if (status == std::future_status::ready) {
		//std::cout << "Thread finished" << std::endl;
		
		//printf("passed check on status\n");
		if(m_alreadyUploadedPic==false)return true;//do not know how to explain but needed stuff

		//check if file need renew
		if(needRenew()==true){
			future=std::async(std::launch::async,&WgHtmlAds::cutyCaptRequest,this);
			m_alreadyUploadedPic=true;//also needed stuf what i can not explan
			//printf("update\n");
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

	//std::cout<<"Inside WG render"<<"\n";

	// Use wait_for() with zero milliseconds to check thread status.
	status = future.wait_for(std::chrono::milliseconds(0));//get status of thread

	// check if thread finished.
	if (status == std::future_status::ready) {
		//std::cout << "Thread finished" << std::endl;
		//cout<<"real thread"<<'\n';

		//check if it was already uploaded advert 
		if(m_alreadyUploadedPic==false){
			m_alreadyUploadedPic=true;

			delete m_HtmlPic;
			m_HtmlPic=NULL;

			m_HtmlPic=new Picture(m_OutputFilePath);//create advert //btw can also use local path to file
			//scale image
			m_ScaleByX = static_cast<float>(rectClient.width) / static_cast<float>(m_HtmlPic->getWidth());//calc scale
	 		m_ScaleByY = static_cast<float>(rectClient.height) / static_cast<float>(m_HtmlPic->getHeight());//calc scale
		}
	}
	else {
		//cout<<"zagluska"<<'\n';

		//check if it is advert and already uploaded into widget
		if(m_alreadyUploadedPic==true){
			m_alreadyUploadedPic=false;//change flag what it is not advert uploaded into widget

			delete m_HtmlPic;
			m_HtmlPic=NULL;

			m_HtmlPic=new Picture("res/tmp/cnn.png");
			m_ScaleByX = static_cast<float>(rectClient.width) / static_cast<float>(m_HtmlPic->getWidth());//calc scale
	 		m_ScaleByY = static_cast<float>(rectClient.height) / static_cast<float>(m_HtmlPic->getHeight());//calc scale
		}
	}

	//render pic
	m_HtmlPic->render(rectClient.left, rectClient.bottom, m_ScaleByX, m_ScaleByY, 0, 0, 0);//Render image

	//~~~~~ render back shadows
	WgBackground::renderOnlyShadows();
}
