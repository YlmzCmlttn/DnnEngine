#pragma once
#include "Core/Event.h"
namespace DnnEngine
{
    struct WindowProps
	{
		std::string title;
		uint32_t width;
		uint32_t height;

		WindowProps(const std::string& title = "Window",
			        uint32_t width = 640,
			        uint32_t height = 480)
			: title(title), width(width), height(height)
		{
		}
	};

    class Window{
    public:
		using EventCallbackFn = std::function<void(Event&)>;
        virtual ~Window() = default;
        virtual void onUpdate()=0;
        virtual void setEventCallback(const EventCallbackFn& callback) = 0;
        virtual void showImage(const cv::Mat& image)const=0;
        static std::unique_ptr<Window> Create(const WindowProps& props = WindowProps());
    };
}