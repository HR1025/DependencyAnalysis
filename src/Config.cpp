#include "Config.h"

#include <iostream>

#include <Poco/Util/IniFileConfiguration.h>
#include <Poco/JSON/Parser.h>
#include <Poco/JSON/Object.h>
#include <Poco/JSON/Array.h>

const std::string Config::kBin         = "bin";
const std::string Config::kObjdump     = "objdump";
const std::string Config::kTxtOuput    = "txt_output";
const std::string Config::kMdOutput    = "md_output";
const std::string Config::kSearchPaths = "search_paths";

void Config::LoadConfig(const std::string& iniFile)
{
    const static std::string kConfig = "config.";
    Poco::AutoPtr<Poco::Util::IniFileConfiguration> pConf = new Poco::Util::IniFileConfiguration(iniFile);

    _configs[kBin] = pConf->getString(kConfig + kBin);
    _configs[kObjdump] = pConf->getString(kConfig + kObjdump);
    _configs[kTxtOuput] = pConf->getString(kConfig + kTxtOuput);
    _configs[kMdOutput] = pConf->getString(kConfig + kMdOutput);
    _configs[kSearchPaths] = pConf->getString(kConfig + kSearchPaths);
}

const std::string& Config::GetConfig(const std::string& key)
{
    return _configs[key];
}

void Config::Info()
{
    auto seachPaths = ParseJsonStringArrayToStringVector(GetConfig(kSearchPaths));
    
    std::cout << "********************************************** config(begin) ****************************************************" << std::endl;
    std::cout << "-- bin is : " << GetConfig(kBin) << std::endl;
    std::cout << "-- objdump is : " << GetConfig(kObjdump) << std::endl;
    std::cout << "-- txt_output is : " << GetConfig(kTxtOuput) << std::endl;
    std::cout << "-- md_output is : " << GetConfig(kMdOutput) << std::endl;
    std::cout << "-- search path num is : " << seachPaths.size() << std::endl;
    for(const auto& seachPath : seachPaths)
    {
        std::cout << "\t-- seach path is: " << seachPath << std::endl;
    }
    std::cout << "********************************************** config( end ) ****************************************************" << std::endl;
}

std::vector<std::string> Config::ParseJsonStringArrayToStringVector(const std::string& jsonStringArray)
{
    std::vector<std::string> stringVec;
    Poco::JSON::Parser parser;
    Poco::Dynamic::Var result;
    result = parser.parse(jsonStringArray);
    Poco::JSON::Array::Ptr array = result.extract<Poco::JSON::Array::Ptr>();
    auto arraySize = array->size();
    for (size_t i=0; i<arraySize; i++)
    {
        stringVec.push_back(array->getElement<std::string>(i));
    }
    return stringVec;
}