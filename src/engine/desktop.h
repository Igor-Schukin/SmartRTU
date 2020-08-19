#pragma once

#ifndef SMART_RTU_SRC_ENGINE_DESKTOP_H_
#define SMART_RTU_SRC_ENGINE_DESKTOP_H_


struct Desktop
{
    int screen_width, screen_height;                                            // screen size
    struct { int left, top, right, bottom, width, height; } DwRect;     // widgets area
    int colum_count, row_count, colum_width, row_height;                        // grid

    Desktop( int scr_width, int scr_height );
    ~Desktop();
};

extern Desktop * desktop;

#endif /*SMART_RTU_SRC_ENGINE_DESKTOP_H_*/