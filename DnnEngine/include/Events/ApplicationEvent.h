#pragma once
#include "Core/Event.h"
namespace DnnEngine
{
    class WindowCloseEvent : public Event
    {
    public:
        WindowCloseEvent(){}
        EVENT_CLASS_TYPE(WindowClose)
        EVENT_CLASS_CATEGORY(EventCategoryApplication)
    };
}