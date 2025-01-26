#include "Core/Application.h"
#include "Stream/Stream.h"
#include "Stream/StreamThread.h"
#include "Stream/OpenCVVideoStream.h"

int main() {
    
    auto stream = std::make_unique<DnnEngine::StreamThread<DnnEngine::OpenCVVideoStream,true,false /*It won't wait until frame grabbed*/>>(std::string(DATA_PATH)+"test.mp4");
    stream->setLoopInterval(std::chrono::milliseconds(1));

    DnnEngine::Application* app = DnnEngine::createApplication(DnnEngine::WindowProps{"StreamUsage",640,360});
    cv::Mat frame;
    while(app->isRunning()){
        std::cout<<"Running"<<std::endl;
        std::this_thread::sleep_for (std::chrono::milliseconds(100));
        stream->getFrame(frame);
        app->showImage(frame);
    }
    delete app;
    return 0;
}
