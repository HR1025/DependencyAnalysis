#include "DependencyCache.h"

#include <cassert>

DependencyCache::DependencyCache(const std::string& program /* or dynamic */)
    : _name(program)
{

}

const std::string& DependencyCache::GetName()
{
    return _name;
}

void DependencyCache::AddDependency(Dependency&& dependency)
{
    _dependencies.push_back(dependency);
}

const std::vector<DependencyCache::Dependency>& DependencyCache::GetDependencies()
{
    return _dependencies;
}