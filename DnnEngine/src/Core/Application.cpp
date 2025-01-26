#include "Core/Application.h"
#include "Window/Window.h"
#include "Core/Assert.h"
namespace DnnEngine
{
#define BIND_EVENT_FN(x) std::bind(&Application::x,this,std::placeholders::_1)
    Application* Application::s_Instance = nullptr; 

    Application::Application(const WindowProps windowProps)
    {
        DNN_ENGINE_ASSERT(!s_Instance,"Application already exist");
        s_Instance = this;
        m_Window = Window::Create(windowProps);        

        m_Window->setEventCallback(BIND_EVENT_FN(onEvent));
        m_Thread = std::thread([this](){
            run();
        });
    }
    Application::~Application(){        
        close();
    }
    void Application::close()
	{
		m_Running = false;
        if(m_Thread.joinable()){
            m_Thread.join();
        }
	}

    void Application::onEvent(Event& e){
        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(onWindowClose));        
    }

    void Application::run(){
        while(m_Running){
            m_Window->onUpdate();
        }
    }

    bool Application::onWindowClose([[maybe_unused]]WindowCloseEvent& e){
        std::cout<<e.toString()<<std::endl;
        m_Running = false;
        return true;
    }

	Application* createApplication(WindowProps windowProps)
	{
		return new Application(windowProps);
	}
}