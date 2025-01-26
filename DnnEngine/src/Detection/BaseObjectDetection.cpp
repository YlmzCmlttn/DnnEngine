#include "Detection/BaseObjectDetection.h"
#include "Dnn/DnnFactory.h"
namespace DnnEngine
{   
    BaseObjectDetection::BaseObjectDetection(const DnnParameters& dnnParameters,
            const std::optional<std::string>& classNamesFilePath,
            const std::optional<std::string>& classColorsFilePath):
        m_Dnn{DnnFactory::create(dnnParameters)}
    {
        setClassNames(classNamesFilePath);
        setClassColors(classColorsFilePath);
    }
    std::vector<ObjectClass> BaseObjectDetection::detect(const cv::Mat& frame)const{
        return postProcess(process(preProcess(frame)));
    }
    void BaseObjectDetection::detectAndDraw(cv::Mat& frame)const{
        postProcessAndDraw(process(preProcess(frame)),frame);
    }
    void BaseObjectDetection::checkClassNames(const std::size_t& numberOfClasses){
        if (m_ClassNames.empty()) {
            m_ClassNames.resize(numberOfClasses);
            for(std::size_t i = 0; i < numberOfClasses; ++i) {
                m_ClassNames[i] = "classID" + std::to_string(i);
            }
        }else if(numberOfClasses != m_ClassNames.size()) {
            std::cerr << "Number of classes and size of class names do not match. Using default naming." << std::endl;
            m_ClassColors.clear();
        }
        if(numberOfClasses != m_ClassColors.size()) {
            std::cerr << "Number of classes and size of class names do not match. Resizing class names vector." << std::endl;
            m_ClassColors.clear();
        }
    }

    void BaseObjectDetection::setClassNames(const std::optional<std::string>& classNamesFilePath){
        if(const auto& filePathOpt = classNamesFilePath){
            std::ifstream file(*filePathOpt);
            if(file){
                std::string line;
                while (std::getline(file, line)) {
                    m_ClassNames.push_back(std::move(line));  // Use std::move for efficiency
                }
            }else{
                std::cerr << "Unable to open class name file: " << *filePathOpt << std::endl;
                std::cout << "Class names file not provided; class<#Id> format will be used." << std::endl;
            }
        }else{
            std::cout << "Class names file not provided; class<#Id> format will be used." << std::endl;
        }
    }

    void BaseObjectDetection::setClassColors(const std::optional<std::string>& classColorsFilePath){
        if (const auto& filePathOpt = classColorsFilePath) {
            std::ifstream file(*filePathOpt);
            if (file) {
                std::string line;
                while (std::getline(file, line)) {
                    std::istringstream stream(line);
                    std::array<int, 3> color;
                    char comma;

                    stream >> color[0] >> comma >> color[1] >> comma >> color[2];
                    m_ClassColors.push_back(std::move(color));  // Use std::move for efficiency
                }
            } else {
                std::cerr << "Unable to open color file: " << *filePathOpt << std::endl;
                std::cout << "Default colors will be used." << std::endl;
            }
        } else {
            std::cout << "Color file not provided; default colors will be used." << std::endl;
        }
    }
} 
