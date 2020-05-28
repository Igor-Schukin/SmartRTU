
#include <cstdio>
#include <csignal>

#include<string>

#include "CPicturesStorage.h"
#include "CFontStorage.h"

#include "Engine.h"
#include "timetable.h"
#include "desktop.h"

#include"configurator.h"

void termSignalHandler(int signal)
{
	if (engine)
		engine->terminate();
}

int main()
{

	std::signal(SIGTERM, termSignalHandler);
	//all about fonts
	std::string base_font_name;
	std::string base_font_path;
	std::string base_font_full_name;
	try
	{
		fprintf(stdout,"%s\t***** INFOBORAD engine is started\n", strNow());
		
		//create config
		config=new Configuration;

		//check if config loaded
		if(config->Load("./res/config.cfg")==false){
			fprintf(stderr,"%s\t \033[1;31m CONFIG DID NOT LOADED check your config.cfg destination or if file exist!\033[0m\n", strNow());
		}
		else
		{
			fprintf(stdout,"%s\tConfig loaded successfully\n", strNow());
		}

		try
		{
			timetable = new Timetable;
		}
		catch (...)
		{
			timetable = NULL;
		}

		config->Get("BASE_FONT_NAME",base_font_name);
		config->Get("BASE_FONT_PATH",base_font_path);
		config->Get("BASE_FONT",base_font_full_name);

		int width, height;
		init(&width, &height);//get display/monitor width and height

		desktop = new Desktop(width, height);

		PicStorage = new CPicturesStorage();
		FontStorage = new CFontStorage();
		//set MAIN font to project
		FontStorage->setFont(
			const_cast<char*>(
				base_font_name.c_str()
				),
			const_cast<char*>(
				(base_font_path+"/"+base_font_full_name).c_str()
				)
			 );

		engine = new Engine;
		engine->start();


		delete engine;
		delete FontStorage;
		delete PicStorage;
		delete config;
		finish();

		fprintf(stdout,"%s\t***** INFOBORAD engine is finished\n", strNow());
	}
	catch (...)
	{
		fprintf(stderr,"%s\t~~~~~ INFOBORAD engine is crashed\n", strNow());
		return 1; // need restart
	}
	return 0;
}
