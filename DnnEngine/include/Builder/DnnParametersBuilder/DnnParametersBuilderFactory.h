#pragma once
#include "DnnParametersBuilder.h"
#include "OpenCVDnnParametersBuilder/OpenCVDnnParametersBuilder.h"
namespace DnnEngine
{
    template <typename Base>
    class DnnParametersBuilderFactory
    {
    public:
        template <DnnMethod method>
        static auto Create(Base& base, DnnParameters& parameters)
        {
            DnnParametersBuilder<Base> dnnBuilder{base, parameters };
            if constexpr (method == DnnMethod::OpenCV)
            {
                if (std::holds_alternative<OpenCVDnnParameters>(parameters.parameters)){
                    return OpenCVDnnParametersBuilder<DnnParametersBuilder<Base>>{dnnBuilder, std::get<OpenCVDnnParameters>(parameters.parameters)};
                }
                parameters.parameters = OpenCVDnnParameters{};
                return OpenCVDnnParametersBuilder<DnnParametersBuilder<Base>>{dnnBuilder, std::get<OpenCVDnnParameters>(parameters.parameters)};
            }
        }

        static auto Get(Base& base, DnnParameters& parameters) {
            DnnParametersBuilder<Base> dnnBuilder{base, parameters};
            if (std::holds_alternative<OpenCVDnnParameters>(parameters.parameters)) {
                return OpenCVDnnParametersBuilder<DnnParametersBuilder<Base>>{dnnBuilder, std::get<OpenCVDnnParameters>(parameters.parameters)};
            } else {
                throw std::runtime_error("Unsupported DNN method type. You probably did not set DNN method type yet.");
            }
        }
    };
}
