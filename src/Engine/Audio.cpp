#include "../../include/engine/Audio.hpp"
#include "../../include/engine/Error.hpp"
#include <filesystem>
#include <iostream>
#include <algorithm>
#include "../../include/math/Random.hpp"

namespace sgf
{

    namespace 
    {
        void StopMusic()
        {
            Mix_HaltMusic();
        }    

        void PauseMusic()
        {
            Mix_PauseMusic();
        }

        void ResumeMusic()
        {
            Mix_ResumeMusic();
        }

        bool IsPausedMusic()
        {
            return Mix_PausedMusic() == 1 ? true : false;
        }

        bool IsPlayingMusic()
        {
            return Mix_PlayingMusic() == 1 ? true : false;
        }
    }

    void SoundEffect::Load(const std::string& path)
    {
        if(m_path.length() > 1)
        {
            Mix_FreeChunk(m_soundEffect);
        }

        m_path = path;
        m_soundEffect = nullptr;
        m_soundEffect = Mix_LoadWAV(path.c_str());

        if(!m_soundEffect)
        {
            error::GetSDLError<error::Type::MIXER>("Cannot load sound effect");
        }
    }

    void SoundEffect::Play()
    {
        Mix_PlayChannel(-1, m_soundEffect, 0);
    }

    void Music::Load(const std::string& path)
    {
        if(m_path.length() > 1)
        {
            Mix_FreeMusic(m_music);
        }

        m_path = path;
        m_music = nullptr;
        m_music = Mix_LoadMUS(path.c_str());

        if(!m_music)
        {
            error::GetSDLError<error::Type::MIXER>("Cannot load music");
        }

        m_loop = 1;
    }

    bool Music::IsPlaying()
    {
        return IsPlayingMusic();
    }

    bool Music::IsPaused()
    {
       return IsPausedMusic();
    }

    void Music::Loop(int loop)
    {
        m_loop = loop;
    }

    void Music::Play()
    {
        Mix_PlayMusic(m_music, m_loop);
    }

    void Music::Pause()
    {
        PauseMusic();
    }

    void Music::Resume()
    {
        ResumeMusic();
    }

    void Music::Stop()
    {
        StopMusic();
    }

    void Playlist::Load(const std::string& path)
    {
        std::string str;
        std::size_t found; 
        for(auto&& entry : std::filesystem::directory_iterator(path))
        {
            str = entry.path().string();

            found = str.find_first_of("\\");
            while (found != std::string::npos)
            {
                str.at(found)='/';
                found = std::string::npos;
            }

            m_tracks.push_back(str);
        }

        m_it = 0;
        m_loop = 1;
    }

    void Playlist::Shuffle()
    {
        std::random_shuffle(m_tracks.begin(), m_tracks.end());
    }

    void Playlist::Loop(int loop)
    {
        m_loop = loop;
    }

    void Playlist::Play()
    {
        if(m_it > 0)
        {
            Mix_FreeMusic(m_music);
        }

        if(m_it != m_tracks.size())
        {
            m_music = nullptr;
            m_music = Mix_LoadMUS(m_tracks.at(m_it).c_str());
            Mix_PlayMusic(m_music, -1);
            m_it++;
        }
    }

    void Playlist::Pause()
    {
        PauseMusic();
    }

    void Playlist::Resume()
    {
        ResumeMusic();
    }

    bool Playlist::IsPlaying()
    {
        return IsPlayingMusic();
    }

    bool Playlist::IsPaused()
    {
        return IsPausedMusic();
    }

    void Playlist::Update()
    {
        if(!IsPlaying())
        {
            if(m_it > 0)
            {
                Play();
            }
        }
    }

    void Playlist::Stop()
    {
        StopMusic();
        m_it = 0;
    }
}