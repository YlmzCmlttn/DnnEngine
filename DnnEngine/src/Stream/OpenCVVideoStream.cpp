#include "Stream/OpenCVVideoStream.h"
#include "Core/Exception.h"
namespace DnnEngine {
    OpenCVVideoStream::OpenCVVideoStream(const std::string& filename) {
        open(filename);
    }
    bool OpenCVVideoStream::open(const std::string& filename) {
        m_Cap.open(filename);
        if (!m_Cap.isOpened()) {
            throw Exception(std::string("Error: Could not open video file: ")+ filename);
            return false;
        }
        return true;
    }
    OpenCVVideoStream::~OpenCVVideoStream() {
        if (m_Cap.isOpened()) {
            m_Cap.release();
        }
    }
    void OpenCVVideoStream::operator>>(cv::Mat& frame) {
        getFrame(frame);
    }
    bool OpenCVVideoStream::getFrame(cv::Mat& frame) {
        
        if (m_Cap.isOpened()) {
            if(!m_Cap.read(frame)){
                m_Cap.set(cv::CAP_PROP_POS_FRAMES, 0);
                if(!m_Cap.read(frame)){
                    throw Exception("Error: Could not read: ");
                    return false;
                }
            }
            return true;
        } else {
            return false;
        }
    }
    bool OpenCVVideoStream::isOpened()const{
        return m_Cap.isOpened();
    }

} 
