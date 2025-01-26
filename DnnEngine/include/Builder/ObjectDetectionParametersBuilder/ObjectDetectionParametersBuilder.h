#pragma once
#include "Builder/ParametersBuilderContainer.h"
#include "Builder/DnnParametersBuilder/DnnParametersBuilderFactory.h"
#include "BoundingBoxObjectDetectionParametersBuilder/BoundingBoxObjectDetectionParametersBuilder.h"
namespace DnnEngine
{
    template <typename Base>
    class ObjectDetectionParametersBuilder : public Base
    {
        ObjectDetectionParameters& m_Parameters;
    public:
        explicit ObjectDetectionParametersBuilder(Base& base,ObjectDetectionParameters& parameters):Base{base},m_Parameters{parameters}{}

        template<DnnMethod method>
        auto Dnn(){
            return DnnParametersBuilderFactory<ObjectDetectionParametersBuilder<Base>>::template Create<method>(*this, m_Parameters.dnnParameters);
        }
        
        auto Dnn(){
            return DnnParametersBuilderFactory<ObjectDetectionParametersBuilder<Base>>::Get(*this, m_Parameters.dnnParameters);
        }

        template <BoundingBoxDetectionModelType type>
        auto Model(){
            if (std::holds_alternative<BoundingBoxObjectDetectionParameters>(m_Parameters.detectionParameters)){
                auto builder = BoundingBoxObjectDetectionParametersBuilder<ObjectDetectionParametersBuilder<Base>>(*this,std::get<BoundingBoxObjectDetectionParameters>(m_Parameters.detectionParameters));
                return builder.template Model<type>();
            }else{
                throw std::runtime_error("Unsupported detectionParameters method type. You probably did not set Model method type yet.");
            }
        }

        auto Model(){
            if (std::holds_alternative<BoundingBoxObjectDetectionParameters>(m_Parameters.detectionParameters)){
                auto builder = BoundingBoxObjectDetectionParametersBuilder<ObjectDetectionParametersBuilder<Base>>(*this,std::get<BoundingBoxObjectDetectionParameters>(m_Parameters.detectionParameters));
                return builder.Model();
            }else{
                throw std::runtime_error("Unsupported detectionParameters method type. You probably did not set Model method type yet.");
            }
        }


        
        ObjectDetectionParametersBuilder& classNamesFilePath(const std::string& classNamesFilePath){
            m_Parameters.classNamesFilePath = classNamesFilePath;
            return *this;
        }

        ObjectDetectionParametersBuilder& classColorsFilePath(const std::string& classColorsFilePath){
            m_Parameters.classColorsFilePath = classColorsFilePath;
            return *this;
        }

    };
}