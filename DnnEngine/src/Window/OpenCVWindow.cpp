#include "Window/OpenCVWindow.h"
#include "Events/ApplicationEvent.h"
namespace DnnEngine
{
    OpenCVWindow::OpenCVWindow(const WindowProps& props):
        m_WindowName{props.title}
    {
        init(props);
    }
    void OpenCVWindow::init(const WindowProps& props)const{
        m_IsClosed = false;
        cv::namedWindow(m_WindowName, cv::WINDOW_NORMAL);
        cv::resizeWindow(props.title, props.width, props.height);        
    }

    void OpenCVWindow::close()const{
        cv::destroyWindow(m_WindowName);
    }

    void OpenCVWindow::closeEvent()const{
        m_IsClosed = true;
        WindowCloseEvent event;                
        if (m_EventCallback) {
            m_EventCallback(event);
        }
    }

    void OpenCVWindow::onUpdate(){        
        {
            std::unique_lock<std::mutex> lck(m_Mutex);
            cv::waitKey(1);
            try{
                if(cv::getWindowProperty(m_WindowName, 0) < 0) {
                    closeEvent();
                }
            }catch(...){
                closeEvent();
                
            }
        }
        std::this_thread::sleep_for (std::chrono::microseconds(1));
    }
    void OpenCVWindow::showImage(const cv::Mat& image)const{
        std::unique_lock<std::mutex> lck(m_Mutex);
        if(!m_IsClosed){
            cv::imshow(m_WindowName,image);
        }
    }
}