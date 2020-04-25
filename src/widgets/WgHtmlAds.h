
#pragma once
#ifndef WGHTMLADS_H
#define WGHTMLADS_H

#include <iostream>
#include <string>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "WgBackground.h"
#include "Engine.h"
#include "desktop.h"
#include "Timer.h"
#include "CPicturesStorage.h"
#include "CFontStorage.h"
#include "config.h"

class WgHtmlAds : public WgBackground
{
private:
    Picture *HtmlPic;

public:
    WgHtmlAds(int Ax, int Ay, wgMode Amode);
    ~WgHtmlAds();
    void render();
};

#endif /*WGHTMLADS_H*/