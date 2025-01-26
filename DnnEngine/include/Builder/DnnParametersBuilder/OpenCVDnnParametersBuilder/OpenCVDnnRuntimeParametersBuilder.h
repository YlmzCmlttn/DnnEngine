#pragma once
#include "Builder/ParametersBuilderContainer.h"
namespace DnnEngine
{
    template <typename Base>
    class OpenCVDnnRuntimeParametersBuilder : public Base
    {
        OpenCVDnnRuntimeParameters& m_Parameters;
    public:
        explicit OpenCVDnnRuntimeParametersBuilder(Base& base,OpenCVDnnRuntimeParameters& parameters):Base{base},m_Parameters{parameters}{}
        OpenCVDnnRuntimeParametersBuilder& backend(const OpenCVBackend& Backend){
            m_Parameters.backend = Backend;
            return *this;
        }
        OpenCVDnnRuntimeParametersBuilder& target(const OpenCVTarget& Target){
            m_Parameters.target = Target;
            return *this;
        }
    };
} 

