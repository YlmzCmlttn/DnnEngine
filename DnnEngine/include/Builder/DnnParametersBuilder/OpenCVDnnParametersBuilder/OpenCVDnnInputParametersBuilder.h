#pragma once
#include "Builder/ParametersBuilderContainer.h"
namespace DnnEngine
{
    template <typename Base>
    class OpenCVDnnInputParametersBuilder : public Base
    {
        OpenCVDnnInputParameters& m_Parameters;
    public:
        explicit OpenCVDnnInputParametersBuilder(Base& base,OpenCVDnnInputParameters& parameters):Base{base},m_Parameters{parameters}{}
        OpenCVDnnInputParametersBuilder& inputSize(const cv::Size& InputSize){
            m_Parameters.inputSize=InputSize;
            return *this;
        }
        OpenCVDnnInputParametersBuilder& scaleFactor(const double& ScaleFactor){
            m_Parameters.scaleFactor=ScaleFactor;
            return *this;
        }
        OpenCVDnnInputParametersBuilder& mean(const cv::Scalar& Mean){
            m_Parameters.mean=Mean;
            return *this;
        }
        OpenCVDnnInputParametersBuilder& swapRB(const bool& SwapRB){
            m_Parameters.swapRB=SwapRB;
            return *this;
        }
        OpenCVDnnInputParametersBuilder& crop(const bool& Crop){
            m_Parameters.crop=Crop;
            return *this;
        }
    };
} 

