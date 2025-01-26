#pragma once
#include "Builder/ParametersBuilderContainer.h"
namespace DnnEngine
{
    template <typename Base>
    class DnnParametersBuilder : public Base
    {
        DnnParameters& m_Parameters;
    public:
        explicit DnnParametersBuilder(Base& base,DnnParameters& parameters):Base{base},m_Parameters{parameters}{}
        
    };
} 

