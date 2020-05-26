#pragma once
#ifndef SMART_RTU_SRC_CONFIGURATOR_CONFIG_H_
#define SMART_RTU_SRC_CONFIGURATOR_CONFIG_H_


#include <map>
#include <string>

//
// Idea was took from here https://wiki.calculquebec.ca/w/C%2B%2B_:_fichier_de_configuration/en
//

// to get c string -> str.c_str()
// to get int from string -> atoi(str.c_str());
// to get long from string -> atol(str.c_str());
// to get double from string -> atof(str.c_str()); 
// to get bool from string -> value=(str=="true"); // need more understandable info




// red text //std::cout<<"\033[1;31m RED TEXT \033[0m"<<'\n'; //for red text
//source of diferent text colors in console  https://stackoverflow.com/questions/2616906/how-do-i-output-coloured-text-to-a-linux-terminal
//

 
class Configuration
{
public:
    // clear all values
    void Clear();
 
    // load a configuration file
    bool Load(const std::string& file_name);
 
    // check if value associated with given key exists
    bool Contains(const std::string& key) const;
 
    // get value associated with given key
    std::string Get(const std::string& key) ;

    // get value associated with given key or return default val
    std::string Get(const std::string& key ,const std::string&default_val) ;

private:
    // the container
    std::map<std::string,std::string> m_data;
 
    // remove leading and trailing tabs and spaces
    static std::string m_Trim(const std::string& str);
};
 //make it visible for others
 extern Configuration*config;

#endif/*SMART_RTU_SRC_CONFIGURATOR_CONFIG_H_*/