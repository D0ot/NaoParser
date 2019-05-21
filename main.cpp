#include <iostream>
#include <fstream>
#include <streambuf>
#include <sstream>
#include <string>
#include <vector>
#include <string>
#include <cstdint>
#include <cstdlib>
#include <unistd.h>
#include <map>
#include <utility>
#include "sexpresso.hpp"
#include "NaoMetaData.h"
#include "NaoMetaAdapter.h"
#include "NaoMetaCommon.h"
#include "DataSelector.h"
#include "DataGenerator.h"

const std::string testfile = "/home/doot/learnthings/learnse/test.se";
const std::string testfile_prefix = "/home/doot/robocup3d/logdata/prereceptor.log";
const std::string logDataRoot = "/home/doot/robocup3d/logdata1/agentctrl/1558280119/";

std::string file2String(const std::string arg_filename)
{
	auto fb = std::ifstream(testfile);
	std::stringstream ss;
	ss << fb.rdbuf();
	return ss.str();
}


void showSexp(sexpresso::Sexp & arg_v)
{
	for(auto&& iter : arg_v.arguments()) {
		if(iter.isSexp()) {
			//std::cout << iter.value.str << std::endl;
			std::cout << iter.toString() << std::endl;
			//showSexp(iter);
		} else
		{
			std::cout << '\t' <<iter.value.str << std::endl;
		}
		
	}
}

void test1()
{
	std::cout << "Basic Test start." << std::endl;
	std::string s_exp_data = "(fuck 1) (time (now 93.60)) (GS(t 0.00) (pm BeforeKickOff)) (hear 0.00 self 1000-501)";
	auto data = file2String(testfile);

	//std::cout << s_exp_data << std::endl;
	auto result = sexpresso::parse(s_exp_data);
	//showSexp(result);
	
	std::cout << std::endl;
	auto result2 = sexpresso::parse(data);
	showSexp(result2);



	auto sub = result.getChildByPath("time");
	std::cout << sub->toString() << std::endl;
	std::cout << sub->value.sexp[0].value.str << std::endl;

	auto sub2 = result2.getChildByPath("GYR");
	std::cout << sub2->value.sexp[1].value.sexp[1].value.str << std::endl;

	std::cout << "Basic Test End." << std::endl;
}

void showHJ(NaoMetaData::MetaData& md, const std::string &name)
{
	std::cout << name << ':' << md.getHingeJointDegree(name) << std::endl;
}

void test2()
{
	NaoMetaData::MetaData md(testfile);

	std::cout << "now: " << md.getTimeNow() << std::endl;

	showHJ(md, "hj1");
	showHJ(md, "hj2");

	std::cout << "Acc: "<< md.getAcc() << std::endl;
	std::cout << "GYR: "<< md.getGyr() << std::endl;

	NaoMetaData::vec3<double> tc, tf;
	md.getFRP(NaoMetaData::wf_left, tc, tf);
	std::cout << "FRPl: " << tc << ' ' << tf << std::endl;

	md.getFRP(NaoMetaData::wf_right, tc, tf);
	std::cout << "FRPr: " << tc << ' ' << tf << std::endl;

}

void test3()
{
	NaoMetaData::MetaData md;
	
	for(int i = 1; i < 700; ++i)
	{
		
		std::system("clear");
		std::cout << i << std::endl;
		md.updateData(testfile_prefix + std::to_string(i));
		md.print();
		usleep(50*1000);
	}
}

void testFileSourceAdapter()
{
	auto fs = NaoMetaData::NaoMetaFileSource("/home/doot/robocup3d/logdata/", "prereceptor.log", 0, 700);
	NaoMetaData::MetaData md;
	for(auto i: fs)
	{
		usleep(1000*50);
		md.updateDataFromString(i);
		md.print();
	}

	

}


void testServerTrack()
{
	auto data = NaoMetaData::loadFiletoMetaData(logDataRoot + "outfile.dat11");
	NaoMetaData::MetaData md;
	std::map<std::string, bool> table;
	std::vector<std::pair<double, std::string>> goalFrames;
	
	for(auto i : data)
	{
		md.updateDataFromString(i);
		system("clear");
		std::cout << "Play Mode" << md.getPlayMode() << std::endl;
		table[md.getPlayMode()] = true;

		if(md.getPlayMode().find("Goal") == 0)
		{
			goalFrames.push_back(std::make_pair(md.getTimeNow(), md.getPlayMode()));
			std::cin.get();
		}

		md.print();
	}

	for(auto i : table)
	{
		std::cout << i.first << std::endl;
	}

	for(auto i : goalFrames)
	{
		std::cout << i.second << ':' << i.first << std::endl;
	}



}

void selectorTest()
{
	auto data = NaoMetaData::loadFiletoMetaData(logDataRoot + "outfile.dat5");
	auto sub_data1 = NaoMetaData::selectBeforeGoal(data, 4);
	//auto sub_data1 = data;
	NaoMetaData::MetaData md;
	std::cout << "Check" << std::endl;
	for(auto i : sub_data1)
	{
		md.updateDataFromString(i);
		std::cout << system("clear") << std::endl;
		//md.print();
		usleep(10000);
	}

	NaoMetaData::writeToCsvFile("./hj.csv", data);
	
}



int main(void)
{
	//test3();
	try{
		selectorTest();
	} catch (std::exception & e)
	{
		std::cerr << "In main catch an exception : " << e.what() << std::endl;
	}
	
	return 0;
}

