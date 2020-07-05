#include "WgForecast.h"


#include <curl/curl.h>

#include <iostream>/*cout*/
#include <string>

#include "Timer.h"/*strNow()*/
#include "desktop.h"/*desktop obj*/
#include "CPicturesStorage.h"/*pict obj*/
#include "CFontStorage.h"/*font obj*/
#include "configurator.h"/*config*/

WgForecast::WgForecast(int Ax, int Ay, wgMode Amode) 
: WgBackground(Ax, Ay, Amode)
{
	updateTime = 60 * 60 * 1000; // 1 hour
	m_weather_icon_picture = nullptr;
	m_weather_icon_name = "";

	//get destination of weather icon
	config->Get("PIC_WEATHER_ICONS_PATH",m_weather_icons_path);
	config->Get("BASE_FONT_NAME",m_base_font_name);

	isConnection = false;

	strcpy(tempDegree, "");
	strcpy(windSpeed, "");
	windDegree = 0;
	std::cout<<strNow()<<"\tWgForecast widget object was created\n";
}

WgForecast::~WgForecast()
{
	if (m_weather_icon_picture)
		delete m_weather_icon_picture;
	std::cout<<strNow()<<"\tWgForecast widget object was deleted\n";
}

size_t WgForecast::m_WriteCallback(void *contents, size_t size, size_t nmemb, void *userp) //???
{
	((std::string *)userp)->append((char *)contents, size * nmemb); // ???
	return size * nmemb;											// ???
}

void WgForecast::m_GetWeatherFromWeb(const char site[], json &weatherData)
{
	CURL *curl;				// object CURL tipa
	std::string readBuffer; //буффур куда будем записывать принятые данные
	CURLcode res;
	static char errorBuffer[CURL_ERROR_SIZE]; //объявляем буфер, для хранения возможной ошибки, размер определяется в самой библиотеке
	curl = curl_easy_init();				  // curl initialization
	if (curl)								  //проверяем
	{
		//задаем все необходимые опции
		curl_easy_setopt(curl, CURLOPT_ERRORBUFFER, errorBuffer);	  //определяем, куда выводить ошибки
		curl_easy_setopt(curl, CURLOPT_URL, site);					  //задаем опцию - получить страницу по адресу site
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, m_WriteCallback); //указываем функцию обратного вызова для записи получаемых данных
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);		  //указываем куда записывать принимаемые данные
		res = curl_easy_perform(curl);								  //запускаем выполнение задачи
		if (res == CURLE_OK)
		{
			isConnection = true;
			auto buf = json::parse(readBuffer);
			weatherData = buf;
			std::cout<<strNow()<<"\tNew current weather state was received\n";
		}
		else
		{
			isConnection = false;
			std::cerr<<strNow()<<"\tError of current weather state receiving!!!\n";
		}
	}
	curl_easy_cleanup(curl); //выполняем обязательное завершение сессии
}

bool WgForecast::update()
{
	json weatherData;
	m_GetWeatherFromWeb(CURRENT_WEATHER_URL, weatherData);

	if (isConnection && weatherData["main"]["temp"].is_number())
	{
		int bufTemp = weatherData["main"]["temp"];
		sprintf(tempDegree, "%+d°", bufTemp);
	}
	else
		sprintf(tempDegree, "---");

	if (isConnection && weatherData["wind"]["deg"].is_number())
	{
		windDegree = weatherData["wind"]["deg"];
		float bufSpeed = weatherData["wind"]["speed"];
		sprintf(windSpeed, "%.0f m/s", bufSpeed);
	}
	else
	{
		sprintf(windSpeed, "---");
		windDegree = 0;
	}

	//~~~ load weather icon

	if (isConnection && weatherData["weather"][0]["icon"].is_string())
	{
		std::string iconName = weatherData["weather"][0]["icon"];
		if (iconName != m_weather_icon_name)
		{
			if (m_weather_icon_picture)
				delete m_weather_icon_picture;
			m_weather_icon_picture = new Picture(
				(m_weather_icons_path+"/"+ iconName + ".png").c_str()
									);
			m_weather_icon_name = iconName;
			std::cout<<strNow()<<"\tNew weather icon was loaded \n";
		}
	}
	else
	{
		if (m_weather_icon_picture){
			delete m_weather_icon_picture;
		}
		m_weather_icon_picture = nullptr;
	}

	return true;
}

void WgForecast::m_RenderMode1()
{
	RenderHeader(tempDegree);
}

void WgForecast::m_RenderMode2()
{
	float field = rectClient.width * 0.07;

	//~~ weather icon

	int iw = 0, ih = 0;
	if (m_weather_icon_picture)
	{
		float is = (float)rectClient.height * 1.0 / m_weather_icon_picture->getHeight();
		iw = m_weather_icon_picture->getWidth() * is;
		ih = m_weather_icon_picture->getHeight() * is;
		m_weather_icon_picture->render(
			rectClient.left + field,
			rectClient.bottom + (rectClient.height - ih) / 2,
			is, is, 0, 0, 0);
	}

	//~~ wind arrow

	float as = (float)rectClient.height * 0.35 / PicStorage->Arrow->getHeight();
	int aw = PicStorage->Arrow->getWidth() * as * 1.75; // 1.4 = sqrt(2)
	int ah = PicStorage->Arrow->getHeight() * as;
	PicStorage->Arrow->render(
		rectClient.right - aw - field,
		rectClient.bottom + (rectClient.height - ah) / 2,
		as, as, 0, 0,
		-windDegree);

	//~~~ wind speed

	setTextColor(clHaki);
	TFont *font = FontStorage->getFont(
		const_cast<char *>(m_base_font_name.c_str())
		);
	font->SetSize(desktop->rowHeight / 3);
	int ww = (int)font->TextWidth(windSpeed);
	int wh = (int)font->TextHeight();
	font->TextMid(
		windSpeed,
		rectClient.left + iw + (rectClient.width - iw - aw) / 2,
		rectClient.bottom + (rectClient.height - wh) / 2);
}

void WgForecast::m_RenderMode3() // need to debug
{
	/*
	FontStorage->getFont((char*)"arialBold")->SetSize(desktop->rowHeight/5);
	FontStorage->getFont((char*)"arialBold")->TextMid("Veišs:", rectClient.left + (desktop->colWidth/2),
		rectClient.top - desktop->rowHeight - (desktop->rowHeight/5/2));
	setTextColor(color);
	FontStorage->getFont((char*)"arialBold")->SetSize(desktop->rowHeight/2.8);
	FontStorage->getFont((char*)"arialBold")->TextMid(windSpeed, rectClient.left + (desktop->colWidth/2.5),
		rectClient.top - desktop->rowHeight - desktop->rowHeight/16*11);
	PicStorage->Arrow->render(rectClient.left + (desktop->colWidth/1.3), rectClient.top - desktop->rowHeight - desktop->rowHeight/1.4, 1, 1, 0,0,-windDegree);
	*/
}

void WgForecast::render()
{
	if (isConnection)
	{
		WgBackground::render();
		switch (mode)
		{
		case md1x1:
		{
			m_RenderMode1();
			break;
		}
		case md1x2:
		{
			m_RenderMode1();
			m_RenderMode2();
			break;
		}
		case md1x3:
		{
			m_RenderMode1();
			m_RenderMode2();
			m_RenderMode3();
			break;
		}
		}
	}
}
