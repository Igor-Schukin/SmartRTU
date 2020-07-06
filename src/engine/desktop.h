#pragma once

#ifndef SMART_RTU_SRC_ENGINE_DESKTOP_H_
#define SMART_RTU_SRC_ENGINE_DESKTOP_H_


struct Desktop
{
    int scrWidth, scrHeight;                                            // screen size
    struct { int left, top, right, bottom, width, height; } dwRect;     // widgets area
    int colCount, rowCount, colWidth, rowHeight;                        // grid

    Desktop( int scr_width, int scr_height );
    ~Desktop();
};

extern Desktop * desktop;

#endif /*SMART_RTU_SRC_ENGINE_DESKTOP_H_*/