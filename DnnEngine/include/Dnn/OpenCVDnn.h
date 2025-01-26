#pragma once
#include "IDnn.h"
#include "OpenCVDnnParameters.h"
namespace DnnEngine
{
    class OpenCVDnn final : public IDnn
    {
    private:
        const OpenCVDnnInputParameters m_InputParameters;        
        cv::dnn::Net m_Net;
        std::vector<cv::String> m_OutLayersNames;
        void setParameters(const OpenCVDnnParameters& parameters);
        void readNet(const OpenCVDnnModelPath& model);
        void setRunTimeParameters(const OpenCVDnnRuntimeParameters& runtimeParameters);
        void setTarget(const OpenCVTarget& target);
        void setBackend(const OpenCVBackend& backend);
        cv::Mat prepareInput(const cv::Mat& frame,const OpenCVDnnInputParameters& inputParameters);
        std::vector<std::vector<cv::Mat>> forward();
    public:
        OpenCVDnn(const OpenCVDnnParameters& parameters);
        virtual std::vector<std::vector<cv::Mat>> forward(const cv::Mat& frame)override;
        virtual inline const cv::Size& getInputSize()const override{return m_InputParameters.inputSize;};
        virtual ~OpenCVDnn()=default;
    };
} 
