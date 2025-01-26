#include "Core/Application.h"
#include "Stream/Stream.h"
#include "Stream/StreamThread.h"
#include "Builder/ParametersBuilder.h"
#include "Detection/ObjectDetectionFactory.h"
#include "Stream/OpenCVVideoStream.h"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <video_path>" << std::endl;
        return 1;
    }
    const char* video_filename = argv[1];
    DnnEngine::ObjectDetectionParameters objectDetectionParameters = DnnEngine::ParametersBuilder<DnnEngine::ObjectDetectionParameters>::build()
                                    .ObjectDetection<DnnEngine::ObjectDetectionMethod::BoundingBoxes>()
                                        .Model<DnnEngine::BoundingBoxDetectionModelType::Yolo>()
                                            .Threshold()
                                                .objectness(0.3)
                                                .classConfidence(0.5)
                                                .nms(0.4)
                                        .Dnn<DnnEngine::DnnMethod::OpenCV>()
                                            .Parameters()
                                                .inputSize(cv::Size(128,64))
                                                .scaleFactor(1./255)
                                                .mean(cv::Scalar(0,0,0))
                                            .Runtime()                        
                                                .backend(DnnEngine::OpenCVBackend::BACKEND_DEFAULT)
                                                .target(DnnEngine::OpenCVTarget::TARGET_CPU)                                            
                                            .ModelPath<DnnEngine::OpenCVModelFileType::DARKNET>()
                                                .cfgPath(std::string(MODEL_PATH)+"yolov3.cfg")
                                                .weightsPath(std::string(MODEL_PATH)+"yolov3.weights")
                                        .classNamesFilePath(std::string(MODEL_PATH)+"coco_classes.txt")
                                        .classColorsFilePath(std::string(MODEL_PATH)+"coco_colors.txt");

    std::unique_ptr<DnnEngine::IObjectDetection> yoloObjectDetection = DnnEngine::ObjectDetectionFactory::create(objectDetectionParameters);
    
    auto stream = std::make_unique<DnnEngine::StreamThread<DnnEngine::OpenCVVideoStream,true,true>>(video_filename);
    stream->setLoopInterval(std::chrono::milliseconds(33));

    DnnEngine::Application* app = DnnEngine::createApplication(DnnEngine::WindowProps{"DNN_ENGINE C++ Tech Test",640*2,360});
    cv::Mat frame,frameProcess;
    while(app->isRunning()){
        stream->getFrame(frame);
        frameProcess = frame.clone();
        yoloObjectDetection->detectAndDraw(frameProcess);
        cv::hconcat(frame, frameProcess, frame);
        app->showImage(frame);
    }
    delete app;
    return 0;
}
