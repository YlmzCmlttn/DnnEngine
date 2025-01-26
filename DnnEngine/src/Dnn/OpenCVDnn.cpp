#include "Dnn/OpenCVDnn.h"
#include "Core/Exception.h"

namespace DnnEngine
{
    OpenCVDnn::OpenCVDnn(const OpenCVDnnParameters& parameters):m_InputParameters{parameters.inputParameters}
    {
        setParameters(parameters);
    }

    void OpenCVDnn::setParameters(const OpenCVDnnParameters& parameters){
        readNet(parameters.model);
        setRunTimeParameters(parameters.runtimeParameters);
    }

    void OpenCVDnn::readNet(const OpenCVDnnModelPath& model){
        if (std::holds_alternative<OpenCVDnnDarknetModelPath>(model)) {
            const auto& path = std::get<OpenCVDnnDarknetModelPath>(model);
            m_Net = cv::dnn::readNetFromDarknet(path.cfgFilePath,path.weightsFilePath);
        }else{
            throw Exception("OpenCVDnnModelPath is not initialized");
        }
        m_OutLayersNames = m_Net.getUnconnectedOutLayersNames();
    }
    void OpenCVDnn::setRunTimeParameters(const OpenCVDnnRuntimeParameters& runtimeParameters){
        setTarget(runtimeParameters.target);
        setBackend(runtimeParameters.backend);
    }
    void OpenCVDnn::setTarget(const OpenCVTarget& target){
        m_Net.setPreferableTarget(static_cast<std::underlying_type_t<OpenCVTarget>>(target));
    }
    void OpenCVDnn::setBackend(const OpenCVBackend& backend){
        m_Net.setPreferableBackend(static_cast<std::underlying_type_t<OpenCVBackend>>(backend));
    }
    std::vector<std::vector<cv::Mat>> OpenCVDnn::forward(){
        std::vector<std::vector<cv::Mat>> output;
        m_Net.forward(output,m_OutLayersNames);
        return output;
    }
    cv::Mat OpenCVDnn::prepareInput(const cv::Mat& frame,const OpenCVDnnInputParameters& inputParameters){
        return cv::dnn::blobFromImage(frame, inputParameters.scaleFactor, inputParameters.inputSize, inputParameters.mean, inputParameters.swapRB, inputParameters.crop);
    }
    std::vector<std::vector<cv::Mat>> OpenCVDnn::forward(const cv::Mat& frame){
        m_Net.setInput(prepareInput(frame,m_InputParameters));
        return forward();
    }
} 
