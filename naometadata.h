#ifndef _NAOMETADATA_H
#define _NAOMETADATA_H

#include <iostream>
#include <string>
#include <map>
#include <fstream>
#include <streambuf>
#include <sstream>
#include <exception>
#include <stdexcept>
#include "sexpresso.hpp"

namespace NaoMetaData
{
    //general exception
    class MetaDataExeception: public std::exception
    {
      private:
        std::string content;
      public:
        MetaDataExeception(const std::string& arg_content)noexcept;
        virtual const char* what()const noexcept;
    };

    //The data defined is all same with manual
    template<class T>
    struct vec3
    {
        T x, y, z;
        vec3(T arg_x, T arg_y, T arg_z);
        vec3(){};
        bool operator==(const vec3<T>& b)const;
    };

    template<class T>
    vec3<T>::vec3(T arg_x, T arg_y, T arg_z)
    {
        x = arg_x;
        y = arg_y;
        z = arg_z;
    }

    template<class T>
    bool vec3<T>::operator==(const vec3<T>& b)const
    {
        return (x - b.x < 10E-7) && (y - b.y < 10E-7) && (z - b.z < 10E-7);
    }

    template<class T>
    std::ostream& operator<<(std::ostream& arg_out, const vec3<T>& arg_data)
    {
        std::cout << arg_data.x << ' ' 
            << arg_data.y << ' '
            << arg_data.z << ' ';
        return arg_out;
    }


    struct time
    {
        double now;
        time(double arg_now){now = arg_now;}
        time(){}
    };

    struct GS
    {
        double t;
        std::string pm;
    };

    struct hear
    {
        double p1;
        std::string p2, p3;
    };


    struct GYR
    {
        GYR(){};
        std::string n;
        vec3<double> rt;
    };

    struct ACC
    {
        ACC(){};
        std::string n;
        vec3<double> a;
    };

    struct See
    {
        //TODO
    };

    struct HJ
    {
        HJ(){};
        std::string n;
        double ax;
    };

    struct FRP
    {
        FRP(){};
        std::string n;
        vec3<double> c, f;
    };

    enum WhichFoot
    {
        wf_left = 1, wf_right = 2
    };



    //Do the simplest work to resolve data and form metadata.
    class MetaData
    {
      private:
        time _time;
        GS _GS;
        hear _hear;
        GYR _GYR;
        ACC _ACC;
        See _See;
        std::map<std::string, HJ> _HJ;
        FRP _FRPl, _FRPr;

        time resolvetime(const sexpresso::Sexp &arg_sexp);
        GS resolveGS(const sexpresso::Sexp &arg_sexp);
        hear resolvehear(const sexpresso::Sexp &arg_sexp);
        GYR resolveGYR(const sexpresso::Sexp &arg_sexp);
        ACC resolveACC(const sexpresso::Sexp &arg_sexp);
        See resolveSee(const sexpresso::Sexp &arg_sexp);
        HJ resolveHJ(const sexpresso::Sexp &arg_sexp);
        FRP resolveFRP(const sexpresso::Sexp &arg_sexp);

      public:
        MetaData();
        MetaData(const std::string& arg_in);
        void updateData(const std::string& arg_in);
        double getHingeJointDegree(const std::string& arg_name);
        double getTimeNow()const;
        std::string getPlayMode()const;
        vec3<double> getAcc()const;
        vec3<double> getGyr()const;
        void getFRP(WhichFoot arg_which, vec3<double>& arg_pos, vec3<double>& arg_force)const;
        void print()const;
    };

} // namespace NaoMetaData

#endif // _NAOMETADATA_H