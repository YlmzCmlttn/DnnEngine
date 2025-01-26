#pragma once
#include "ObjectDetectionParametersBuilder.h"
#include "BoundingBoxObjectDetectionParametersBuilder/BoundingBoxObjectDetectionParametersBuilder.h"
namespace DnnEngine
{
    template <typename Base>
    class ObjectDetectionParametersBuilderFactory
    {
    public:
        template <ObjectDetectionMethod method>
        static auto Create(Base& base, ObjectDetectionParameters& parameters)
        {
            ObjectDetectionParametersBuilder<Base> objectDetectionParameterBuilder{base, parameters };
            if constexpr (method == ObjectDetectionMethod::BoundingBoxes)
            {
                if (std::holds_alternative<BoundingBoxObjectDetectionParameters>(parameters.detectionParameters)){
                    return BoundingBoxObjectDetectionParametersBuilder<ObjectDetectionParametersBuilder<Base>>{objectDetectionParameterBuilder, std::get<BoundingBoxObjectDetectionParameters>(parameters.detectionParameters)};
                }
                parameters.detectionParameters = BoundingBoxObjectDetectionParameters{};
                return BoundingBoxObjectDetectionParametersBuilder<ObjectDetectionParametersBuilder<Base>>{objectDetectionParameterBuilder, std::get<BoundingBoxObjectDetectionParameters>(parameters.detectionParameters)};
            }
        }

        static auto Get(Base& base, ObjectDetectionParameters& parameters) {
            ObjectDetectionParametersBuilder<Base> objectDetectionParameterBuilder{base, parameters};
            if (std::holds_alternative<BoundingBoxObjectDetectionParameters>(parameters.detectionParameters)) {
                return BoundingBoxObjectDetectionParametersBuilder<ObjectDetectionParametersBuilder<Base>>{objectDetectionParameterBuilder, std::get<BoundingBoxObjectDetectionParameters>(parameters.detectionParameters)};
            } else {
                throw std::runtime_error("Unsupported DNN method type. You probably did not set DNN method type yet.");
            }
        }
    };
}
