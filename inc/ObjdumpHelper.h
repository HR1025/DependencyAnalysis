#pragma once

#include <functional>
#include <vector>

class ObjdumpHelper
{
public:
    /**
     * @brief      查询到依赖时触发
     * @param[in]  dependencies : 依赖项
     */
    using OnDependencies = std::function<void(const std::vector<std::string>& dependencies)>;
public:
    /**
     * @brief       构造函数
     * @param[in]   objdump : objdump 可执行程序路径
     */
    explicit ObjdumpHelper(const std::string& objdump);
    /**
     * @brief 设置依赖回调
     */
    void SetOnDependencies(const OnDependencies& onDependencies);
    /**
     * @brief      调用 objdump 查询
     * @param[in]  executable : 可执行程序
     * @note       objdump -x executable
     */
    void Dump(std::string executable);
private:
    OnDependencies            _onDependencies;
    std::string               _objdump;
};