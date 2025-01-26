#pragma once
#include "IStream.h"
namespace DnnEngine
{

    enum class StreamBackend{
        OpenCV
    };

    class Stream
    {
    public:
        template<StreamBackend Backend>
        static std::unique_ptr<IStream> createVideoStream(const std::string& filename);
        template<StreamBackend Backend>
        static std::unique_ptr<IStream> createVideoStreamThread(const std::string& filename);        
    };
} 
