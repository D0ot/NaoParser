// Author D0ot @ github

#ifndef _NAOMETAADAPTER_H
#define _NAOMETAADAPTER_H

#include <string>
#include <iostream>
#include <vector>
#include <memory>

namespace NaoMetaData
{
    class NaoMetaAdapter;
    class NaoMetaAdapterIter;
    class NaoMetaFileSource;
    //Iter base
    class NaoMetaAdapterIter
    {
        friend NaoMetaFileSource;
      private:
        size_t index;
        NaoMetaAdapter* data;
        NaoMetaAdapterIter(NaoMetaAdapter *arg_adapter, size_t arg_index);
      public:
        NaoMetaAdapterIter& operator++();
        bool operator!=(const NaoMetaAdapterIter& arg_iter);
        std::string &operator*();
    };



    class NaoMetaFileSource;

    class NaoMetaAdapter
    {
      

      public:
        NaoMetaAdapter();
        virtual ~NaoMetaAdapter() {};
        
        virtual std::string& getData(size_t index) = 0;
        virtual size_t getSize() = 0;

    };


    class NaoMetaFileSource: public NaoMetaAdapter
    {
      private:
        std::string dirName, prefix, singleFile;
        const bool checkSingleFile;
        const int start_index;
        const int end_index;
        std::vector<std::string> data;
        std::vector<std::shared_ptr<NaoMetaAdapterIter>> iters;
        void loadFiles();
      public:
        NaoMetaFileSource(const std::string &arg_singleFile);
        NaoMetaFileSource(const std::string &arg_dir, const std::string &arg_prefix, 
          const int arg_start, const int arg_end);
        std::string& getData(size_t index);
        size_t getSize();
        NaoMetaAdapterIter begin();
        NaoMetaAdapterIter end();
        virtual ~NaoMetaFileSource() {};

        

    };

} // namespace NaoMetaData




#endif //_NAOMETAADAPTER_H