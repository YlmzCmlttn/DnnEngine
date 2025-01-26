#pragma once
namespace DnnEngine
{
    class IStream
    {
    public:
        virtual void operator>>(cv::Mat&) = 0;
        virtual bool getFrame(cv::Mat&)=0;
        virtual bool isOpened()const=0;
        virtual ~IStream()=default;
    };
} 
