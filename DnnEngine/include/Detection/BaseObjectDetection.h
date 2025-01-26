#pragma once
#include "Detection/IObjectDetection.h"
#include "Dnn/IDnn.h"
#include "Detection/ObjectDetectionContainers.h"
namespace DnnEngine{
    class BaseObjectDetection : public IObjectDetection{
    protected:
        std::unique_ptr<IDnn> m_Dnn;
        std::vector<std::string> m_ClassNames;
        mutable cv::Size m_FrameSize;
        BaseObjectDetection(const DnnParameters& dnnParameters,
            const std::optional<std::string>& classNamesFilePath = std::nullopt,
            const std::optional<std::string>& classColorsFilePath = std::nullopt);
        
        inline virtual cv::Mat preProcess(const cv::Mat& frame)const{
            m_FrameSize = frame.size();
            return frame;
        };
        inline virtual std::vector<std::vector<cv::Mat>> process(const cv::Mat& frame)const{return m_Dnn->forward(frame);};
        virtual std::vector<ObjectClass> postProcess(const std::vector<std::vector<cv::Mat>>& output)const =0;
        virtual void postProcessAndDraw(const std::vector<std::vector<cv::Mat>>& output,cv::Mat& frame)const =0;
        void checkClassNames(const std::size_t& numberOfClasses);
        std::vector<std::array<int, 3>> m_ClassColors;
    private:
        void setClassNames(const std::optional<std::string>& classNamesFilePath);
        void setClassColors(const std::optional<std::string>& classNamesFilePath);
    public:
        virtual std::vector<ObjectClass> detect(const cv::Mat& frame)const override;
        virtual void detectAndDraw(cv::Mat& frame)const override;
        virtual void drawClasses(cv::Mat& frame,const std::vector<ObjectClass>& classes)const=0;
        virtual ~BaseObjectDetection()=default;
    };
}