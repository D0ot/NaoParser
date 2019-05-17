//Author D0ot at github

#include "NaoMetaAdapter.h"
#include "NaoMetaCommon.h"
namespace NaoMetaData
{
    NaoMetaAdapter::NaoMetaAdapter(){};

    NaoMetaAdapterIter::NaoMetaAdapterIter(NaoMetaAdapter *arg_adapter, size_t arg_index)
        :index(arg_index), data(arg_adapter){}

    NaoMetaAdapterIter& NaoMetaAdapterIter::operator++()
    {
        ++index;
        return *this;
    }




    bool NaoMetaAdapterIter::operator!=(const NaoMetaAdapterIter& arg_iter)
    {
        return index != arg_iter.index;
    }

    std::string& NaoMetaAdapterIter::operator*()
    {
        return data->getData(index);
    }

    NaoMetaFileSource::NaoMetaFileSource(const std::string &arg_singleFile)
        :checkSingleFile(true), start_index(0), end_index(0)
    {
        //TODO
    }

    NaoMetaFileSource::NaoMetaFileSource(const std::string &arg_dir, const std::string &arg_prefix, 
        const int arg_start, const int arg_end):checkSingleFile(false), start_index(arg_start), end_index(arg_end) 
    {
        dirName = arg_dir;
        prefix = arg_prefix;

        loadFiles();

    }

    NaoMetaAdapterIter NaoMetaFileSource::begin()
    {
        /*auto temp = std::shared_ptr<NaoMetaAdapterIter>(
            new NaoMetaAdapterIter(static_cast<NaoMetaAdapter*>(this), 0)
            );

        iters.push_back(temp);
        return *temp;*/


        return NaoMetaAdapterIter(this, 0);


    }

    NaoMetaAdapterIter NaoMetaFileSource::end()
    {
        /*auto temp = std::shared_ptr<NaoMetaAdapterIter>(
            new NaoMetaAdapterIter(static_cast<NaoMetaAdapter*>(this), data.size())
            );

        iters.push_back(temp);
        return *temp;*/

        return NaoMetaAdapterIter(this, data.size());
    }

    std::string& NaoMetaFileSource::getData(size_t arg_index)
    {
        #ifdef DEBUG
        std::cout << "Data get " << arg_index << ' ' <<data.size() << std::endl;
        #endif
        return data.at(arg_index);
    }

    void NaoMetaFileSource::loadFiles()
    {
        for(int i = start_index; i <= end_index; ++i)
        {
            #ifdef DEBUG
            std::cout << "In load loop" << std::endl;
            #endif
            data.push_back(std::move(loadFiletoString(dirName + prefix + std::to_string(i))));     
        }
    }

    size_t NaoMetaFileSource::getSize()
    {
        return data.size();
    }

} // namespace NaoMetaData



//TODO