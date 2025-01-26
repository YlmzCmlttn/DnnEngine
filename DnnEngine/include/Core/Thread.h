#pragma once
namespace DnnEngine
{
    template<typename Derived, std::size_t Mutex = 0, std::size_t ConditionalVariable = 0>
    class Thread
    {
    private:
        std::atomic<bool> m_Running;
        std::atomic<bool> m_Release;
        std::atomic<std::chrono::milliseconds> m_LoopInterval;
        std::thread m_Thread;
        mutable std::array<std::mutex, Mutex> m_Mutexs;
        mutable std::array<std::condition_variable, ConditionalVariable> m_ConditionalVariables;
        mutable std::array<bool, ConditionalVariable> m_Updated;

        virtual void onStart(){}
        virtual void beforeRun(){}
        virtual void onRun(){}
        virtual void afterRun(){}
        virtual void onStop(){}

        virtual void run(){
            beforeRun();
            while (m_Running){
                onRun();
                waitLoopInterval();
            }
            afterRun();
        }
    protected:
        Thread():
            m_Running{false},
            m_Release{false},
            m_LoopInterval{std::chrono::milliseconds(0)}
        {
            for(auto& up:m_Updated){
                up = false;
            }
        }

        virtual ~Thread(){
            stop();
        }
        template<std::size_t mutex,typename F>
        auto lock(F f)const{
            static_assert(mutex < Mutex, "Mutex index out of range");
            std::unique_lock lock(m_Mutexs[mutex]);
            return f(static_cast<const Derived&>(*this));
        }

        template<std::size_t mutex,typename F>
        auto lock(F f){
            static_assert(mutex < Mutex, "Mutex index out of range");
            std::unique_lock lock(m_Mutexs[mutex]);
            return f(static_cast<Derived&>(*this));
        }

        template<std::size_t mutex, std::size_t cv,typename Predicate, typename F>
        auto lockWhen(Predicate p, F f){
            static_assert(mutex < Mutex, "Mutex index out of range");
            static_assert(cv < ConditionalVariable, "Condition variable index out of range");
            std::unique_lock lock(m_Mutexs[mutex]);
            m_ConditionalVariables[cv].wait(lock, [&]{ return ((p(static_cast<Derived&>(*this))) || m_Release); });
            return f(static_cast<Derived&>(*this));
        }

        template<std::size_t mutex, std::size_t cv,typename Predicate, typename F>
        auto lockWhen(Predicate p, F f)const{
            static_assert(mutex < Mutex, "Mutex index out of range");
            static_assert(cv < ConditionalVariable, "Condition variable index out of range");
            std::unique_lock lock(m_Mutexs[mutex]);
            m_ConditionalVariables[cv].wait(lock, [&]{ return ((p(static_cast<const Derived&>(*this))) || m_Release); });
            return f(static_cast<const Derived&>(*this));
        }

        template<std::size_t mutex, std::size_t cv, typename F>
        auto set(F f)const{
            if constexpr (std::is_void_v<decltype(f(static_cast<const Derived&>(*this)))>){
                lock<mutex>(f);
            } else {
                const auto ret = lock<mutex>(f);
                m_Updated[cv] = true;
                notifyAll<cv>();
                return ret;
            }
            m_Updated[cv] = true;
            notifyAll<cv>();
        }
        template<std::size_t mutex, std::size_t cv, typename F>
        auto set(F f){
            if constexpr (std::is_void_v<decltype(f(static_cast<Derived&>(*this)))>){
                lock<mutex>(f);
            } else {
                const auto ret = lock<mutex>(f);
                m_Updated[cv] = true;
                notifyAll<cv>();
                return ret;
            }
            m_Updated[cv] = true;
            notifyAll<cv>();
        }
        template<std::size_t mutex, std::size_t cv, typename F>
        auto getWhenUpdated(F f){
            return lockWhen<mutex,cv>(
                [this](Derived&){return m_Updated[cv];},
                [this,f](Derived& derived){
                    m_Updated[cv] = false;
                    return f(derived);
                }
            );
        }
        template<std::size_t mutex, std::size_t cv, typename F>
        auto getWhenUpdated(F f)const{
            return lockWhen<mutex,cv>(
                [this](const Derived&){return m_Updated[cv];},
                [this,f](const Derived& derived){
                    m_Updated[cv] = false;
                    return f(derived);
                }
            );
        }

        template<std::size_t cv>
        void notify(){
            static_assert(cv < ConditionalVariable, "Condition variable index out of range");
            m_ConditionalVariables[cv].notify_one();
        }

        template<std::size_t cv>
        void notifyAll(){
            static_assert(cv < ConditionalVariable, "Condition variable index out of range");
            m_ConditionalVariables[cv].notify_all();
        }

        void waitLoopInterval() {
            std::this_thread::sleep_for(m_LoopInterval.load());
        }
    public:
        void start(){
            if (m_Running.load()) throw std::runtime_error("The thread is already running.");
            onStart();
            m_Running = true;
            m_Thread = std::thread(&Thread::run, this);
        }

        void stop(){
            if (m_Running.load()){
                onStop();
                m_Release = true;
                m_Running = false;
                for(auto& cv: m_ConditionalVariables){
                    cv.notify_all();
                }
                if (m_Thread.joinable()){
                    m_Thread.join();
                }
            }
        }

        bool isRunning()const{
            return m_Running.load();
        }

        void setLoopInterval(const std::chrono::milliseconds& interval) {
            m_LoopInterval = interval;
        }
    };
}
