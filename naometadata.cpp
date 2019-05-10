//Author D0ot at github
//5.10 2019
#include "naometadata.h"


namespace NaoMetaData
{
    
    MetaDataExeception::MetaDataExeception(const std::string& arg_content)noexcept :exception() 
    {
         content = arg_content;
    }

    const char *MetaDataExeception::what()const noexcept
    {
        return content.c_str();
    }


    MetaData::MetaData(){
        //Do nothing.
    }

    MetaData::MetaData(const std::string& arg_in)
    {
        updateData(arg_in);   
    }


    void MetaData::updateData(const std::string& arg_in)
    {
                //read a file to std::string
        auto fb = std::ifstream(arg_in);
        if(!fb.is_open())
        {
            throw MetaDataExeception("File:" + arg_in + "open failed.");
        }
        
	    std::stringstream ss;
	    ss << fb.rdbuf();
	    auto strdata = ss.str();

        //parse
        auto parser = sexpresso::parse(strdata);


        //if parse is "time 1 2 3" the arguments would be "1", "2", "3". 
        auto spnow = parser.getChildByPath("time/now");
        _time.now = std::stod(spnow->value.sexp[1].value.str);



        HJ tempHJ;
        FRP tempFRP;
        //iter
        for(auto&& iter: parser.arguments())
        {
            switch(iter.toString()[0])
            {
                case 't': //time
                    break;

                case 'G': //GS or GYR
                    switch (iter.toString()[1])
                    {
                        case 'S':
                            _GS = resolveGS(iter);
                            break;
                        case 'Y':
                            _GYR = resolveGYR(iter);
                            break;
                        default:
                            std::cerr << "undefine data:\n"
                            << iter.toString()
                            << std::endl;
                            break;
                    }
                    break;

                case 'h': //hear
                    _hear = resolvehear(iter);
                    break;

                case 'A': //ACC
                    _ACC = resolveACC(iter);
                    break;

                case 'S': //See
                    //TODO
                    break;

                case 'H': //HJ
                    tempHJ = resolveHJ(iter);
                    _HJ[tempHJ.n] = tempHJ;
                    break;

                case 'F': //FRP
                    tempFRP = resolveFRP(iter);
                    if(tempFRP.n[0] == 'l')
                    {
                        _FRPl = tempFRP;
                    } else
                    {
                        _FRPr = tempFRP;
                    }
                    
                    break;

            }
        }
    }

    NaoMetaData::time MetaData::resolvetime(const sexpresso::Sexp &arg_sexp)
    {
        return NaoMetaData::time(std::stod(arg_sexp.value.sexp[1].value.sexp[1].value.str));
    }

    NaoMetaData::GS MetaData::resolveGS(const sexpresso::Sexp &arg_sexp)
    {
        NaoMetaData::GS temp;
        temp.t = std::stod(arg_sexp.value.sexp[1].value.sexp[1].value.str);
        temp.pm = arg_sexp.value.sexp[2].value.sexp[1].value.str;
        return temp;
    }

    NaoMetaData::hear MetaData::resolvehear(const sexpresso::Sexp &arg_sexp)
    {
        NaoMetaData::hear temp;
        temp.p1 = arg_sexp.value.sexp[1].value.str;
        temp.p2 = std::stod(arg_sexp.value.sexp[2].value.str);
        temp.p3 = arg_sexp.value.sexp[3].value.str;
        temp.p4 = arg_sexp.value.sexp[4].value.str;
        return temp;
    }

    NaoMetaData::GYR MetaData::resolveGYR(const sexpresso::Sexp &arg_sexp)
    {
        NaoMetaData::GYR temp;
        temp.n = arg_sexp.value.sexp[1].value.sexp[1].value.str;
        auto &temp2 = arg_sexp.value.sexp[2];

        #ifdef DEBUG
        std::cout << "log:" << temp2.value.sexp[1].value.str << std::endl;
        temp.rt.x = std::stod(temp2.value.sexp[1].value.str);
        std::cout << "log:" << temp2.value.sexp[2].value.str << std::endl;
        temp.rt.y = std::stod(temp2.value.sexp[2].value.str);
        std::cout << "log:" << temp2.value.sexp[3].value.str << std::endl;
        temp.rt.z = std::stod(temp2.value.sexp[3].value.str);
        #endif
        temp.rt.x = std::stod(temp2.value.sexp[1].value.str);
        temp.rt.y = std::stod(temp2.value.sexp[2].value.str);
        temp.rt.z = std::stod(temp2.value.sexp[3].value.str);
        return temp;
    }

    NaoMetaData::ACC MetaData::resolveACC(const sexpresso::Sexp &arg_sexp)
    {
        //same as MetaData::resolveGYR
        NaoMetaData::ACC temp;
        temp.n = arg_sexp.value.sexp[1].value.sexp[1].value.str;
        auto &temp2 = arg_sexp.value.sexp[2];
        temp.a.x = std::stod(temp2.value.sexp[1].value.str);
        temp.a.y = std::stod(temp2.value.sexp[2].value.str);
        temp.a.z = std::stod(temp2.value.sexp[3].value.str);
        return temp;

    }

    NaoMetaData::See MetaData::resolveSee(const sexpresso::Sexp &arg_sexp)
    {
        throw MetaDataExeception("Unimplemented function called : MetaData::resolveSee().");
    }

    NaoMetaData::HJ MetaData::resolveHJ(const sexpresso::Sexp &arg_sexp)
    {
        NaoMetaData::HJ temp;
        temp.n = arg_sexp.value.sexp[1].value.sexp[1].value.str;

        try {
            temp.ax = std::stod(arg_sexp.value.sexp[2].value.sexp[1].value.str);
        } catch(std::exception &exc)
        {
            std::cerr << "Exception : " << exc.what() << std::endl;
            temp.ax = 0;
        }
        return temp;
    }

    NaoMetaData::FRP MetaData::resolveFRP(const sexpresso::Sexp &arg_sexp)
    {
        NaoMetaData::FRP temp;
        temp.n = arg_sexp.value.sexp[1].value.sexp[1].value.str;
        auto &temp2 = arg_sexp.value.sexp[2];
        auto &temp3 = arg_sexp.value.sexp[3];
        temp.c.x = std::stod(temp2.value.sexp[1].value.str);
        temp.c.y = std::stod(temp2.value.sexp[2].value.str);
        temp.c.z = std::stod(temp2.value.sexp[3].value.str);
        temp.f.x = std::stod(temp3.value.sexp[1].value.str);
        temp.f.y = std::stod(temp3.value.sexp[2].value.str);
        temp.f.z = std::stod(temp3.value.sexp[3].value.str);
        //std::cout << "inside resolveFRP() " <<  temp.n << ' ' << temp.f.x << std::endl;
        return temp;
    }


    //above is interfer to lib user.

    double MetaData::getTimeNow()const
    {
        return _time.now;
    }

    double MetaData::getHingeJointDegree(const std::string& arg_name)
    {
        return _HJ[arg_name].ax;
    }

    std::string MetaData::getPlayMode()const
    {
        return _GS.pm;
    }

    vec3<double> MetaData::getAcc()const
    {
        return _ACC.a;
    }


    vec3<double> MetaData::getGyr()const
    {
        return _GYR.rt;
    }

    void MetaData::getFRP(WhichFoot arg_which, vec3<double>& arg_pos, vec3<double>& arg_force)const
    {
        if(arg_which == WhichFoot::wf_left)
        {
            arg_pos = _FRPl.c;
            arg_force = _FRPl.f;
        } else
        {
            arg_pos = _FRPr.c;
            arg_force = _FRPr.f;

        }
        
    }

    void MetaData::print()const
    {

        std::cout << "Preceptor Begin" << std::endl
            << "Time : " << getTimeNow() << std::endl
            << "GYR : " << _GYR.rt << std::endl
            << "Acc : " << _ACC.a << std::endl
            << "HJ : " << std::endl;
        
        for(auto i:_HJ)
        {
            std::cout << '\t' << i.second.n << " : " << i.second.ax << std::endl;
        }
        vec3<double> c, f;
        getFRP(WhichFoot::wf_left, c, f);
        std::cout << "FRPl : " << c << ' ' << f << std::endl;
        getFRP(WhichFoot::wf_right, c, f);
        std::cout << "FRPr : " << c << ' ' << f << std::endl
        << "Preceptor End" << std::endl;
    }






} // NaoMetaData
