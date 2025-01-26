#pragma once
#include "Builder/ParametersBuilderContainer.h"
#include "BoundingBoxObjectDetectionParametersBuilderFactory.h"
namespace DnnEngine
{
    template <typename Base>
    class BoundingBoxObjectDetectionParametersBuilder : public Base
    {
        BoundingBoxObjectDetectionParameters& m_Parameters;
    public:
        explicit BoundingBoxObjectDetectionParametersBuilder(Base& base,BoundingBoxObjectDetectionParameters& parameters):Base{base},m_Parameters{parameters}{}
        
        template<BoundingBoxDetectionModelType type>
        auto Model(){
            return BoundingBoxObjectDetectionParametersBuilderFactory<BoundingBoxObjectDetectionParametersBuilder<Base>>::template Create<type>(*this, m_Parameters.modelParameters);
        }

        auto Model(){
            return BoundingBoxObjectDetectionParametersBuilderFactory<BoundingBoxObjectDetectionParametersBuilder<Base>>::Get(*this, m_Parameters.modelParameters);
        }
    };
    
} 
