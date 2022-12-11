#include <string>
#include <vector>
#include <map>

/**
 * @brief 简单加载并解析 ini 配置文件
 */
class Config
{
public:
    /**
     * @brief        加载配置
     * @param[in]    iniFile : ini 配置文件
     */
    void LoadConfig(const std::string& iniFile);
    /**
     * @brief       获取配置
     * @param[in]   key
     * @return      value
     */
    const std::string& /* value */ GetConfig(const std::string& key);
    /**
     * @brief 打印配置信息 
     */
    void Info();
    /**
     * @brief      将 json 格式的字符数组解析为 stl 类型的字符数组
     * @param[in]  jsonStringArray : json 格式的字符数组
     * @return     stl 类型的字符数组
     * @note       辅助函数
     */
    std::vector<std::string> ParseJsonStringArrayToStringVector(const std::string& jsonStringArray);
public: /* available key */
    static const std::string kBin;
    static const std::string kObjdump;
    static const std::string kTxtOuput;
    static const std::string kMdOutput;
    static const std::string kSearchPaths;

private:
    std::map<std::string /* key */, std::string /* value */> _configs;
};