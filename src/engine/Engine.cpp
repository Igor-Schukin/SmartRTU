#include "Engine.h"

#include <unistd.h>/*usleep() e.tc*/

// C++
#include <cstdio>/*fprintf*/

//libshape stuff probably can cut some not used
/*OpenVG stuff like vgLoadIdenty*/
extern "C"
{
#include "VG/openvg.h"
#include "VG/vgu.h"
#include "fontinfo.h"
#include "shapes.h"
}


#include"timetable.h"//to delete timetable
#include "board.h"/*to also delete board*/
#include "Timer.h"/*StrNow()*/



const char *fmt(const char *f, const char *s1, const char *s2, const char *s3)
{
	static char buf[100];
	sprintf(buf, f, s1, s2, s3);
	return buf;
}

//********************************************************************************
//*** Engine
//********************************************************************************

#define DEBUG_OUTPUT_PRD (60 * 60 * 1000) // 1hour
#define FLUSH_LOG_PRD 1000				  // 1sec

Engine *engine = nullptr;

Engine::Engine()
{
	m_is_terminated = false;
	board = new Board;
	m_is_running = false;
	m_frame_capacity = 1000 / FRAMES_PER_SECOND;
}

Engine::~Engine()
{
	if (board){
		delete board;
	}
	
	if (timetable){
		delete timetable;
	}
}

void Engine::start()
{
	if (!m_is_running)
		run();
}

void Engine::run()
{
	m_is_running = true;

	LongTimeMs idleTime = 0;
	LongTimeMs lastRender = 0;
	LongTimeMs lastDebug = 0;
	LongTimeMs lastFlush = 0;
	//LongTimeMs t = 0; //not used variable
	int fps = 0;

	this->ForceUpdate();
	render(true);

	fprintf(stdout,"%s\tEngine main circle  started\n", StrNow());

	while (m_is_running && !m_is_terminated)
	{
		LongTimeMs time = timer.GetTime();

		//kbhit();  //?

		update();

		if ((time - lastRender) >= static_cast<long long unsigned int>(m_frame_capacity))
		{
			render(false);
			lastRender = time;
			fps++;
		}

#ifdef DEBUG_OUTPUT_PRD

		if ((time - lastDebug) >= DEBUG_OUTPUT_PRD)
		{
			unsigned int tsec = static_cast<unsigned int>((time / 1000LLU));
			unsigned int tm_d = tsec / (24 * 3600);
			tsec %= (24 * 3600);
			unsigned int tm_h = tsec / 3600;
			tsec %= 3600;
			unsigned int tm_m = tsec / 60;
			tsec %= 60;
			unsigned int tm_s = tsec;
			fprintf(stdout,
				"%s\tStatus: on time: %u:%02u:%02u:%02u, idle: %llu%%, fps: %.0f\n",
				StrNow(), tm_d, tm_h, tm_m, tm_s,
				idleTime * 100 / (time - lastDebug),
				(float)(fps)*1000 / (time - lastDebug));

			fps = 0;
			idleTime = 0;
			lastDebug = time;
		}

#endif

#ifdef FLUSH_LOG_PRD

		if (time - lastFlush >= FLUSH_LOG_PRD)
		{
			fflush(stdout);
			lastFlush = time;
		}

#endif

		usleep(1000); // 1ms
		idleTime += 1;
	}

	fprintf(stdout,"%s\tEngine main circle  finished\n", StrNow());
}

void Engine::update()
{
	board->update(false);
}

void Engine::ForceUpdate()
{
	board->update(true);
}

void Engine::render(bool All)
{
	//Start(width, height);
	VGfloat color[4] = {1, 1, 1, 1};
	//vgSetfv(VG_CLEAR_COLOR, 4, color);
	//vgClear(0, 0, width, height);
	color[0] = 0, color[1] = 0, color[2] = 0;
	setfill(color);
	setstroke(color);
	StrokeWidth(0);
	vgLoadIdentity();

	//Background(0, 0, 0);
	VGfloat colour[4];
	RGB(0, 0, 0, colour);
	vgSetfv(VG_CLEAR_COLOR, 4, colour);
	//	vgClear(0, 0, state->window_width, state->window_height);

	board->render(All);

	End();
}

/*
int Engine::kbhit(void)
{
	struct termios oldt, newt;
	int ch;
	int oldf;

	tcgetattr(STDIN_FILENO, &oldt);
	newt = oldt;
	newt.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &newt);
	oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
	fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

	ch = getchar();

	tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
	fcntl(STDIN_FILENO, F_SETFL, oldf);

	if(ch != EOF)
	{
		ungetc(ch, stdin);	
		m_is_running = false;		
		return 1;
	}
	return 0;
}
*/