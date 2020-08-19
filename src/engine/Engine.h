#pragma once

#ifndef SMART_RTU_SRC_ENGINE_ENGINE_H_
#define SMART_RTU_SRC_ENGINE_ENGINE_H_

#include "board.h"/*for board var*/
#include "IWidget.h"/*for IWidget var*/

//  includes to kbhit function
// #include <termios.h>

#define FRAMES_PER_SECOND 25

class Engine
{	
public:
	Engine();
	~Engine();
	void start();
	void terminate() { is_terminated_ = true; }
	void ForceUpdate();
	
private:
	int frame_capacity_;
	bool is_running_;
	bool is_terminated_;

	Board *board_;
	IWidget *w;

	void run_();
	void update();
	void render(bool All);
	void ShowFrames();
};

extern Engine *engine;
extern const char *fmt(const char *f, const char *s1, 
					   const char *s2 = nullptr, const char *s3 = nullptr
					   );
#endif /*SMART_RTU_SRC_ENGINE_ENGINE_H_*/