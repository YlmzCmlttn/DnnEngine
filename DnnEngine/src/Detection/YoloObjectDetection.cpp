#include "Detection/YoloObjectDetection.h"
namespace DnnEngine
{   

    typedef struct float4 {
        float x;
        float y;
        float z;
        float w;
    } float4;

    YoloObjectDetection::YoloObjectDetection(
            const DnnParameters& dnnParameters,
            const YoloObjectDetectionParameters& yoloObjectDetectionParameters,
            const std::optional<std::string>& classNamesFilePath,
            const std::optional<std::string>& classColorsFilePath):
        BoundingBoxBaseObjectDetection(dnnParameters,classNamesFilePath,classColorsFilePath),
        m_YoloThresholdParameters{yoloObjectDetectionParameters.thresholdParameters}
    {
        const auto output = m_Dnn->forward(cv::Mat::zeros(m_Dnn->getInputSize(),CV_8UC3));
        const std::size_t numberOfClasses = output.front().front().size[output.front().front().dims - 1] - 5;
        checkClassNames(numberOfClasses);
    }



    std::vector<ObjectClass> YoloObjectDetection::nms(const std::vector<cv::Rect2d>& boxes,
        const std::vector<float>& confidences,
        const std::vector<int>& classIds
    )const{
        std::vector<int> indices;
        cv::dnn::NMSBoxes(boxes, confidences, m_YoloThresholdParameters.classConfidenceThreshold, m_YoloThresholdParameters.nmsThreshold, indices);
        std::vector<ObjectClass> objectClasses;
        for (int idx : indices) {
            ObjectClass objectClass;
            objectClass.name = (m_ClassNames.empty()) ? 
                                            "Class" + std::to_string(classIds[idx]) : 
                                            m_ClassNames.at(classIds[idx]);
            objectClass.area = boxes[idx];
            objectClass.confidence = confidences[idx];
            objectClass.id = classIds[idx];
            objectClasses.push_back(std::move(objectClass));
        }
        return objectClasses;   
    }

    void YoloObjectDetection::nmsAndDraw(const std::vector<cv::Rect2d>& boxes,
        const std::vector<float>& confidences,
        const std::vector<int>& classIds,
        cv::Mat& frame
    )const{
        std::vector<int> indices;
        cv::dnn::NMSBoxes(boxes, confidences, m_YoloThresholdParameters.classConfidenceThreshold, m_YoloThresholdParameters.nmsThreshold, indices);
        const bool isClassColorsEmpty = m_ClassColors.empty();
        for (int idx : indices) {
            const cv::Rect2d& box = boxes[idx];
            const int& classId = classIds[idx];
            const float& confidence = confidences[idx];
            cv::Scalar color = isClassColorsEmpty ? cv::Scalar(0,255,0) : cv::Scalar(m_ClassColors[classId][2],m_ClassColors[classId][1],m_ClassColors[classId][0]);
            cv::rectangle(frame,box,color,3);
            std::string className = (m_ClassNames.empty()) ? 
                                            "Class" + std::to_string(classId) : 
                                            m_ClassNames.at(classId);
            std::string label = cv::format("%s <%.2f>", className.c_str(), confidence);

            int baseLine;
            cv::Size labelSize = cv::getTextSize(label, cv::FONT_HERSHEY_SIMPLEX, 0.5, 1, &baseLine);
            auto top = std::max(box.y, static_cast<double>(labelSize.height));
            cv::putText(frame, label, cv::Point(box.x, top - 10), cv::FONT_HERSHEY_SIMPLEX, 0.5, color, 1);
        }
    }

    void YoloObjectDetection::processOutput(const std::vector<std::vector<cv::Mat>>& output, 
            std::vector<cv::Rect2d>& boxes,
            std::vector<float>& confidences,
            std::vector<int>& classIds)const
    {
        for(size_t i=0;i<output.size();i++){
            const cv::Mat& out = output[i][0];
            float* data = (float*)out.data;
            const int& rows = out.rows;
            const int& cols = out.cols;

            for (int j = 0; j < rows; ++j, data += cols) {
                const float objectness = data[4];

                if (objectness > m_YoloThresholdParameters.objectnessThreshold) {
                    
                    cv::Mat scores = out.row(j).colRange(5, cols);
                    cv::Point classIdPoint;
                    double confidence;
                    cv::minMaxLoc(scores, nullptr, &confidence, nullptr, &classIdPoint);

                    if (confidence > m_YoloThresholdParameters.classConfidenceThreshold) {
                        const int& classId = classIdPoint.x;

                        const int centerX = (int)(data[0] * m_FrameSize.width);
                        const int centerY = (int)(data[1] * m_FrameSize.height);
                        int width = (int)(data[2] * m_FrameSize.width);
                        int height = (int)(data[3] * m_FrameSize.height);
                        int left = centerX - width / 2;
                        int top = centerY - height / 2;

                        boxes.emplace_back(left, top, width, height);
                        confidences.push_back(static_cast<float>(confidence));
                        classIds.emplace_back(classId);
                    }
                }
            }
        }
    }
    
    std::vector<ObjectClass> YoloObjectDetection::postProcess(const std::vector<std::vector<cv::Mat>>& output)const{
        std::vector<cv::Rect2d> boxes;
        std::vector<float> confidences;
        std::vector<int> classIds;
        processOutput(output,boxes,confidences,classIds);        
        return nms(boxes,confidences,classIds);
    }
    void YoloObjectDetection::postProcessAndDraw(const std::vector<std::vector<cv::Mat>>& output,cv::Mat& frame)const{
        std::vector<cv::Rect2d> boxes;
        std::vector<float> confidences;
        std::vector<int> classIds;
        processOutput(output,boxes,confidences,classIds);        
        nmsAndDraw(boxes,confidences,classIds,frame);
    }
} 
