#define CATCH_CONFIG_MAIN

#include <iostream>
#include <fstream>
#include <streambuf>
#include <sstream>
#include <string>
#include <vector>
#include <string>
#include <cstdint>
#include "catch.hpp"
#include "sexpresso.hpp"
#include "naometadata.h"
#include <cmath>
using namespace Catch;

TEST_CASE ("NaoMetaData::MetaData unit test", "[NaoMetaData::MetaData]") {
    NaoMetaData::MetaData md("test.se");
    REQUIRE(md.getTimeNow() - 93.60 < 10E-5);
    REQUIRE(md.getPlayMode() == "BeforeKickOff");
    REQUIRE(md.getAcc() == NaoMetaData::vec3<double>(-0.35, -0.36, -0.02));
    REQUIRE(md.getGyr() == NaoMetaData::vec3<double>(-0.35, -0.36, -0.01));

    NaoMetaData::vec3<double> temp_c, temp_f;
    md.getFRP(NaoMetaData::WhichFoot::wf_left, temp_c, temp_f);
    REQUIRE(temp_c == NaoMetaData::vec3<double>(0.01, -0.01, -0.02));
    REQUIRE(temp_f == NaoMetaData::vec3<double>(-0.21, 0.21, 19.77));

    md.getFRP(NaoMetaData::WhichFoot::wf_right, temp_c, temp_f);
    REQUIRE(temp_c == NaoMetaData::vec3<double>(0.01, -0.01, -0.02));
    REQUIRE(temp_f == NaoMetaData::vec3<double>(-0.21, 0.21, 19.77));

    REQUIRE(fabs(md.getHingeJointDegree("hj1") - 0.33) < 10E-5);
    REQUIRE(fabs(md.getHingeJointDegree("hj2") - -3.31) < 10E-5);
    
}



