#pragma once

#include "Builder/ParametersBuilderContainer.h"
namespace DnnEngine
{
    template <typename Base>
    class OpenCVDnnModelPathParametersBuilder : public Base
    {
        OpenCVDnnModelPath& m_Parameters;
    public:
        explicit OpenCVDnnModelPathParametersBuilder(Base& base,OpenCVDnnModelPath& parameters):Base{base},m_Parameters{parameters}{}
    };
} 

