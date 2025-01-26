#pragma once
namespace DnnEngine
{
    enum class OpenCVBackend{
        BACKEND_DEFAULT = cv::dnn::DNN_BACKEND_DEFAULT,
        BACKEND_CUDA = cv::dnn::DNN_BACKEND_CUDA,
        BACKEND_OPENVINO = cv::dnn::DNN_BACKEND_INFERENCE_ENGINE,
        BACKEND_OPENCV = cv::dnn::DNN_BACKEND_OPENCV
    };
    enum class OpenCVTarget{
        TARGET_CPU = cv::dnn::DNN_TARGET_CPU,
        TARGET_OPENCL = cv::dnn::DNN_TARGET_OPENCL,
        TARGET_OPENCL_FP16 = cv::dnn::DNN_TARGET_OPENCL_FP16,
        TARGET_CUDA = cv::dnn::DNN_TARGET_CUDA,
        TARGET_CUDA_FP16 = cv::dnn::DNN_TARGET_CUDA_FP16,
    };

    struct OpenCVDnnInputParameters
    {
        cv::Size inputSize = cv::Size{0,0};
        double scaleFactor = 1.0;
        cv::Scalar mean =cv::Scalar{0,0,0};
        bool swapRB=true;
        bool crop=false;
    };

    struct OpenCVDnnRuntimeParameters{
        OpenCVTarget target;
        OpenCVBackend backend;
    };

    enum class OpenCVModelFileType{
        DARKNET
        // ONNX for example we can add ONNX support
    };

    struct OpenCVDnnDarknetModelPath{
        std::string cfgFilePath;
        std::string weightsFilePath;
    };
    typedef std::variant<std::monostate,OpenCVDnnDarknetModelPath> OpenCVDnnModelPath;
    
    struct OpenCVDnnParameters
    {
        OpenCVDnnModelPath model;
        OpenCVDnnInputParameters inputParameters;
        OpenCVDnnRuntimeParameters runtimeParameters;
    };



    inline std::ostream& operator<<(std::ostream& os, const OpenCVDnnDarknetModelPath& obj) {    

        os <<"OpenCVDnnDarknetModelPath::Start"<<std::endl;    
        os<<"cfg: "<<obj.cfgFilePath<<" weights: "<<obj.weightsFilePath<<std::endl;
        os <<"OpenCVDnnDarknetModelPath::End"<<std::endl;
        return os;
    }

    inline std::ostream& operator<<(std::ostream& os, const OpenCVDnnModelPath& obj) {    

        os <<"OpenCVDnnModelPath::Start"<<std::endl;    
        if (std::holds_alternative<OpenCVDnnDarknetModelPath>(obj)) {
            os << std::get<OpenCVDnnDarknetModelPath>(obj) << std::endl;
        } else {
            os << "OpenCVDnnModelPath is Empty" << std::endl;
        }   
        os <<"OpenCVDnnModelPath::End"<<std::endl;
        return os;
    }

    inline std::ostream& operator<<(std::ostream& os, const OpenCVDnnInputParameters& params)
    {
        os <<"OpenCVDnnInputParameters::Start"<<std::endl;
        os << "Input Size: " << params.inputSize << std::endl;
        os << "Scale Factor: " << params.scaleFactor << std::endl;
        os << "Mean: " << params.mean << std::endl;
        os << "Swap RB: " << params.swapRB << std::endl;
        os << "Crop: " << params.crop << std::endl;
        os <<"OpenCVDnnInputParameters::End"<<std::endl;
        return os;
    }

    inline std::ostream& operator<<(std::ostream& os, const OpenCVDnnRuntimeParameters& params)
    {
        os <<"OpenCVDnnRuntimeParameters::Start"<<std::endl;
        os << "Target: " << static_cast<int>(params.target) << std::endl;
        os << "Backend: " << static_cast<int>(params.backend) << std::endl;
        os <<"OpenCVDnnRuntimeParameters::End"<<std::endl;
        return os;
    }

    inline std::ostream& operator<<(std::ostream& os, const OpenCVDnnParameters& params)
    {
        os <<"OpenCVDnnParameters::Start"<<std::endl;
        os << "Model: " << params.model << std::endl;
        os << "Input Parameters: " << params.inputParameters << std::endl;
        os << "Runtime Parameters: " << params.runtimeParameters << std::endl;
        os <<"OpenCVDnnParameters::End"<<std::endl;
        return os;
    }
} 
