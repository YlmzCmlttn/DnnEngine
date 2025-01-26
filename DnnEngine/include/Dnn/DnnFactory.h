#pragma once
#include "Dnn/IDnn.h"
#include "Dnn/OpenCVDnn.h"
#include "Core/Assert.h"
namespace DnnEngine
{
    class DnnFactory
    {
    private:
        static std::unique_ptr<IDnn> createOpenCVDnn(const OpenCVDnnParameters& parameters){
            return std::make_unique<OpenCVDnn>(parameters);
        }
    public:
        static std::unique_ptr<IDnn> create(const DnnParameters& parameters){
            if (std::holds_alternative<OpenCVDnnParameters>(parameters.parameters)) {
                return createOpenCVDnn(std::get<OpenCVDnnParameters>(parameters.parameters));
            }
            DNN_ENGINE_ASSERT(false,"Currently, only OpenCV dnn types avaiable!");
        }
    };
} 
