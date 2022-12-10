#pragma once

#include <memory>
#include <map>

#include "DependencyCache.h"

// forward declare
class ObjdumpHelper;
class FileSearch;

/**
 * @brief 依赖查找
 */
class DependencySerach
{
public:
    /**
     * @brief      构造函数
     * @param[in]  objdump : objdump 可执行路径
     * @param[in]  fileSearch    : 文件查找辅助器
     */
    DependencySerach(const std::string& objdump, std::shared_ptr<FileSearch> fileSearch);
    /**
     * @brief      查找 program 的依赖
     * @param[in]  program : 可执行程序
     */
    void Search(const std::string& program);
    /**
     * @brief      根据 name 获取依赖缓存
     * @param[in]  name : 可执行程序或者动态库
     */
    std::shared_ptr<DependencyCache> GetCacheByName(const std::string& name);
    /**
     * @brief 获取依赖缓存
     */
    std::map<std::string /* name */, std::shared_ptr<DependencyCache>> GetCaches();
private:
    std::shared_ptr<FileSearch>    _fileSearch;
    std::string                    _objdump;
    std::map<std::string /* name */, std::shared_ptr<DependencyCache>> _caches;
};