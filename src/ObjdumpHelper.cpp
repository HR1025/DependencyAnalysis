#include "ObjdumpHelper.h"

#include <iostream>
#include <sstream>
#include <Poco/Pipe.h>
#include <Poco/PipeStream.h>
#include <Poco/Process.h>
#include <Poco/StreamCopier.h>

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
    Poco::Pipe outPipe;
    Poco::Process::Args args;
    args.push_back("-x");
    args.push_back(executable);
    Poco::ProcessHandle ph(Poco::Process::launch(_objdump, args, 0, &outPipe, 0));
    Poco::PipeInputStream is(outPipe);
    std::stringstream ss;
    Poco::StreamCopier::copyStream(is, ss);
    // for debug
    std::cout << ss.str() << std::endl;
}