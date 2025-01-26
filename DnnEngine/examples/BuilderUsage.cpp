#include "Core/Application.h"
#include "Stream/Stream.h"
#include "Stream/StreamThread.h"
#include "Builder/ParametersBuilder.h"
#include "Detection/ObjectDetectionFactory.h"
#include "Stream/OpenCVVideoStream.h"

int main() {
    DnnEngine::ObjectDetectionParameters objectDetectionParameters = DnnEngine::ParametersBuilder<DnnEngine::ObjectDetectionParameters>::build()
                                    .ObjectDetection<DnnEngine::ObjectDetectionMethod::BoundingBoxes>()
                                        .Model<DnnEngine::BoundingBoxDetectionModelType::Yolo>()
                                            .Threshold()
                                                .objectness(0.5)
                                                .classConfidence(0.2)
                                                .nms(0.5)
                                        .Dnn<DnnEngine::DnnMethod::OpenCV>()
                                            .Parameters()
                                                .inputSize(cv::Size(128,64))
                                                .scaleFactor(1./255)
                                                .mean(cv::Scalar(0,0,0))
                                            .Runtime()                        
                                                .backend(DnnEngine::OpenCVBackend::BACKEND_DEFAULT)
                                                .target(DnnEngine::OpenCVTarget::TARGET_CPU)                                            
                                            .ModelPath<DnnEngine::OpenCVModelFileType::DARKNET>()
                                                .cfgPath("../../../model/yolov3.cfg")
                                                .weightsPath("../../../model/yolov3.weights")
                                        .classNamesFilePath("../../../model/coco_classes.txt")
                                        .classColorsFilePath("../../../model/coco_colors.txt");
    {
        DnnEngine::DnnParameters dnnParameters = DnnEngine::ParametersBuilder<DnnEngine::DnnParameters>::build()
                                        .Dnn<DnnEngine::DnnMethod::OpenCV>()
                                            .Parameters()
                                                .inputSize(cv::Size(128,64))
                                                .scaleFactor(1./255)
                                                .mean(cv::Scalar(0,0,0))
                                            .Runtime()                        
                                                .backend(DnnEngine::OpenCVBackend::BACKEND_DEFAULT)
                                                .target(DnnEngine::OpenCVTarget::TARGET_CPU)                                            
                                            .ModelPath<DnnEngine::OpenCVModelFileType::DARKNET>()
                                                .cfgPath("../../../model/yolov3.cfg")
                                                .weightsPath("../../../model/yolov3.weights");
        std::cout<<dnnParameters<<std::endl;    
    }

    {
        //Also you can use by one by
        DnnEngine::ParametersBuilder<DnnEngine::DnnParameters> dnnParameters = DnnEngine::ParametersBuilder<DnnEngine::DnnParameters>::build();
        dnnParameters.Dnn<DnnEngine::DnnMethod::OpenCV>()
            .ModelPath<DnnEngine::OpenCVModelFileType::DARKNET>()
                .cfgPath("../../../model/yolov3.cfg")
                .weightsPath("../../../model/yolov3.weights")
            .Runtime()
                .backend(DnnEngine::OpenCVBackend::BACKEND_DEFAULT)
                .target(DnnEngine::OpenCVTarget::TARGET_CPU);
        auto parameter = dnnParameters.Dnn<DnnEngine::DnnMethod::OpenCV>().Parameters();
        parameter.inputSize(cv::Size(128,64));
        parameter.scaleFactor(1./255);
        parameter.mean(cv::Scalar(0,0,0));        

        std::cout<<(DnnEngine::DnnParameters)dnnParameters<<std::endl;
    }   

    
    return 0;
}
