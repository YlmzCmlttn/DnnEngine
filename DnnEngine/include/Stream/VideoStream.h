#pragma once
#include "IStream.h"
namespace DnnEngine
{
    class VideoStream : public IStream
    {
    protected:
        VideoStream();
        VideoStream(const std::string&);
        bool open(const std::string&);
    public:
        virtual void operator>>(cv::Mat&) override;
        virtual bool getFrame(cv::Mat&) override;
        virtual bool isOpened() override;
        virtual ~VideoStream();
    };
} 
