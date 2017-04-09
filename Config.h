#pragma once
#include <map>
#include <string>
#include <iostream>
#include <fstream>

class ConfigSection
{
    public:
    void setValue(std::string key, std::string value);
    
    int getInt(std::string);
    double getDouble(std::string);
    float getFloat(std::string);
    
    void setSection(std::string key, ConfigSection* section);
    ConfigSection* getSection(std::string key);
    
    void readSection(std::ifstream &file);
    
    private:
    std::map<std::string, std::string> values;
    std::map<std::string, ConfigSection*> subSectons;
};

class Config
{
    public:
    Config(std::string file);
    ConfigSection* getConfig();
    
    private:
    ConfigSection mainSection;
};
