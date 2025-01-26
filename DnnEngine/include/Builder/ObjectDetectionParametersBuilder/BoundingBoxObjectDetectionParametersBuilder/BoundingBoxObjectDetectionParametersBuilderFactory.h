#pragma once
#include "BoundingBoxObjectDetectionModelParametersBuilder.h"
#include "YoloObjectDetectionParametersBuilder/YoloObjectDetectionParametersBuilder.h"
namespace DnnEngine
{
    template <typename Base>
    class BoundingBoxObjectDetectionParametersBuilderFactory
    {
    public:
        template <BoundingBoxDetectionModelType method>
        static auto Create(Base& base, BoundingBoxObjectDetectionModelParameters& parameters)
        {
            BoundingBoxObjectDetectionModelParametersBuilder<Base> boundingBoxObjectDetectionParametersBuilder{base, parameters };
            if constexpr (method == BoundingBoxDetectionModelType::Yolo)
            {
                if (std::holds_alternative<YoloObjectDetectionParameters>(parameters)){
                    return YoloObjectDetectionParametersBuilder<BoundingBoxObjectDetectionModelParametersBuilder<Base>>{boundingBoxObjectDetectionParametersBuilder, std::get<YoloObjectDetectionParameters>(parameters)};
                }
                parameters = YoloObjectDetectionParameters{};
                return YoloObjectDetectionParametersBuilder<BoundingBoxObjectDetectionModelParametersBuilder<Base>>{boundingBoxObjectDetectionParametersBuilder, std::get<YoloObjectDetectionParameters>(parameters)};
            }
        }

        static auto Get(Base& base, BoundingBoxObjectDetectionModelParameters& parameters) {
            BoundingBoxObjectDetectionModelParametersBuilder<Base> boundingBoxObjectDetectionParametersBuilder{base, parameters};
            if (std::holds_alternative<YoloObjectDetectionParameters>(parameters)) {
                return YoloObjectDetectionParametersBuilder<BoundingBoxObjectDetectionModelParametersBuilder<Base>>{boundingBoxObjectDetectionParametersBuilder, std::get<YoloObjectDetectionParameters>(parameters)};
            } else {
                throw std::runtime_error("Unsupported DNN method type. You probably did not set DNN method type yet.");
            }
        }
    };
}
