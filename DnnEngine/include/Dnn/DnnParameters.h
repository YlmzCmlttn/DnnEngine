#pragma once
#include "OpenCVDnnParameters.h"
namespace DnnEngine{

    struct DnnParameters
    {
        std::variant<std::monostate,OpenCVDnnParameters> parameters;
    };

    inline std::ostream& operator<<(std::ostream& os, const DnnParameters& obj) {    

        os <<"DnnParameters::Start"<<std::endl;    
        if (std::holds_alternative<OpenCVDnnParameters>(obj.parameters)) {
            os <<std::get<OpenCVDnnParameters>(obj.parameters)<<std::endl;
        }else{
            os << "Dnn Parameters are Empty" << std::endl;
        }
        os <<"DnnParameters::End"<<std::endl;
        return os;
    }
}