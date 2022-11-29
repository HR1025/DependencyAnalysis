#include <iostream>
#include <string>
#include <memory>
#include <Poco/Util/IniFileConfiguration.h>
#include <Poco/JSON/Parser.h>
#include <Poco/JSON/Object.h>
#include <Poco/JSON/Array.h>

struct Config
{
    std::string               bin;
    std::vector<std::string>  searchPaths;
    bool                      txtOuput;
    bool                      mdOutput;
    std::string               objdump;
};

static void LoadConifgIni(const std::string& configPath, Config& config)
{
    Poco::AutoPtr<Poco::Util::IniFileConfiguration> pConf = new Poco::Util::IniFileConfiguration(configPath);
    std::string      searchPaths;

    config.bin       = pConf->getString("config.bin");
    config.txtOuput  = pConf->getBool("config.txt_output");
    config.mdOutput  = pConf->getBool("config.md_output");
    config.objdump   = pConf->getString("config.objdump");
    
    searchPaths      = pConf->getString("config.search_paths");
    Poco::JSON::Parser parser;
    Poco::Dynamic::Var result;
    result = parser.parse(searchPaths);
    Poco::JSON::Array::Ptr array = result.extract<Poco::JSON::Array::Ptr>();
    auto arraySize = array->size();
    for (size_t i=0; i<arraySize; i++)
    {
        config.searchPaths.push_back(array->getElement<std::string>(i));
    }
    

}

int main(int argc, char** argv)
{
    if (argc < 2)
    {
        std::cout << "Uasge : DependencyAnalysis DependencyAnalysis.ini" << std::endl;
        return -1;
    }

    Config  config;
    LoadConifgIni(std::string(argv[1]), config);
    std::cout << std::endl << "******** config(begin) ********" << std::endl;
    std::cout << "-- bin : " << config.bin << std::endl;
    std::cout << "-- txt_output : " << config.txtOuput << std::endl;
    std::cout << "-- md_output : " << config.mdOutput << std::endl;
    std::cout << "-- search path num : " << config.searchPaths.size() << std::endl;
    for(const auto& searchPath : config.searchPaths)
    {
        std::cout << "---- seach path : " << searchPath << std::endl;
    }
    std::cout << "-- objdump : " << config.objdump << std::endl;
    std::cout << "******** config(end) ********" << std::endl << std::endl;


    return 0;
}