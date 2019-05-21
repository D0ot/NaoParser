#ifndef _DATAGENERATOR_H
#define _DATAGENERATOR_H

#include <iostream>
#include <string>
#include <vector>
#include "NaoMetaData.h"
#include "DataGenerator.h"


namespace NaoMetaData
{
    void writeToCsvFile(std::string arg_fileName, std::vector<std::string>);
} // namespace NaoMetaData




#endif //_DATAGENERATOR_H