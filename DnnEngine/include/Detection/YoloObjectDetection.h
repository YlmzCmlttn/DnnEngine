#pragma once
#include "Detection/BoundingBoxBaseObjectDetection.h"
#include "Dnn/IDnn.h"
#include "Detection/YoloObjectDetectionParameters.h"
namespace DnnEngine{

    class YoloObjectDetection final : public BoundingBoxBaseObjectDetection{
    private:
        const YoloThresholdParameters m_YoloThresholdParameters;
    public:
        YoloObjectDetection(
            const DnnParameters& dnnParameters,
            const YoloObjectDetectionParameters& yoloObjectDetectionParameters,
            const std::optional<std::string>& classNamesFilePath = std::nullopt,
            const std::optional<std::string>& classColorsFilePath = std::nullopt
            );

        
        virtual ~YoloObjectDetection()=default;
    private:
        virtual std::vector<ObjectClass> postProcess(const std::vector<std::vector<cv::Mat>>& output)const override;
        virtual void postProcessAndDraw(const std::vector<std::vector<cv::Mat>>& output,cv::Mat& frame)const override;

        std::vector<ObjectClass> nms(const std::vector<cv::Rect2d>& boxes,
            const std::vector<float>& confidences,
            const std::vector<int>& classIds)const;

        void nmsAndDraw(const std::vector<cv::Rect2d>& boxes,
            const std::vector<float>& confidences,
            const std::vector<int>& classIds,
            cv::Mat& frame)const;

        void processOutput(const std::vector<std::vector<cv::Mat>>& output, std::vector<cv::Rect2d>& boxes,
            std::vector<float>& confidences,
            std::vector<int>& classIds)const;
    };
}