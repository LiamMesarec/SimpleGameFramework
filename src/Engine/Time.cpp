#include "../../include/engine/Time.hpp"

namespace sgf
{
    void Timer::Start()
    {
        m_start = std::chrono::high_resolution_clock::now();
    }

    void Timer::End()
    {
        m_end = std::chrono::high_resolution_clock::now();
    }

    void FPS::Start()
    {
        m_start = std::chrono::high_resolution_clock::now();
    }

    void FPS::End()
    {
        m_end = std::chrono::high_resolution_clock::now();
    }

    void FPS::SetFPSLimit(int limit)
    {
        m_fpsLimit = limit;
    }

    void FPS::Wait()
    {
        while(GetFPS() > m_fpsLimit || GetFPS() < 1)
        {
                
        }
    }

    int FPS::GetFPS()
    {
        m_end = std::chrono::high_resolution_clock::now();
        return (1000.0f / static_cast<float>(std::chrono::duration_cast<std::chrono::milliseconds>((m_end - m_start)).count()));
    }
}