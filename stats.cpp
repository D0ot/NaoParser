#include <iostream>
#include "NaoMetaData.h"
#include "NaoMetaCommon.h"



int main(void)
{
    NaoMetaData::MetaData md;
    auto data = NaoMetaData::loadFiletoMetaData("../testfiles/outfile.dat1");
    for(auto i: data)
    {
        md.updateDataFromString(i);
        std::cout << md.getPlayMode() << std::endl;
    }
    return 0;
}



