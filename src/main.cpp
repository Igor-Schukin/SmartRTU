
#include <cstdio>
#include <csignal>

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

	try
	{
		printf("%s\t***** INFOBORAD engine is started\n", strNow());
		
		//create config
		config=new Configuration;

		//check if config loaded
		if(config->Load("./res/config.cfg")==false){
			printf("%s\t \033[1;31m CONFIG DID NOT LOADED check your config.cfg destination or if file exist!\033[0m\n", strNow());
		}
		else
		{
			printf("%s\tConfig loaded successfully\n", strNow());
		}

		try
		{
			timetable = new Timetable;
		}
		catch (...)
		{
			timetable = NULL;
		}

		int width, height;
		init(&width, &height);//get display/monitor width and height

		desktop = new Desktop(width, height);

		PicStorage = new CPicturesStorage();
		FontStorage = new CFontStorage();
		//set MAIN font to project
		FontStorage->setFont(
			const_cast<char*>(
				config->Get("BASE_FONT_NAME").c_str()
				),
			const_cast<char*>(
				(config->Get("BASE_FONT_PATH")+"/"+config->Get("BASE_FONT")).c_str()
				)
			 );

		engine = new Engine;
		engine->start();


		delete engine;
		delete FontStorage;
		delete PicStorage;
		delete config;
		finish();

		printf("%s\t***** INFOBORAD engine is finished\n", strNow());
	}
	catch (...)
	{
		printf("%s\t~~~~~ INFOBORAD engine is crashed\n", strNow());
		return 1; // need restart
	}
	return 0;
}
