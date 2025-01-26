#pragma once
#include "Detection/ObjectDetectionContainers.h"
namespace DnnEngine{
    struct YoloThresholdParameters{
        float objectnessThreshold=0.f;
        float classConfidenceThreshold=0.f;
        float nmsThreshold=0.f;
    };

    struct YoloObjectDetectionParameters{
        YoloThresholdParameters thresholdParameters;
    };   

    inline std::ostream& operator<<(std::ostream& os, const YoloObjectDetectionParameters& params)
    {
        os << "YoloObjectDetectionParameters::Start" << std::endl;
        os << "Objectness Threshold: " << params.thresholdParameters.objectnessThreshold << std::endl;
        os << "Class Confidence Threshold: " << params.thresholdParameters.classConfidenceThreshold << std::endl;
        os << "NMS Threshold: " << params.thresholdParameters.nmsThreshold << std::endl;
        os << "YoloObjectDetectionParameters::End" << std::endl;
        return os;
    }
}