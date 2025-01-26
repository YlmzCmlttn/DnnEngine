#pragma once
#include "Builder/ParametersBuilderContainer.h"
#include "BoundingBoxObjectDetectionParametersBuilderFactory.h"
namespace DnnEngine
{
    template <typename Base>
    class BoundingBoxObjectDetectionModelParametersBuilder : public Base
    {
        BoundingBoxObjectDetectionModelParameters& m_Parameters;
    public:
        explicit BoundingBoxObjectDetectionModelParametersBuilder(Base& base,BoundingBoxObjectDetectionModelParameters& parameters):Base{base},m_Parameters{parameters}{}        
    };
} 

