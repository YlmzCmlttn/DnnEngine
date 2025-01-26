#pragma once
#include "Builder/ParametersBuilderContainer.h"
#include "OpenCVDnnModelPathParametersBuilderFactory.h"
#include "OpenCVDnnRuntimeParametersBuilder.h"
#include "OpenCVDnnInputParametersBuilder.h"

namespace DnnEngine
{
    template <typename Base>
    class OpenCVDnnParametersBuilder : public Base
    {
        OpenCVDnnParameters& m_Parameters;
    public:
        explicit OpenCVDnnParametersBuilder(Base& base,OpenCVDnnParameters& parameters):Base{base},m_Parameters{parameters}{}
        
        template <OpenCVModelFileType modelFileType>
        auto ModelPath(){
            return OpenCVDnnModelPathParametersBuilderFactory<OpenCVDnnParametersBuilder<Base>>::template Create<modelFileType>(*this, m_Parameters.model);
        }
        auto ModelPath(){
            return OpenCVDnnModelPathParametersBuilderFactory<OpenCVDnnParametersBuilder<Base>>::Get(*this, m_Parameters.model);
        }
        OpenCVDnnRuntimeParametersBuilder<OpenCVDnnParametersBuilder<Base>> Runtime(){
            return OpenCVDnnRuntimeParametersBuilder<OpenCVDnnParametersBuilder<Base>>(*this,m_Parameters.runtimeParameters);
        }
        OpenCVDnnInputParametersBuilder<OpenCVDnnParametersBuilder<Base>> Parameters(){
            return OpenCVDnnInputParametersBuilder<OpenCVDnnParametersBuilder<Base>>(*this,m_Parameters.inputParameters);
        }
    };
} 

