#pragma once
#include "Builder/ParametersBuilderContainer.h"
namespace DnnEngine
{
    template <typename Base>
    class YoloObjectDetectionThresholdParametersBuilder : public Base
    {
    protected:
        YoloThresholdParameters& m_Parameters;
    public:
        explicit YoloObjectDetectionThresholdParametersBuilder(Base& base,YoloThresholdParameters& parameters):Base(base),m_Parameters{parameters}{}

        YoloObjectDetectionThresholdParametersBuilder& setThreshold(YoloThresholdParameters& thresholds){
            m_Parameters = thresholds;
            return *this;
        }
        YoloObjectDetectionThresholdParametersBuilder& setThreshold(float objectness,float classConfidence,float nms){
            m_Parameters = YoloThresholdParameters{objectness,classConfidence,nms};
            return *this;
        }
        YoloObjectDetectionThresholdParametersBuilder& objectness(float objectness){
            m_Parameters.objectnessThreshold = objectness;
            return *this;
        }
        YoloObjectDetectionThresholdParametersBuilder& classConfidence(float classConfidence){
            m_Parameters.classConfidenceThreshold = classConfidence;
            return *this;
        }
        YoloObjectDetectionThresholdParametersBuilder& nms(float nms){
            m_Parameters.nmsThreshold = nms;
            return *this;
        }
    };
} 

