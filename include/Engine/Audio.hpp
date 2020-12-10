#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <string>
#include <vector>

namespace sgf
{
    class SoundEffect
    {
    public:
        void Load(const std::string& path);
        void Play();
        void Unload();
    private:
        Mix_Chunk* m_soundEffect;
        std::string m_path;
    };

    class Music
    {
    public:
        void Load(const std::string& path);
        void Loop(int loop = -1);
        void Play();
        void Pause();
        void Resume();
        void Stop();
        [[nodiscard]] bool IsPaused();
        [[nodiscard]] bool IsPlaying();
    private:
        Mix_Music* m_music;
        std::string m_path;
        int m_loop;
    };

    class Playlist
    {
    public:
        void Load(const std::string& path);
        void Shuffle();
        void Loop(int loop = -1);
        void Play();
        void Pause();
        void Resume();
        void Stop();

        [[nodiscard]] bool IsPaused();
        [[nodiscard]] bool IsPlaying();

        void Update();
    private:
        std::string m_path;
        std::vector<std::string> m_tracks;
        Mix_Music* m_music;
        std::size_t m_it;
        int m_loop;
    };
}