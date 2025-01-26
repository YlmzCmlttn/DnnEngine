#pragma once
#include "Dnn/DnnParameters.h"
#include "Detection/YoloObjectDetectionParameters.h"
namespace DnnEngine{
    typedef std::variant<std::monostate,YoloObjectDetectionParameters> BoundingBoxObjectDetectionModelParameters;

    struct BoundingBoxObjectDetectionParameters{
        BoundingBoxObjectDetectionModelParameters modelParameters;
    };

    struct ObjectDetectionParameters{
        DnnParameters dnnParameters;
        std::variant<std::monostate,BoundingBoxObjectDetectionParameters> detectionParameters;
        std::optional<std::string> classNamesFilePath;
        std::optional<std::string> classColorsFilePath;
    };
    inline std::ostream& operator<<(std::ostream& os, const BoundingBoxObjectDetectionParameters& params)
    {
        os << "BoundingBoxObjectDetectionParameters::Start" << std::endl;

        os << "Model Parameters: ";
        if (std::holds_alternative<YoloObjectDetectionParameters>(params.modelParameters)) {
            os << std::get<YoloObjectDetectionParameters>(params.modelParameters) << std::endl;
        } else {
            os << "Model Parameters are Empty or Unsupported" << std::endl;
        }

        os << "BoundingBoxObjectDetectionParameters::End" << std::endl;
        return os;
    }

    inline std::ostream& operator<<(std::ostream& os, const ObjectDetectionParameters& params)
    {
        os << "ObjectDetectionParameters::Start" << std::endl;

        os << "Dnn Parameters: " << params.dnnParameters << std::endl;

        os << "Detection Parameters: ";
        if (std::holds_alternative<BoundingBoxObjectDetectionParameters>(params.detectionParameters)) {
            os << std::get<BoundingBoxObjectDetectionParameters>(params.detectionParameters) << std::endl;
        } else {
            os << "Detection Parameters are Empty" << std::endl;
        }

        os << "Class Names File Path: ";
        if (params.classNamesFilePath) {
            os << *params.classNamesFilePath << std::endl;
        } else {
            os << "Not Set" << std::endl;
        }

        os << "Class Colors File Path: ";
        if (params.classColorsFilePath) {
            os << *params.classColorsFilePath << std::endl;
        } else {
            os << "Not Set" << std::endl;
        }

        os << "ObjectDetectionParameters::End" << std::endl;
        return os;
    }
    struct ObjectClass{
        int id;
        std::string name;
        std::variant<cv::Rect2d> area; //Output can be difference for bounding boxes it is rectangle.
        float confidence;
    };

    
}