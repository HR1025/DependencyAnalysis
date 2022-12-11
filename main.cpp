#include <iostream>
#include <string>
#include <memory>
#include <map>


#include "Config.h"
#include "ObjdumpHelper.h"
#include "FileSearch.h"
#include "DependencyCache.h"
#include "DependencySerach.h"

int main(int argc, char** argv)
{
    if (argc < 2)
    {
        std::cout << "Uasge : DependencyAnalysis DependencyAnalysis.ini" << std::endl;
        return -1;
    }

    Config  config;

    config.LoadConfig(std::string(argv[1]));
    config.Info();

    auto searchPaths = config.GetConfig(Config::kSearchPaths);
    DependencySerach dependencySerach(config.GetConfig(Config::kObjdump), std::make_shared<FileSearch>(config.ParseJsonStringArrayToStringVector(searchPaths)));
    dependencySerach.Search(config.GetConfig(Config::kBin));
    auto dependencies = dependencySerach.GetCacheByName(config.GetConfig(Config::kBin))->GetDependencies();

    for(const auto& dependency : dependencies)
    {
        std::cout << "\t" << "-- name is " << dependency.name <<  ", file path is " << dependency.filePath << std::endl;
    }
    std::cout << std::endl;

    return 0;
}