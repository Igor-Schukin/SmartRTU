#include"configurator.h"
Configuration*config;
// ----------------------------------
// method implementations
// ----------------------------------
 
void Configuration::Clear()
{
    data.clear();
}
 
bool Configuration::Load(const string& file)
{
    ifstream inFile(file.c_str());
 
    if (!inFile.good())
    {
        cout << "Cannot read configuration file " << file << '\n';
        return false;
    }
 
    while (inFile.good() && ! inFile.eof())
    {
        string line;
        getline(inFile, line);
 
        // filter out comments
        if (!line.empty())
        {
            int pos = line.find('#');
 
            if (pos != string::npos)
            {
                line = line.substr(0, pos);
            }
        }
 
        // split line into key and value
        if (!line.empty())
        {
            int pos = line.find('=');
 
            if (pos != string::npos)
            {
                string key     = Trim(line.substr(0, pos));
                string value   = Trim(line.substr(pos + 1));
 
                if (!key.empty() && !value.empty())
                {
                    data[key] = value;
                }
            }
        }
    }
 
    return true;
}
 
bool Configuration::Contains(const string& key) const
{
    return data.find(key) != data.end();
}
 
std::string Configuration::Get(const string& key) 
{
    std::map<std::string,std::string>::const_iterator iter = data.find(key);
 
    if (iter != data.end())
    {
        return iter->second;
    }
    else
    {
        std::cout << "~~~~ not faund " << key << " in config ~~~~~" << '\n';
        return "error" ;
    }
}
 
std::string Configuration::Get(const std::string & key, const std::string & default_val)
{
	std::map<std::string, std::string>::const_iterator iter = data.find(key);

	if (iter != data.end())
	{
		return iter->second;
	}
	else
	{
		std::cout << "~~~~ not faund " << key << " in config ~~~~~" << '\n';
		return default_val;
	}
}


std::string Configuration::Trim(const string& str)
{
    int first = str.find_first_not_of(" \t");
 
    if (first != std::string::npos)
    {
        int last = str.find_last_not_of(" \t");
 
        return str.substr(first, last - first + 1);
    }
    else
    {
        return "";
    }
}