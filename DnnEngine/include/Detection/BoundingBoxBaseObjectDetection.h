#pragma once
#include "Detection/BaseObjectDetection.h"
namespace DnnEngine{
    class BoundingBoxBaseObjectDetection : public BaseObjectDetection{
    protected:
        BoundingBoxBaseObjectDetection(const DnnParameters& dnnParameters,
            const std::optional<std::string>& classNamesFilePath = std::nullopt,
            const std::optional<std::string>& classColorsFilePath = std::nullopt);
    public:
        virtual void drawClasses(cv::Mat& frame,const std::vector<ObjectClass>& classes)const override;
        virtual ~BoundingBoxBaseObjectDetection()=default;
    };
}