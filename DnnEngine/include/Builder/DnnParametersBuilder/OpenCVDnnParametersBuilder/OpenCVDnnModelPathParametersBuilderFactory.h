#pragma once
#include "OpenCVDnnModelDarknetPathParametersBuilder.h"
#include "OpenCVDnnModelPathParametersBuilder.h"
namespace DnnEngine
{
    template <typename Base>
    class OpenCVDnnModelPathParametersBuilderFactory
    {
    public:
        template <OpenCVModelFileType method>
        static auto Create(Base& base, OpenCVDnnModelPath& parameters)
        {
            OpenCVDnnModelPathParametersBuilder<Base> openCVDnnModelPathBuilder{base, parameters };
            if constexpr (method == OpenCVModelFileType::DARKNET)
            {
                if (std::holds_alternative<OpenCVDnnDarknetModelPath>(parameters)){
                    OpenCVDnnDarknetModelPath& darknetModelPath =std::get<OpenCVDnnDarknetModelPath>(parameters);
                    return OpenCVDnnModelDarknetPathParametersBuilder<OpenCVDnnModelPathParametersBuilder<Base>>{openCVDnnModelPathBuilder, darknetModelPath};    
                }
                parameters = OpenCVDnnDarknetModelPath{};
                OpenCVDnnDarknetModelPath& darknetModelPath =std::get<OpenCVDnnDarknetModelPath>(parameters);
                return OpenCVDnnModelDarknetPathParametersBuilder<OpenCVDnnModelPathParametersBuilder<Base>>{openCVDnnModelPathBuilder, darknetModelPath};
            }
        }

        static auto Get(Base& base, OpenCVDnnModelPath& parameters)
        {
            OpenCVDnnModelPathParametersBuilder<Base> openCVDnnModelPathBuilder{base, parameters };
            if (std::holds_alternative<OpenCVDnnDarknetModelPath>(parameters)){
                OpenCVDnnDarknetModelPath& darknetModelPath =std::get<OpenCVDnnDarknetModelPath>(parameters);
                return OpenCVDnnModelDarknetPathParametersBuilder<OpenCVDnnModelPathParametersBuilder<Base>>{openCVDnnModelPathBuilder, darknetModelPath};    
            }else {
                throw std::runtime_error("Unsupported model type probabaly you did not set model file type yet.");
            }
        }
    };
}
