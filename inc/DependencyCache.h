#pragma once

#include <string>
#include <vector>

/**
 * @brief 简易的依赖记录缓存
 */
class DependencyCache
{
public:
    struct Dependency
    {
        std::string name;
        std::string filePath; 
    };
public:
    /**
     * @brief      构造函数
     * @param[in]  program(dynamic) : 可执行程序或动态库
     */
    explicit DependencyCache(const std::string& program /* or dynamic */);
    /**
     * @brief 获取名称
     * @sa    DependencyCache
     * @note  for debug
     */
    const std::string& GetName();
    /**
     * @brief      添加依赖项
     * @param[in]  dependency : 依赖项
     * @sa         Dependency
     */
    void AddDependency(Dependency&& dependency);
    /**
     * @brief      获取依赖项
     * @return     依赖项
     * @sa         Dependency
     */
    const std::vector<Dependency>& GetDependencies();
private:
    std::string             _name;
    std::vector<Dependency> _dependencies;
};