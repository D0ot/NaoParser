#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <vector>
#include "NaoMetaData.h"
#include "NaoMetaCommon.h"
#include "NaoMetaAdapter.h"


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

    std::vector<std::string> loadFiletoMetaData(const std::string& arg_fileName)
    {
        auto track = NaoMetaServerTrack("", arg_fileName);
        return track.mainData;
    }


} // namespace NaoMetaData
