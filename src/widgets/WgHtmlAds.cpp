#include "WgHtmlAds.h"

WgHtmlAds::WgHtmlAds(int Ax, int Ay, wgMode Amode) : WgBackground(Ax, Ay, Amode)
{
	std::cout << strNow() << "\t"<< "WhHtmlsAds widget object is created\n";
	std::string request =CUTYCAPT_REQUEST ;
	//inside the Xvfb X server, configured with a root
	// window of 1024 by 768 pixels and a color depth
	// of 24 bits.

	std::system(request.c_str());			   //run request in command line
	HtmlPic = new Picture("res/tmp/temp.png"); //upload newly created pic
											   //printf("width: %i, height: %i\n", HtmlPic->getWidth(), HtmlPic->getHeight());
}

WgHtmlAds::~WgHtmlAds()
{
	delete HtmlPic;
}
void WgHtmlAds::render()
{

	//~~~ render background

	//WgBackground::render();

	//calc scale of temp.png pic to fit into witdget area
	float Dx = static_cast<float>(rectClient.width) / static_cast<float>(HtmlPic->getWidth());
	float Dy = static_cast<float>(rectClient.height) / static_cast<float>(HtmlPic->getHeight());
	std::cout << "Dx-> " << Dx << " Dy-> " << Dy << std::endl;
	HtmlPic->render(rectClient.left, rectClient.bottom, Dx, Dy, 0, 0, 0);

	std::cout << "w->" << rectClient.width << " h->" << rectClient.height << std::endl;
	std::cout << "HtmlPic->getWidth()->" << HtmlPic->getWidth() << " HtmlPic->getHeight()->" << HtmlPic->getHeight() << std::endl;
	//~~~~~ render back shadows
	WgBackground::renderOnlyShadows();
}
