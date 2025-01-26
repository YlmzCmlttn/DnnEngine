#pragma once
#include "AbstractParametersBuilder.h"
namespace DnnEngine
{
    template<typename T>
    class ParametersBuilder : public AbstractParametersBuilder<T>
    {
        T parameters;
    public:
        ParametersBuilder(/* args */):AbstractParametersBuilder<T>{parameters}{}
        
        static ParametersBuilder<T> build(){
            return ParametersBuilder<T>{};
        }
    };
} 

