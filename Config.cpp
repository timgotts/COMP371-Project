#include "Config.h"

void ConfigSection::setValue(std::string key, std::string value)
{
    values[key] = value;
}

int ConfigSection::getInt(std::string key)
{
    return std::stoi(values[key]);
}

double ConfigSection::getDouble(std::string key)
{
    return std::stod(values[key]);
}

float ConfigSection::getFloat(std::string key)
{
    return std::stof(values[key]);
}

void ConfigSection::setSection(std::string key, ConfigSection* section)
{
    subSectons[key] = section;
}

ConfigSection* ConfigSection::getSection(std::string key)
{
    return subSectons[key];
}

void ConfigSection::readSection(std::ifstream &file)
{
    std::string line;
    while(getline(file, line))
    {
        const auto strBegin = line.find_first_not_of(" \t");
        if(strBegin == std::string::npos)
        {
            continue;
        }
        
        const auto strEnd = line.find_last_not_of(" \t");
        const auto strRange = strEnd - strBegin + 1;
        
        line = line.substr(strBegin, strRange);
        
        std::size_t commentSymbolLocation = line.find("#");
        if(commentSymbolLocation != std::string::npos)
        {
            continue;
        }
        
        std::size_t sectionSymbolLocation = line.find(">");
        if(sectionSymbolLocation != std::string::npos)
        {
            std::string sectionName = line.substr(1);
            if(sectionName != "end")
            {
                std::cout << "Found section " << sectionName << std::endl;
                ConfigSection* section = new ConfigSection();
                subSectons[sectionName] = section;
                section->readSection(file);
            }else
            {
                return;
            }
            
        }else
        {
            std::size_t valueSeperatorLocation = line.find("=");
            if(valueSeperatorLocation != std::string::npos)
            {
                std::string key = line.substr(0, valueSeperatorLocation);
                std::string value = line.substr(valueSeperatorLocation+1);
                std::cout << "Found value " << key << ":" << value  << std::endl;
                
                values[key] = value;
            }
        }
    }
}

Config::Config(std::string path)
{
    std::ifstream file(path);
    if(file.is_open())
    {
        std::cout << "Loading " << path << std::endl;
        mainSection.readSection(file);
        
        
    }
    else
    {
        std::cout << "Could not open " << path << std::endl;
    }
    
}

ConfigSection* Config::getConfig()
{
    return &mainSection;
}

