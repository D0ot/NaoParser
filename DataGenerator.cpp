#include <fstream>
#include "DataGenerator.h"

namespace NaoMetaData
{
    


    void writeToCsvFile(std::string arg_fileName, std::vector<std::string> arg_data)
    {
        std::ofstream output(arg_fileName);
        NaoMetaData::MetaData md;
        output 
        << "hj1,"
        << "hj2,"
        
        << "laj1,"
        << "laj2,"
        << "laj3,"
        << "laj4,"

        << "llj1,"
        << "llj2,"
        << "llj3,"
        << "llj4,"
        << "llj5,"
        << "llj6,"
        << "llj7,"

        << "rlj1,"
        << "rlj2,"
        << "rlj3,"
        << "rlj4,"
        << "rlj5,"
        << "rlj6,"
        << "rlj7,"

        << "raj1,"
        << "raj2,"
        << "raj3,"
        << "raj4,"
        << std::endl;



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
            << std::to_string(md.getHingeJointDegree("llj7")) << ','

            << std::to_string(md.getHingeJointDegree("rlj1")) << ','
            << std::to_string(md.getHingeJointDegree("rlj2")) << ','
            << std::to_string(md.getHingeJointDegree("rlj3")) << ','
            << std::to_string(md.getHingeJointDegree("rlj4")) << ','
            << std::to_string(md.getHingeJointDegree("rlj5")) << ','
            << std::to_string(md.getHingeJointDegree("rlj6")) << ','
            << std::to_string(md.getHingeJointDegree("rlj7")) << ','

            << std::to_string(md.getHingeJointDegree("raj1")) << ','
            << std::to_string(md.getHingeJointDegree("raj2")) << ','
            << std::to_string(md.getHingeJointDegree("raj3")) << ','
            << std::to_string(md.getHingeJointDegree("raj4")) << ','
            << std::endl;
        }
    }
} // namespace NaoMetaData


