#include "WgForecast.h"


#include <curl/curl.h>

#include <iostream>/*cout*/
#include <string>

#include "Timer.h"/*StrNow()*/
#include "desktop.h"/*desktop obj*/
#include "CPicturesStorage.h"/*pict obj*/
#include "CFontStorage.h"/*font obj*/
#include "configurator.h"/*config*/


WgForecast::WgForecast(int Ax, int Ay, WgMode Amode)
	: WgBackground(Ax, Ay, Amode)
{
	widget_update_time_ = 60 * 60 * 1000; // 1 hour
	m_weather_icon_picture = nullptr;
	weather_icon_name_ = "";

	//get destination of weather icon
	config->Get("PIC_WEATHER_ICONS_PATH", weather_icons_path_);
	config->Get("BASE_FONT_NAME", base_font_name_);

	m_is_data_received = false;

	strcpy(m_temp_degree, "");
	strcpy(m_wind_speed, "");
	m_wind_degree = 0;
	std::cout << StrNow() << "\tWgForecast widget object was created\n";
}

WgForecast::~WgForecast()
{
	if (m_weather_icon_picture)
		delete m_weather_icon_picture;
	std::cout << StrNow() << "\tWgForecast widget object was deleted\n";
}

std::size_t WgForecast::m_WriteCallback(void *contents, std::size_t size, 
										std::size_t nmemb, void *userp) //???
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
			std::cout << StrNow() << "\tNew current weather state was received\n";
		}
		else
		{
			m_is_data_received = false;
			std::cerr << StrNow() << "\tError of current weather state receiving!!!\n";
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
		std::sprintf(m_temp_degree, "%+d°%c", buf_temp, TEMPERATURE_SYMBOL);
	}
	else
	{
		std::sprintf(m_temp_degree, "---");
	}

	if (m_is_data_received && weather_data["wind"]["deg"].is_number())
	{
		m_wind_degree = weather_data["wind"]["deg"];
		float buf_speed = weather_data["wind"]["speed"];
		std::sprintf(m_wind_speed, "%.0f m/s", buf_speed);
	}
	else
	{
		std::sprintf(m_wind_speed, "---");
		m_wind_degree = 0;
	}

	//~~~ load weather icon

	if (m_is_data_received && weather_data["weather"][0]["icon"].is_string())
	{
		std::string icon_name = weather_data["weather"][0]["icon"];
		if (icon_name != weather_icon_name_)
		{
			if (m_weather_icon_picture) {
				delete m_weather_icon_picture;
			}
			m_weather_icon_picture = new Picture(
				(weather_icons_path_ + "/" + icon_name + ".png").c_str()
			);
			weather_icon_name_ = icon_name;
			std::cout << StrNow() << "\tNew weather icon was loaded \n";
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

void WgForecast::RenderMode1_()
{
	RenderWidgetHeader(m_temp_degree);
}

void WgForecast::RenderMode2_()
{
	float field = RectClient.width * 0.07;

	//~~ weather icon
	//NEED RESTYLE IT
	int icon_width = 0, icon_height = 0;
	if (m_weather_icon_picture)
	{
		//icon_scale
		float icon_scale = (float)RectClient.height * 1.0 / m_weather_icon_picture->Get_height();
		icon_width = m_weather_icon_picture->Get_width() * icon_scale;
		icon_height = m_weather_icon_picture->Get_height() * icon_scale;
		m_weather_icon_picture->render(
			RectClient.left + field,
			RectClient.bottom + (RectClient.height - icon_height) / 2,
			icon_scale, icon_scale, 0, 0, 0);
	}

	//~~ wind arrow
	// as
	float arrow_scale = (float)RectClient.height * 0.35 / PicStorage->Arrow->Get_height();
	// aw
	int arrow_width = PicStorage->Arrow->Get_width() * arrow_scale * 1.75; // 1.4 = sqrt(2)
	// ah
	int arrow_height = PicStorage->Arrow->Get_height() * arrow_scale;
	PicStorage->Arrow->render(
		RectClient.right - arrow_width - field,
		RectClient.bottom + (RectClient.height - arrow_height) / 2,
		arrow_scale, arrow_scale, 0, 0,
		-m_wind_degree);

	//~~~ wind speed

	SetTextColor(clHaki);

	TFont *font = FontStorage->GetFont(
		const_cast<char *>(base_font_name_.c_str())
	);
	font->Set_Size(desktop->row_height / 3);
	int wind_height = static_cast<int>(font->TextHeight());
	font->TextMid(
		m_wind_speed,
		RectClient.left + icon_width + (RectClient.width - icon_width - arrow_width) / 2,
		RectClient.bottom + (RectClient.height - wind_height) / 2);
}

void WgForecast::RenderMode3_() // need to debug
{

}

void WgForecast::render()
{
	if (m_is_data_received)
	{
		WgBackground::render();
		switch (widget_mode_)
		{
		case md1x1:
		{
			RenderMode1_();
			break;
		}
		case md1x2:
		{
			RenderMode1_();
			RenderMode2_();
			break;
		}
		case md1x3:
		{
			RenderMode1_();
			RenderMode2_();
			RenderMode3_();
			break;
		}
		case md3x8:{
			//FIXME
			break;
		}
		case mdCustom:{

			//FIXME
			break;
		}
		}
	}
}
