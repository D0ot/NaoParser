#include <string>
#include <fstream>
#include <sstream>
#include "naometacommon.h"


namespace NaoMetaData
{
    std::string loadFiletoString(const std::string& arg_fileName)
    {
        auto fb = std::ifstream(arg_fileName);
	    std::stringstream ss;
	    ss << fb.rdbuf();
	    return ss.str();
    }
} // namespace NaoMetaData
