#pragma once
#ifndef SMART_RTU_SRC_CONFIGURATOR_CONFIG_H_
#define SMART_RTU_SRC_CONFIGURATOR_CONFIG_H_


#include <map>
#include <string>

//
// Idea was took from here https://wiki.calculquebec.ca/w/C%2B%2B_:_fichier_de_configuration/en
//

// red text //std::cout<<"\033[1;31m RED TEXT \033[0m"<<'\n'; //for red text
//source of diferent text colors in console  https://stackoverflow.com/questions/2616906/how-do-i-output-coloured-text-to-a-linux-terminal
//

//
// Probably need to add Timer class for StrNow();
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
    //string
    bool Get(const std::string& key,std::string &value) ;
    bool Get(const std::string& key,std::string &value,const std::string& default_value ) ;
    //int
    bool Get(const std::string& key, int& value);
    bool Get(const std::string& key, int& value,int default_value);
    //long
    //double
    //bool
    bool Get(const std::string& key, bool& value);
    bool Get(const std::string& key, bool& value,bool default_value);


private:
    // the container
    std::map<std::string,std::string> m_data;
 
    // remove leading and trailing tabs and spaces
    static std::string m_Trim(const std::string& str);
};
 //make it visible for others
 extern Configuration*config;

#endif/*SMART_RTU_SRC_CONFIGURATOR_CONFIG_H_*/