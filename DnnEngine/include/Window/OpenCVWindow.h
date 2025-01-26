#pragma once
#include "Window.h"
namespace DnnEngine
{
    class OpenCVWindow : public Window{
    public:
        using EventCallbackFn = std::function<void(Event&)>;
        OpenCVWindow(const WindowProps& props);
        virtual void onUpdate()override;
        inline void setEventCallback(const EventCallbackFn& callback)override{m_EventCallback=callback;}
        void showImage(const cv::Mat& frame)const override;
        virtual ~OpenCVWindow() = default;
    private:
        std::string m_WindowName;
        EventCallbackFn m_EventCallback;
        mutable std::atomic<bool> m_IsClosed;
        mutable std::mutex m_Mutex;
        void init(const WindowProps& props)const;
        void close()const;
        void closeEvent()const;
    };
}