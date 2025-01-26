#include "Core/Application.h"
#include "Stream/Stream.h"
#include "Stream/StreamThread.h"
#include "Stream/OpenCVVideoStream.h"

int main() {
    
    auto stream = std::make_unique<DnnEngine::StreamThread<DnnEngine::OpenCVVideoStream,false/*It will get same frame again will not wait new frame*/,false /*It won't wait until frame grabbed*/>>(std::string(DATA_PATH)+"test.mp4");
    stream->setLoopInterval(std::chrono::seconds(1));

    DnnEngine::Application* app = DnnEngine::createApplication(DnnEngine::WindowProps{"StreamUsage",640,360});
    cv::Mat frame;
    while(app->isRunning()){
        std::cout<<"Running"<<std::endl;
        stream->getFrame(frame);
        app->showImage(frame);
    }
    delete app;
    return 0;
}
