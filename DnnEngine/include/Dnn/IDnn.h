#pragma once
#include "DnnParameters.h"
namespace DnnEngine{
    class IDnn{
    public:
        virtual std::vector<std::vector<cv::Mat>> forward(const cv::Mat& frame)=0;
        virtual const cv::Size& getInputSize()const=0;
        virtual ~IDnn()=default;
    };
}