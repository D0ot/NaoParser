#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include "naometadata.h"
#include "naometacommon.h"


namespace NaoMetaData
{
    std::string loadFiletoString(const std::string& arg_fileName)
    {
        auto fb = std::ifstream(arg_fileName);
        
        
        if(!fb.is_open())
        {
            throw MetaDataExeception("File open failed : " + arg_fileName);
        }
	    std::stringstream ss;
	    ss << fb.rdbuf();
	    return ss.str();
    }
} // namespace NaoMetaData
