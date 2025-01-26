#pragma once
#include "Builder/ParametersBuilderContainer.h"
#include "YoloObjectDetectionThresholdParametersBuilder.h"
namespace DnnEngine
{
    template <typename Base>
    class YoloObjectDetectionParametersBuilder : public Base
    {
        YoloObjectDetectionParameters& m_Parameters;
    public:
        explicit YoloObjectDetectionParametersBuilder(Base& base,YoloObjectDetectionParameters& parameters):Base{base},m_Parameters{parameters}{}

        YoloObjectDetectionThresholdParametersBuilder<YoloObjectDetectionParametersBuilder<Base>> Threshold(){
            return YoloObjectDetectionThresholdParametersBuilder<YoloObjectDetectionParametersBuilder<Base>>{*this,m_Parameters.thresholdParameters};
        }
        
    };
} 

