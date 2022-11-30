#pragma once

#include <vector>
#include <string>

/**
 * @brief 简易的文件查找
 */
class FileSearch
{
public:
    /**
     * @brief      构造函数
     * @param[in]  searchPaths : 查找路径
     * @note       查找优先级按照 vector 的顺序决定
     */
    explicit FileSearch(const std::vector<std::string>& searchPaths);
    /**
     * @brief      查找
     * @param[in]  filename : 文件名
     * @return     文件路径 (绝对)
     */
    std::string /* filepath */ Search(const std::string& filename);
private:
    std::vector<std::string> _searchPaths;
};