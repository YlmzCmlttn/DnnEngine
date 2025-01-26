#pragma once

#include "Detection/YoloObjectDetection.h"
#include "Detection/IObjectDetection.h"
#include "Core/Assert.h"

namespace DnnEngine
{
    class ObjectDetectionFactory
    {
    private:
        static std::unique_ptr<IObjectDetection> createBoundingBoxDetection(const ObjectDetectionParameters& objectDetectionParameters){
            const BoundingBoxObjectDetectionParameters& parameters = std::get<BoundingBoxObjectDetectionParameters>(objectDetectionParameters.detectionParameters);
            if(std::holds_alternative<YoloObjectDetectionParameters>(parameters.modelParameters)){
                return createYoloDetection(objectDetectionParameters);
            }
            DNN_ENGINE_ASSERT(false,"Only support Yolo based bounding box detection model type");
        }
        static std::unique_ptr<IObjectDetection> createYoloDetection(const ObjectDetectionParameters& objectDetectionParameters){
            const BoundingBoxObjectDetectionParameters& parameters = std::get<BoundingBoxObjectDetectionParameters>(objectDetectionParameters.detectionParameters);
            const YoloObjectDetectionParameters& yoloParameters = std::get<YoloObjectDetectionParameters>(parameters.modelParameters);
            return std::make_unique<YoloObjectDetection>(objectDetectionParameters.dnnParameters,yoloParameters,objectDetectionParameters.classNamesFilePath,objectDetectionParameters.classColorsFilePath);            
        }
    public:
        static std::unique_ptr<IObjectDetection> create(const ObjectDetectionParameters& objectDetectionParameters){
            if(std::holds_alternative<BoundingBoxObjectDetectionParameters>(objectDetectionParameters.detectionParameters)){
                return createBoundingBoxDetection(objectDetectionParameters);
            }
            DNN_ENGINE_ASSERT(false,"Only support boundingBoxes detection type");
        }
    };
} 
