/*WgForecast Author: Igors Kolcins
*-- This is visual widget.
*		Show forecast for now.
*		Background render parent class WgBackground
* 
*--  -- Modes: it has 1 modes
*			md1x1: show temperature
*/

/*
// THIS PART MUST BE REWRITEN USING CPR WRAPPER LIB INSTEAD PURE CURL!!!!!
//
//
//
*/



#pragma once

#ifndef SMART_RTU_SRC_WIDGETS_WGFORECAST_H_
#define SMART_RTU_SRC_WIDGETS_WGFORECAST_H_


#include<string>/*string*/

#include "WgBackground.h"
#include "Picture.h"/*for creating Pics*/
#include "json.h"/*parsing jsons*/
using json = nlohmann::json;

#define CURRENT_WEATHER_URL "http://api.openweathermap.org/data/2.5/weather?q=Daugavpils&units=metric&appid=a0a20199a69ae584fd1303a3152d92bc"

#define TEMPERATURE_SYMBOL 'C'

class WgForecast 
: public WgBackground
{
public:
	WgForecast(int AposX, int AposY, wgMode Amode);
	~WgForecast();

	bool update()override;
	void render()override;
private:
	Picture *m_weather_icon_picture;
	std::string m_weather_icon_name;
	std::string m_weather_icons_path;
	std::string m_base_font_name;

	char m_temp_degree[8]; //temperature string buf
	char m_wind_speed[10]; //wind speed string buf
	int m_wind_degree;	//wind degree

	bool m_is_data_received; //flag about received or not data from web /*isConnection*/

	//needed stuff for curl request
	static size_t m_WriteCallback(void *contents, size_t size, size_t nmemb, void *userp);
	//uses curl request to get from server weather data in json form
	void m_GetWeatherFromWeb(const char *site, json &weather_data);

	void m_RenderMode1();
	void m_RenderMode2();
	void m_RenderMode3(); // need debugging
};

#endif /*SMART_RTU_SRC_WIDGETS_WGFORECAST_H_*/

/* server response JSON example
	[{
		"coord": { "lon": 26.53, "lat": 55.88 },
		"weather": [
			{ "id": 803, "main": "Clouds", "description": "broken clouds", "icon": "04d" }
		],
		"base": "stations",
		"main": {
			"temp": 11.62,
			"pressure": 1000.64,
			"humidity": 100,
			"temp_min": 11.62,
			"temp_max": 11.62,
			"sea_level": 1017.84,
			"grnd_level": 1000.64
		},
		"wind": {
			"speed": 2.31,
			"deg": 312.505
		},
		"clouds": {
			"all": 56
		},
		"dt": 1504779065,
		"sys": { "message": 0.0104, "country": "LV", "sunrise": 1504755055, "sunset": 1504803075 },
		"id": 460413,
		"name": "Daugavpils",
		"cod": 200
	}]
*/

//include "curl/curl.h"


// git: github.com/curl/curl
// Some basic information at the russian: http://www.programmersforum.ru/showthread.php?t=60338
//
//--CURLcode curl_easy_setopt(CURL *handle, CURLoption option, parameter)
//----	CURL *handle - указатель на интерфейс, который мы получили выше.
//----	CURLoption option - название опции, которую следует задать.
//----	parameter - параметр, который связывается с опцией, это может быть число, у
//		казатель на функцию, строка. Функцию можно вызывать несколько раз подряд,
//		задавая необходимые опции. Все опции, по умолчанию, выключены.

//--CURLOPT_URL - очень важная опция, в параметре указывается строка - URL,
//	с которым собираемся взаимодействовать. В строке параметра можно указать небходимый протокол,
//	в виде стандартного префикса "http://" или "ftp://".

//--CURLOPT_WRITEFUNCTION - данная опция позволяет задавать,
//	в качестве параметра, указатель на функцию обратного вызова.
//	Эта функция вызывается библиотекой, каждый раз, когда принимаются какие либо данные,
//	требующие дальнейшего использования или сохранения.

//--CURLOPT_WRITEDATA - эта опция определяет параметр, как объект,
//	в который производится запись принимаемых данных.

//--void curl_easy_cleanup(CURL * handle) - Это функция должна вызываться самой последней
//	и вызываться должна обязательно. Она выполняет завершение текущей сессии.
