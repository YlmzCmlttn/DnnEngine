#pragma once
#include "Detection/ObjectDetectionContainers.h"
namespace DnnEngine
{    
    enum class DnnMethod{
        OpenCV
        //TensorRT We can also configure TensorRt easily.
    };   

    enum class ObjectDetectionMethod{
        BoundingBoxes =0
    };
    enum class BoundingBoxDetectionModelType{
        Yolo = 0
    };
} 
