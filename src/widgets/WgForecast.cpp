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
	m_widget_update_time = 60 * 60 * 1000; // 1 hour
	m_weather_icon_picture = nullptr;
	m_weather_icon_name = "";

	//get destination of weather icon
	config->Get("PIC_WEATHER_ICONS_PATH", m_weather_icons_path);
	config->Get("BASE_FONT_NAME", m_base_font_name);

	m_is_data_received = false;

	strcpy(m_temp_degree, "");
	strcpy(m_wind_speed, "");
	m_wind_degree = 0;
	std::cout << strNow() << "\tWgForecast widget object was created\n";
}

WgForecast::~WgForecast()
{
	if (m_weather_icon_picture)
		delete m_weather_icon_picture;
	std::cout << strNow() << "\tWgForecast widget object was deleted\n";
}

size_t WgForecast::m_WriteCallback(void *contents, size_t size, size_t nmemb, void *userp) //???
{
	((std::string *)userp)->append((char *)contents, size * nmemb); // ???
	return size * nmemb;											// ???
}

void WgForecast::m_GetWeatherFromWeb(const char site[], json &weather_data)
{
	CURL *curl;				// object CURL tipa
	std::string read_buffer; //буффур куда будем записывать принятые данные
	CURLcode res;
	static char error_buffer[CURL_ERROR_SIZE]; //объявляем буфер, для хранения возможной ошибки, размер определяется в самой библиотеке
	curl = curl_easy_init();				  // curl initialization
	if (curl)								  //проверяем
	{
		//задаем все необходимые опции
		curl_easy_setopt(curl, CURLOPT_ERRORBUFFER, error_buffer);	  //определяем, куда выводить ошибки
		curl_easy_setopt(curl, CURLOPT_URL, site);					  //задаем опцию - получить страницу по адресу site
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, m_WriteCallback); //указываем функцию обратного вызова для записи получаемых данных
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &read_buffer);		  //указываем куда записывать принимаемые данные
		res = curl_easy_perform(curl);								  //запускаем выполнение задачи
		if (res == CURLE_OK)
		{
			m_is_data_received = true;
			auto buf = json::parse(read_buffer);
			weather_data = buf;
			std::cout << strNow() << "\tNew current weather state was received\n";
		}
		else
		{
			m_is_data_received = false;
			std::cerr << strNow() << "\tError of current weather state receiving!!!\n";
		}
	}
	curl_easy_cleanup(curl); //выполняем обязательное завершение сессии
}

bool WgForecast::update()
{
	json weather_data;
	m_GetWeatherFromWeb(CURRENT_WEATHER_URL, weather_data);

	if (m_is_data_received && weather_data["main"]["temp"].is_number())
	{
		int buf_temp = weather_data["main"]["temp"];
		sprintf(m_temp_degree, "%+d°%c", buf_temp, TEMPERATURE_SYMBOL);
	}
	else
	{
		sprintf(m_temp_degree, "---");
	}

	if (m_is_data_received && weather_data["wind"]["deg"].is_number())
	{
		m_wind_degree = weather_data["wind"]["deg"];
		float buf_speed = weather_data["wind"]["speed"];
		sprintf(m_wind_speed, "%.0f m/s", buf_speed);
	}
	else
	{
		sprintf(m_wind_speed, "---");
		m_wind_degree = 0;
	}

	//~~~ load weather icon

	if (m_is_data_received && weather_data["weather"][0]["icon"].is_string())
	{
		std::string icon_name = weather_data["weather"][0]["icon"];
		if (icon_name != m_weather_icon_name)
		{
			if (m_weather_icon_picture) {
				delete m_weather_icon_picture;
			}
			m_weather_icon_picture = new Picture(
				(m_weather_icons_path + "/" + icon_name + ".png").c_str()
			);
			m_weather_icon_name = icon_name;
			std::cout << strNow() << "\tNew weather icon was loaded \n";
		}
	}
	else
	{
		if (m_weather_icon_picture) {
			delete m_weather_icon_picture;
		}
		m_weather_icon_picture = nullptr;
	}

	return true;
}

void WgForecast::m_RenderMode1()
{
	RenderHeader(m_temp_degree);
}

void WgForecast::m_RenderMode2()
{
	float field = rectClient.width * 0.07;

	//~~ weather icon
	//NEED RESTYLE IT
	int icon_width = 0, icon_height = 0;
	if (m_weather_icon_picture)
	{
		//icon_scale
		float icon_scale = (float)rectClient.height * 1.0 / m_weather_icon_picture->Get_height();
		icon_width = m_weather_icon_picture->Get_width() * icon_scale;
		icon_height = m_weather_icon_picture->Get_height() * icon_scale;
		m_weather_icon_picture->render(
			rectClient.left + field,
			rectClient.bottom + (rectClient.height - icon_height) / 2,
			icon_scale, icon_scale, 0, 0, 0);
	}

	//~~ wind arrow
	// as
	float arrow_scale = (float)rectClient.height * 0.35 / PicStorage->Arrow->Get_height();
	// aw
	int arrow_width = PicStorage->Arrow->Get_width() * arrow_scale * 1.75; // 1.4 = sqrt(2)
	// ah
	int arrow_height = PicStorage->Arrow->Get_height() * arrow_scale;
	PicStorage->Arrow->render(
		rectClient.right - arrow_width - field,
		rectClient.bottom + (rectClient.height - arrow_height) / 2,
		arrow_scale, arrow_scale, 0, 0,
		-m_wind_degree);

	//~~~ wind speed

	setTextColor(clHaki);
	TFont *font = FontStorage->getFont(
		const_cast<char *>(m_base_font_name.c_str())
	);
	font->SetSize(desktop->rowHeight / 3);
	int wind_width = static_cast<int>(font->TextWidth(m_wind_speed));
	int wind_height = static_cast<int>(font->TextHeight());
	font->TextMid(
		m_wind_speed,
		rectClient.left + icon_width + (rectClient.width - icon_width - arrow_width) / 2,
		rectClient.bottom + (rectClient.height - wind_height) / 2);
}

void WgForecast::m_RenderMode3() // need to debug
{
	/*
	FontStorage->getFont((char*)"arialBold")->SetSize(desktop->rowHeight/5);
	FontStorage->getFont((char*)"arialBold")->TextMid("Veišs:", rectClient.left + (desktop->colWidth/2),
		rectClient.top - desktop->rowHeight - (desktop->rowHeight/5/2));
	setTextColor(color);
	FontStorage->getFont((char*)"arialBold")->SetSize(desktop->rowHeight/2.8);
	FontStorage->getFont((char*)"arialBold")->TextMid(m_wind_speed, rectClient.left + (desktop->colWidth/2.5),
		rectClient.top - desktop->rowHeight - desktop->rowHeight/16*11);
	PicStorage->Arrow->render(rectClient.left + (desktop->colWidth/1.3), rectClient.top - desktop->rowHeight - desktop->rowHeight/1.4, 1, 1, 0,0,-m_wind_degree);
	*/
}

void WgForecast::render()
{
	if (m_is_data_received)
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
