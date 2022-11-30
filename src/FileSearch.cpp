#include "FileSearch.h"

#include <iostream>
#include <Poco/Path.h>
#include <Poco/RecursiveDirectoryIterator.h>

FileSearch::FileSearch(const std::vector<std::string>& searchPaths)
{
    for (const auto& searchPath : searchPaths)
    {
        _searchPaths.push_back(searchPath);
        // FIX ME : the depth of search can be changed
        Poco::SimpleRecursiveDirectoryIterator dirIterator(searchPath, 2);
        Poco::SimpleRecursiveDirectoryIterator end;
        while (dirIterator != end)
        {
            
            if (dirIterator->isDirectory())
            {
                _searchPaths.push_back(dirIterator->path());
            }
            ++dirIterator;
        }
    }
}

std::string FileSearch::Search(const std::string& filename)
{
    bool isFound = false;
    Poco::Path path;
    isFound = Poco::Path::find(_searchPaths.begin(), _searchPaths.end(), filename, path);
    if (isFound)
    {
        return path.absolute().toString();
    }
    else
    {
        return std::string();
    }
}