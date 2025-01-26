#pragma once
#include "Window/Window.h"
#include "Core/Event.h"
#include "Events/ApplicationEvent.h"
namespace DnnEngine
{
    class Application
    {
    public:
        void run();
        void onEvent(Event& e);
        void close();
        inline static Application& Get(){return *s_Instance;}
        Application(const WindowProps windowProps);
        inline void showImage(const cv::Mat& image)const{if(m_Window) m_Window->showImage(image);};
        inline bool isRunning()const{return m_Running;}
        inline Window& GetWindow(){return *m_Window;}
        virtual ~Application();
    private:
        std::unique_ptr<Window> m_Window;
        std::atomic<bool> m_Running = true;
        static Application* s_Instance;
        std::thread m_Thread;
        bool onWindowClose(WindowCloseEvent& e);
    };
    Application* createApplication(WindowProps windowProps = WindowProps{});
} 
