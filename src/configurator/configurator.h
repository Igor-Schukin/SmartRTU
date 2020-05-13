#pragma once
#ifndef CONFIG_H
#define CONFIG_H
#include <map>
#include <string>
#include <fstream>
#include <iostream>
 
//
// Idea was took from here https://wiki.calculquebec.ca/w/C%2B%2B_:_fichier_de_configuration/en
//

using namespace std;
 
class Configuration
{
public:
    // clear all values
    void Clear();
 
    // load a configuration file
    bool Load(const std::string& File);
 
    // check if value associated with given key exists
    bool Contains(const string& key) const;
 
    // get value associated with given key
    std::string Get(const std::string& key) ;

    // get value associated with given key or return default val
    std::string Get(const std::string& key ,const std::string&default_val) ;
    //(get("foo")+"/"+get("bar")).c_str()

 
private:
    // the container
    std::map<std::string,std::string> data;
 
    // remove leading and trailing tabs and spaces
    static string Trim(const std::string& str);
};
 //make it visible for others
 extern Configuration*config;
#endif