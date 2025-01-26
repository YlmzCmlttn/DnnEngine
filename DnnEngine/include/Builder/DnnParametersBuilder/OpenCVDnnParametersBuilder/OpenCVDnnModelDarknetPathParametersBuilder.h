#pragma once

#include "Builder/ParametersBuilderContainer.h"
namespace DnnEngine
{
    template <typename Base>
    class OpenCVDnnModelDarknetPathParametersBuilder : public Base
    {
        OpenCVDnnDarknetModelPath& m_Parameters;
    public:
        explicit OpenCVDnnModelDarknetPathParametersBuilder(Base& base,OpenCVDnnDarknetModelPath& parameters):Base{base},m_Parameters{parameters}{}

        OpenCVDnnModelDarknetPathParametersBuilder& cfgPath(const std::string& cfgPath){
            m_Parameters.cfgFilePath = cfgPath;
            return *this;
        }

        OpenCVDnnModelDarknetPathParametersBuilder& weightsPath(const std::string& weightsPath){
            m_Parameters.weightsFilePath = weightsPath;
            return *this;
        }
    };
} 

