#include "Stream/Stream.h"
#include "Stream/StreamThread.h"
#include "Stream/OpenCVVideoStream.h"

namespace DnnEngine {
    template<>
    std::unique_ptr<IStream> Stream::createVideoStream<StreamBackend::OpenCV>(const std::string& filename) {
        return std::make_unique<OpenCVVideoStream>(filename);
    }
    template<>
    std::unique_ptr<IStream> Stream::createVideoStreamThread<StreamBackend::OpenCV>(const std::string& filename) {
        return std::make_unique<StreamThread<OpenCVVideoStream,true,true>>(filename);
    }

} 