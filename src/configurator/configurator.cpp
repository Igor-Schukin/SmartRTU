#include"configurator.h"
Configuration*config;
// ----------------------------------
// method implementations
// ----------------------------------
 
#include <fstream> // /*read from file*/
#include <iostream>/*cout*/

void Configuration::Clear()
{
    m_data.clear();
}
 
bool Configuration::Load(const std::string& file_name)
{
     std::ifstream inFile(file_name.c_str());
 
    if (!inFile.good())
    {
          std::cerr << "\033[1;31mCannot read configuration file\033[0m" << file_name << '\n'; //red text 
        return false;
    }
 
    while (inFile.good() && ! inFile.eof())
    {
        std::string line;
        std::getline(inFile, line);
 
        // filter out comments
        if (!line.empty())
        {
            std::size_t pos = line.find('#'); //changed int to size_t
           
            if (pos != std::string::npos)
            {
                line = line.substr(0, pos);
            }
        }
 
        // split line into key and value
        if (!line.empty())
        {
         std::size_t pos = line.find('=');//changed int to size_t
        
            if (pos != std::string::npos)
            {
                std::string key     = m_Trim(line.substr(0, pos));  
                std::string value   = m_Trim(line.substr(pos + 1));
 
                if (!key.empty() && !value.empty())
                {
                    m_data[key] = value;
                }
            }
        }
    }
 
    return true;
}
 
bool Configuration::Contains(const std::string& key) const
{
    return m_data.find(key) != m_data.end();
}
 
bool Configuration::Get(const std::string& key,std::string &value) 
{
    std::map<std::string,std::string>::const_iterator iter = m_data.find(key);
 
    if (iter != m_data.end())
    {
        value= iter->second;
        return true;
    }
    else
    {
        std::cerr << "\033[1;31m~~~~ not faund \"" << key << "\" in config ~~~~~\033[0m" << '\n';
        return false;
    }
}

bool Configuration::Get(const std::string& key,std::string &value,const std::string& default_value) 
{
    std::map<std::string,std::string>::const_iterator iter = m_data.find(key);
 
    if (iter != m_data.end())
    {
        value= iter->second;
        return true;
    }
    else
    {
        std::cerr << "\033[1;31m~~~~ not TEST faund \"" << key << "\" in config, replaced by default_value:"<<default_value<<" ~~~~~\033[0m" << '\n';
        value=default_value;
        return false;
    }
}

bool Configuration::Get(const  std::string& key, int& value) 
{
    std::string str;
 
    if (Get(key, str))
    {
        value = atoi(str.c_str());
        return true;
    }
    else
    {
        std::cerr << "\033[1;31m~~~~ not faund \"" << key << "\" in config ~~~~~\033[0m" << '\n';
        return false;
    }
}

bool Configuration::Get(const std::string& key, int& value,int default_value) 
{
    std::string str;
 
    if (Get(key, str))
    {
        value = atoi(str.c_str());
        return true;
    }
    else
    {
        std::cerr << "\033[1;31m~~~~ not faund \"" << key << "\" in config, replaced by default_value:"<<default_value<<"~~~~~\033[0m" << '\n';
        value=default_value;
        return false;
    }
}

bool Configuration::Configuration::Get(const std::string& key, double& value) {
      std::string str;
 
    if (Get(key, str))
    {
        value = std::stod(str.c_str());
        return true;
    }
    else
    {
        std::cerr << "\033[1;31m~~~~ not faund \"" << key 
        << "\" in config ~~~~~\033[0m" 
        << '\n';
        return false;
    }
}

bool Configuration::Configuration::Get(const std::string& key, double& value,double default_value) {
    std::string str;
 
    if (Get(key, str))
    {
        value = std::stod(str.c_str());
        return true;
    }
    else
    {
        std::cerr << "\033[1;31m~~~~ not faund \"" 
        << key << "\" in config, replaced by default_value:"
        <<default_value<<"~~~~~\033[0m" << '\n';
        
        value=default_value;
        return false;
    }
}


bool Configuration::Get(const std::string& key, bool& value)
{
    std::string str;
 
    if (Get(key, str))
    {
        value = (str == "true");
        return true;
    }
    else
    {
        std::cerr << "\033[1;31m~~~~ not faund \"" << key << "\" in config~~~~~\033[0m" << '\n';
        return false;
    }
}

bool Configuration::Get(const std::string& key, bool& value,bool default_value)
{
    std::string str;
 
    if (Get(key, str))
    {
        value = (str == "true");
        return true;
    }
    else
    {
        std::cerr << "\033[1;31m~~~~ not faund \"" << key 
        << "\" in config, replaced by default_value:"
        <<default_value<<"~~~~~\033[0m" << '\n'; 

        value=default_value;
        return false;
    }

}


std::string Configuration::m_Trim(const std::string& str)
{
     std::size_t first = str.find_first_not_of(" \t"); //int to size_t
 
    if (first != std::string::npos)
    {
        std::size_t last = str.find_last_not_of(" \t");//int to size_t
 
        return str.substr(first, last - first + 1);
    }
    else
    {
        return "";
    }
}

