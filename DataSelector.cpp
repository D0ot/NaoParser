#include "DataSelector.h"
#include "NaoMetaData.h"

namespace NaoMetaData
{



    std::vector<std::string> selectBeforeGoal(std::vector<std::string>& arg_data, std::size_t arg_second)
    {
        std::size_t firstAppear = 0;
        
        std::cout << "what is going" << std::endl;
        
        MetaData md;

        for(std::size_t i = 0; i < arg_data.size(); ++i)
        {
            md.updateDataFromString(arg_data[i]);
            if(md.getPlayMode().find("Goal") == 0)
            {
                std::cout << "What is going on" << std::endl;
                firstAppear = i;
                break;
            }    
        }

        if(firstAppear)
        {
            auto end = arg_data.begin() + firstAppear;
           auto start = end - secondToFrames(arg_second);

           return std::vector<std::string>(start, end);

        } else
        {
            return std::vector<std::string>();
        }
        


    }

    std::size_t secondToFrames(std::size_t arg_second)
    {
        return arg_second * FRAMESPERSECOND;
    }


} // namespace NaoMetaData
