#pragma once
#include "DnnParametersBuilder/DnnParametersBuilderFactory.h"
#include "ObjectDetectionParametersBuilder/ObjectDetectionParametersBuilderFactory.h"

namespace DnnEngine{
    template<typename T>
    class AbstractParametersBuilder
    {
    public: 
        T& m_Parameters;
        AbstractParametersBuilder(T& parameters):m_Parameters{parameters}{};        
        inline operator T(){return m_Parameters;}

        
        template <DnnMethod method, typename U = T>
        auto Dnn() -> std::enable_if_t<std::is_same_v<U, DnnParameters>, decltype(DnnParametersBuilderFactory<AbstractParametersBuilder<DnnParameters>>::template Create<method>(*this, m_Parameters))> {
            return DnnParametersBuilderFactory<AbstractParametersBuilder<DnnParameters>>::template Create<method>(*this, m_Parameters);
        }

        template <ObjectDetectionMethod method, typename U = T>
        auto ObjectDetection() -> std::enable_if_t<std::is_same_v<U, ObjectDetectionParameters>, decltype(ObjectDetectionParametersBuilderFactory<AbstractParametersBuilder<ObjectDetectionParameters>>::template Create<method>(*this, m_Parameters))> {
            return ObjectDetectionParametersBuilderFactory<AbstractParametersBuilder<ObjectDetectionParameters>>::template Create<method>(*this, m_Parameters);
        }
    };
}

