#include "Detection/BoundingBoxBaseObjectDetection.h"
namespace DnnEngine
{   
    BoundingBoxBaseObjectDetection::BoundingBoxBaseObjectDetection(const DnnParameters& dnnParameters,
            const std::optional<std::string>& classNamesFilePath,
            const std::optional<std::string>& classColorsFilePath):
        BaseObjectDetection{dnnParameters,classNamesFilePath,classColorsFilePath}
    {

    }
    void BoundingBoxBaseObjectDetection::drawClasses(cv::Mat& frame,const std::vector<ObjectClass>& classes)const{
        const bool isClassColorsEmpty = m_ClassColors.empty();
        for(const auto& object : classes){
            const cv::Rect2d& box = std::get<cv::Rect2d>(object.area);
            const int& classId = object.id;
            const float& confidence = object.confidence;
            const std::string& className = object.name;

            cv::Scalar color = isClassColorsEmpty ? cv::Scalar(0,255,0) : cv::Scalar(m_ClassColors[classId][2],m_ClassColors[classId][1],m_ClassColors[classId][0]);
            cv::rectangle(frame,box,color,3);
            std::string label = cv::format("%s <%.2f>", className.c_str(), confidence);

            int baseLine;
            cv::Size labelSize = cv::getTextSize(label, cv::FONT_HERSHEY_SIMPLEX, 0.5, 1, &baseLine);
            auto top = std::max(box.y, static_cast<double>(labelSize.height));
            cv::putText(frame, label, cv::Point(box.x, top - 10), cv::FONT_HERSHEY_SIMPLEX, 0.5, color, 1);
        }
    }
} 
