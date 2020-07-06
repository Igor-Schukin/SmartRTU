#pragma once

#include "board.h"/*for board var*/
#include "IWidget.h"/*for IWidget var*/

//  includes to kbhit function
// #include <termios.h>

#define FRAMES_PER_SECOND 25

class Engine
{
private:
	int m_frame_capacity;
	bool m_is_running;
	bool m_is_terminated;

	Board *board;
	IWidget *w;

	void run();
	void update();
	void render(bool All);
	void ShowFrames();
	//int kbhit(void);

public:
	Engine();
	~Engine();
	void start();
	void terminate() { m_is_terminated = true; }
	void ForceUpdate();
};

extern Engine *engine;
extern const char *fmt(const char *f, const char *s1, const char *s2 = nullptr, const char *s3 = nullptr);