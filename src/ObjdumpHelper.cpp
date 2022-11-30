#include "ObjdumpHelper.h"

#include <iostream>
#include <sstream>
#include <Poco/Pipe.h>
#include <Poco/PipeStream.h>
#include <Poco/Process.h>
#include <Poco/RegularExpression.h>

ObjdumpHelper::ObjdumpHelper(const std::string& objdump)
{
    _objdump = objdump;
    _onDependencies = [](const std::vector<std::string>& dependencies) -> void 
    {
    };
}

void ObjdumpHelper::SetOnDependencies(const OnDependencies& onDependencies)
{
    _onDependencies = onDependencies;
}

void ObjdumpHelper::Dump(std::string executable)
{
    /************************************ Utils (begin) **************************************/
    /**
     * @brief 是否是动态库依赖
     * @note  匹配 NEEDED.*so
     */
    auto isDependency = [](const std::string& line) -> bool
    {
        bool res = false;
        Poco::RegularExpression re(".*NEEDED.*so.*");
        return re.match(line, 0);
    };
    /**
     * @brief 抽离动态库表达式
     * @note  根据 lib*so 或者 lib*so.* 的规则进行
     */
    auto getDependency = [](const std::string& line) -> std::string
    {
        Poco::RegularExpression re("lib.*([0-9]|o)");
        std::vector<std::string> splits; // splits only one size in fact
        re.split(line, 0, splits);
        for (const auto& split : splits)
        {
            if (split.find("so") != std::string::npos)
            {
                return split;
            }
        }
        return std::string();
    };
    /************************************ Utils (end) **************************************/

    Poco::Pipe outPipe;
    Poco::Process::Args args;
    args.push_back("-x");
    args.push_back(executable);
    Poco::ProcessHandle ph(Poco::Process::launch(_objdump, args, 0, &outPipe, 0));
    Poco::PipeInputStream is(outPipe);

    std::vector<std::string> dependencies;
    char buf[1024];
    uint32_t bytesRead = 0;
    do {
        is.getline(buf, 1024);
        bytesRead = is.gcount();
        std::string line(buf);
        if (isDependency(line))
        {
            dependencies.push_back(getDependency(line));
        }
    }while(bytesRead != 0);
    _onDependencies(dependencies);
}