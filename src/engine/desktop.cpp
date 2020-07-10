#include "desktop.h"

#include <iostream>/*cout*/

#include "Timer.h"/*strNow*/
#include "configurator.h"//config
/*
#define GRID_VERTICAL   8 //10
#define GRID_HORIZONTAL 4 //6

#define TOP_FIELD       0.15
#define BOTTOM_FIELD    0.05
#define LEFT_FIELD      0.05
#define RIGHT_FIELD     0.05
*/
Desktop * desktop;

Desktop::Desktop( int scr_width, int scr_height )
    :screen_width(scr_width),
    screen_height(scr_height)
{
    //screen_width = scr_width;
    //screen_height = scr_height;

    int grid_vertical,grid_horizontal;
    double top_field,bottom_field,left_field,right_field;

    config->Get("DESKTOP_GRID_VERTICAL",grid_vertical);
    config->Get("DESKTOP_GRID_HORIZONTAL",grid_horizontal);

    config->Get("DESKTOP_TOP_FIELD",top_field);
    config->Get("DESKTOP_BOTTOM_FIELD",bottom_field);
    config->Get("DESKTOP_LEFT_FIELD",left_field);
    config->Get("DESKTOP_RIGHT_FIELD",right_field);

    DwRect.left = static_cast<int>(screen_width * left_field); 
    DwRect.bottom = static_cast<int>(screen_height * bottom_field);
    DwRect.right = static_cast<int>(screen_width * ( 1 - right_field ));
    DwRect.top = static_cast<int>(screen_height * ( 1 - top_field ));
    DwRect.width = DwRect.right - DwRect.left;
    DwRect.height = DwRect.top - DwRect.bottom;

    row_count = grid_vertical;
    colum_count = grid_horizontal;
    colum_width = DwRect.width / colum_count;
    row_height = DwRect.height / row_count;

    std::cout<<StrNow()<<"\tDesktop size "
    <<screen_width<<" x "<<screen_height<<", widgets area size "
    <<DwRect.width<<" x "<<DwRect.height<<"\n";
}

Desktop::~Desktop() { 

}

