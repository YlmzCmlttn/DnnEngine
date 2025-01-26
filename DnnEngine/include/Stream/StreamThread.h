#pragma once
#include "Core/Thread.h"
namespace DnnEngine
{
    constexpr std::size_t FRAME_MUTEX = 0;
    constexpr std::size_t FRAME_GRABED_MUTEX = 1;
    constexpr std::size_t FRAME_CV = 0;
    constexpr std::size_t FRAME_GRABED_CV = 1;
    constexpr std::size_t calculateMutexes(bool WaitUntilFrameGrabbed) {
        return WaitUntilFrameGrabbed ? 2 : 1;
    }

    constexpr std::size_t calculateConditionVariables(bool WaitNewFrame, bool WaitUntilFrameGrabbed) {
        std::size_t number =0;
        if(WaitNewFrame){
            number++;
        }
        if(WaitUntilFrameGrabbed){
            number++;
        }
        return number;
    }

    template <class StreamType,bool WaitNewFrame = true, bool WaitUntilFrameGrabbed = false> 
    class StreamThread : public StreamType, public Thread<StreamThread<StreamType, WaitNewFrame, WaitUntilFrameGrabbed>,
                    calculateMutexes(WaitUntilFrameGrabbed),
                    calculateConditionVariables(WaitNewFrame, WaitUntilFrameGrabbed)> 
    {
        
    private:
        cv::Mat m_Frame;
        inline void onStart()override{
            StreamType::getFrame(m_Frame);
            setFrame();
        }
        inline void onRun()override{
            std::this_thread::sleep_for (std::chrono::microseconds(1));
            setFrame();
            if constexpr (WaitUntilFrameGrabbed){
                this->template getWhenUpdated<FRAME_GRABED_MUTEX, FRAME_GRABED_CV>([]([[maybe_unused]]const StreamThread& self) {});
            }
        }
        
        template <bool T = WaitNewFrame>
        inline typename std::enable_if<!T, void>::type
        setFrame(){
            this->template lock<FRAME_MUTEX>([](StreamThread& self) {
                cv::Mat frame;
                self.StreamType::getFrame(frame);
                self.m_Frame = frame.clone();
            });
        }
        template <bool T = WaitNewFrame>
        inline typename std::enable_if<T, void>::type
        setFrame() {
            this->template set<FRAME_MUTEX, FRAME_CV>([](StreamThread& self) {
                cv::Mat frame;
                self.StreamType::getFrame(frame);
                self.m_Frame = frame.clone();
            });
        }
    public:
        template<class... Args>
        StreamThread(Args&&... args):StreamType{std::forward<Args>(args)...}{
            this->start();
        }

        inline virtual void operator>>(cv::Mat& frame)override{getFrame(frame);}

        inline virtual bool getFrame(cv::Mat& frame)override{
            frame = getFrame();
            if constexpr (WaitUntilFrameGrabbed){
                this->template set<FRAME_GRABED_MUTEX, FRAME_GRABED_CV>([]([[maybe_unused]] StreamThread& self) {});
            }
            return !frame.empty();
        }

        template <bool T = WaitNewFrame>
        inline typename std::enable_if<T, cv::Mat>::type
        getFrame() {
            return this->template getWhenUpdated<FRAME_MUTEX, FRAME_CV>([](const StreamThread& self) {
                return self.m_Frame;
            });
        }

        template <bool T = WaitNewFrame>
        inline typename std::enable_if<!T, cv::Mat>::type
        getFrame() {
            return this->template lock<FRAME_MUTEX>([](const StreamThread& self) {
                return self.m_Frame;
            });
        }
        virtual ~StreamThread()=default;
    };    
} 


