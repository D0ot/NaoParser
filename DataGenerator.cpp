#include <fstream>
#include "DataGenerator.h"

namespace NaoMetaData
{
    


    void writeToCsvFile(std::string arg_fileName, std::vector<std::string> arg_data)
    {
        std::ofstream output(arg_fileName);
        NaoMetaData::MetaData md;
        for(auto i:arg_data)
        {
            md.updateDataFromString(i);
            output 
            << std::to_string(md.getHingeJointDegree("hj1")) << ','
            << std::to_string(md.getHingeJointDegree("hj2")) << ','
            << std::to_string(md.getHingeJointDegree("laj1")) << ','
            << std::to_string(md.getHingeJointDegree("laj2")) << ','
            << std::to_string(md.getHingeJointDegree("laj3")) << ','
            << std::to_string(md.getHingeJointDegree("laj4")) << ','
            << std::to_string(md.getHingeJointDegree("llj1")) << ','
            << std::to_string(md.getHingeJointDegree("llj2")) << ','
            << std::to_string(md.getHingeJointDegree("llj3")) << ','
            << std::to_string(md.getHingeJointDegree("llj4")) << ','
            << std::to_string(md.getHingeJointDegree("llj5")) << ','
            << std::to_string(md.getHingeJointDegree("llj6")) << ','
            << std::to_string(md.getHingeJointDegree("rlj1")) << ','
            << std::to_string(md.getHingeJointDegree("rlj2")) << ','
            << std::to_string(md.getHingeJointDegree("rlj3")) << ','
            << std::to_string(md.getHingeJointDegree("rlj4")) << ','
            << std::to_string(md.getHingeJointDegree("rlj5")) << ','
            << std::to_string(md.getHingeJointDegree("rlj6")) << ','
            << std::to_string(md.getHingeJointDegree("raj1")) << ','
            << std::to_string(md.getHingeJointDegree("raj2")) << ','
            << std::to_string(md.getHingeJointDegree("raj3")) << ','
            << std::to_string(md.getHingeJointDegree("raj4")) << ','
            << std::endl;
        }
    }
} // namespace NaoMetaData


