#include "DataSelector.h"
#include "NaoMetaData.h"

namespace NaoMetaData
{



    std::vector<std::string> selectBeforeGoal(std::vector<std::string>& arg_data, std::size_t arg_second)
    {
        std::size_t firstAppear = 0;
        
        #ifdef DEBUG
        std::cout << "verbose : Get in selectBeforeGoal() " << std::endl;
        #endif 

        MetaData md;

        for(std::size_t i = 0; i < arg_data.size(); ++i)
        {
            md.updateDataFromString(arg_data[i]);
            if(md.getPlayMode().find("Goal") == 0)
            {
                #ifdef DEBUG
                std::cout << "verbose : Get in for loop." << std::endl;
                #endif 
                firstAppear = i;
                break;
            }    
        }
        

        if(firstAppear)
        {

            #ifdef DEBUG
            std::cout << arg_data[firstAppear] << std::endl;
            std::cout << arg_data[firstAppear - 1] << std::endl;
            #endif

            auto end = arg_data.begin() + firstAppear;

            auto start = arg_data.begin();

            if(firstAppear - secondToFrames(arg_second) > 0)
            {
                start = end - secondToFrames(arg_second);
            }

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
