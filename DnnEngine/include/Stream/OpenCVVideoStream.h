#pragma once
#include "IStream.h"
namespace DnnEngine
{
    class OpenCVVideoStream : public IStream
    {
        cv::VideoCapture m_Cap;        
        bool open(const std::string&);
    public:
        OpenCVVideoStream()=default;
        OpenCVVideoStream(const std::string&);
        
        virtual void operator>>(cv::Mat&) override;
        virtual bool getFrame(cv::Mat&) override;
        virtual bool isOpened()const override;
        virtual ~OpenCVVideoStream() ;
    };
} 
