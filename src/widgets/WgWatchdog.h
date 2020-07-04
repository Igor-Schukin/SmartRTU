#pragma once

#include<string>

#include "IWidget.h"

class WgWatchdog : public IWidget
{
public:
    ~WgWatchdog();
    WgWatchdog();
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
    int getUpdateTime() { return 10 * 60 * 1000; } //10min

private:
    int id;
    std::string watchdog_name;
    std::string watchdog_dest;
};