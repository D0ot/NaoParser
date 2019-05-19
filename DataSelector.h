#ifndef _DATASELECTOR_H
#define _DATASELECTOR_H

#include <iostream>
#include <vector>
#include "NaoMetaAdapter.h"
#include "NaoMetaCommon.h"
#include "NaoMetaData.h"


namespace NaoMetaData
{
    const std::size_t FRAMESPERSECOND = 50;
    std::vector<std::string> simpleSelect(std::vector<std::string>& arg_data);
    std::vector<std::string> selectBeforeGoal(std::vector<std::string>& arg_data, std::size_t arg_second);
    std::size_t secondToFrames(std::size_t arg_second);
    
}




#endif // _DATASELECTOR_H