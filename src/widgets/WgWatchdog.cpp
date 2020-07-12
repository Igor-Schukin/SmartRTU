#include "WgWatchdog.h"

#include <iostream>/*cout*/
#include <cstdlib>//system

#include "Engine.h"       /*fmt*/
#include "Timer.h"        /*StrNow()*/
#include "configurator.h" //config

WgWatchdog::WgWatchdog() {
  config->Get("WATCHDOG_DEST", watchdog_dest);
  config->Get("WATCHDOG_NAME", watchdog_name);

  std::cout << StrNow() << "\t"
            << "WgWatchdog widget object was created\n";
}

WgWatchdog::~WgWatchdog() {
  std::cout << StrNow() << "\t"
            << "WgWatchdog widget object was deleted\n";
}

void WgWatchdog::Set_widget_id(int m_widget_id) {
  this->m_widget_id = m_widget_id;
}

bool WgWatchdog::update() {
  std::system(fmt("rm -rf %s 2> /dev/null",
             (watchdog_dest + "/" + watchdog_name).c_str()));
  return false;
}

void WgWatchdog::render() {
//emty    
}
