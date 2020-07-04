/***********************************************************************************************************

Socket  RPi      GPIO    WiringPi
        header   number  pin
        pin    
1       3        2       8
2       5        3       9
3       7        4       7
4       11       17      0

***********************************************************************************************************/

#pragma once

#ifndef SMART_RTU_SRC_WIDGETS_WGSOCKETS_H_
#define SMART_RTU_SRC_WIDGETS_WGSOCKETS_H_


#include "IWidget.h"
/*
Restyled by RazdolbayOne
*/

constexpr int SOCKETS_COUNT =  4;

//what pins are used for socket
const int SOCKETS_PINS[SOCKETS_COUNT] = {8, 9, 7, 0}; 

class WgSockets : public IWidget
{
private:
    int id;
    bool m_current_states[SOCKETS_COUNT]; //holds current state of pin(on/off )

public:
    ~WgSockets();
    WgSockets();
    bool update();
    void render() {}
    bool IsVisible() override { return false; };
    void getRect(int &x, int &y, int &w, int &h)
    {
        x = 0;
        y = 0;
        w = 0;
        h = 0;
    }
    void setId(int id) { this->id = id; }
    int getUpdateTime() { return 1000; } //1000ms = 1 time / sec
};

#endif /*SMART_RTU_SRC_WIDGETS_WGSOCKETS_H__*/