#pragma once 
#include <chrono>

namespace sgf 
{
    class Timer
    {
    public:
        static void Start();
        static void End();
    private:
        static inline std::chrono::time_point<std::chrono::system_clock> m_start, m_end;
    };

    class FPS
    {
    public: 
        static void Start();
        static void End();
        static void SetFPSLimit(int limit);
        static void Wait();
    private:
        static int GetFPS();
        static inline std::chrono::time_point<std::chrono::system_clock> m_start, m_end;
        static inline int m_fpsLimit = 2000;
    };

    void Delay(int ms);
}