#include "DependencySerach.h"

#include "ObjdumpHelper.h"
#include "FileSearch.h"

DependencySerach::DependencySerach(const std::string& objdump, std::shared_ptr<FileSearch> fileSearch)
    : _objdump(objdump),
      _fileSearch(fileSearch)
{
}

void DependencySerach::Search(const std::string& program)
{
    /**
     * @note 递归遍历辅助函数
     */
    std::function<void(const std::string& name)> recursionHelper = [&recursionHelper, this](const std::string& name) -> void
    {
        ObjdumpHelper objdumpHelper(_objdump);
        _caches[name] = std::make_shared<DependencyCache>(name);
        objdumpHelper.SetOnDependencies([&recursionHelper, name, this](const std::vector<std::string>& dependencies) -> void
        {
            for (const auto& dependency : dependencies)
            {
                DependencyCache::Dependency info;
                info.name = dependency;
                info.filePath = _fileSearch->Search(dependency);
                auto _filePath = info.filePath;
                _caches[name]->AddDependency(std::move(info));
                if (_caches.find(dependency) == _caches.end())
                {
                    // Hint : 如果 name 当前的依赖没有记录再 _caches 中, 则递归查询其依赖
                    recursionHelper(_filePath);
                }
            }
        });
        objdumpHelper.Dump(name);
    };
    recursionHelper(program);
}

std::shared_ptr<DependencyCache> DependencySerach::GetCacheByName(const std::string& name)
{
    return _caches[name];
}

std::map<std::string /* name */, std::shared_ptr<DependencyCache>> DependencySerach::GetCaches()
{
    return _caches;
}