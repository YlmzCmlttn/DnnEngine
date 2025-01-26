#pragma once
#include "Detection/ObjectDetectionContainers.h"
namespace DnnEngine
{
    class IObjectDetection{
    public:
        virtual std::vector<ObjectClass> detect(const cv::Mat& frame)const= 0;
        virtual void detectAndDraw(cv::Mat& frame)const = 0;
        virtual void drawClasses(cv::Mat& frame,const std::vector<ObjectClass>& classes)const=0;
        virtual ~IObjectDetection()=default;
    };
} 
