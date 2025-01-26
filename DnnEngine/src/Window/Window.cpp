
#include "Window/OpenCVWindow.h"
namespace DnnEngine
{
    std::unique_ptr<Window> Window::Create(const WindowProps& props)
	{	
		return std::make_unique<OpenCVWindow>(props);
	}
}
	