#include "WgWatchdog.h"

#include<iostream>/*cout*/

#include "Timer.h"/*strNow()*/
#include "Engine.h"/*fmt*/
#include "configurator.h" //config 

WgWatchdog::WgWatchdog()
{
    config->Get("WATCHDOG_DEST",watchdog_dest);
    config->Get("WATCHDOG_NAME",watchdog_name);

    std::cout<<strNow()<<"\t"<<"WgWatchdog widget object was created\n";
}

WgWatchdog::~WgWatchdog()
{
    std::cout<<strNow()<<"\t"<<"WgWatchdog widget object was deleted\n";
}

bool WgWatchdog::update()
{
    system(fmt("rm -rf %s 2> /dev/null",(watchdog_dest+"/"+watchdog_name).c_str()));
    return false;
}
