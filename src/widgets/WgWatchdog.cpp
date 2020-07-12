#include "WgWatchdog.h"

#include <iostream>/*cout*/
#include <cstdlib>//system

#include "Engine.h"       /*fmt*/
#include "Timer.h"        /*StrNow()*/
#include "configurator.h" //config

WgWatchdog::WgWatchdog() {
  config->Get("WATCHDOG_PATH", watchdog_path_);
  config->Get("WATCHDOG_NAME", watchdog_name_);

  std::cout << StrNow() << "\t"
            << "WgWatchdog widget object was created\n";
}

WgWatchdog::~WgWatchdog() {
  std::cout << StrNow() << "\t"
            << "WgWatchdog widget object was deleted\n";
}

void WgWatchdog::Set_widget_id(int a_widget_id) {
  this->widget_id_ = a_widget_id;
}

bool WgWatchdog::update() {
  std::system(fmt("rm -rf %s 2> /dev/null",
             (watchdog_path_ + "/" + watchdog_name_).c_str()));
  return false;
}

void WgWatchdog::render() {
//emty    
}
