#include "../../include/engine/Audio.hpp"
#include "../../include/engine/Error.hpp"
#include <filesystem>
#include <iostream>
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

        void SetChannelVolume(std::size_t channelID, int volume)
        {
            if(Audio::IsEnabled())
            {
                if(volume > 128) 
                {
                    volume = 128;
                }

                Mix_Volume(channelID, volume);
            }
        }
    }

    void Audio::SetVolume(int volume)
    {
        if(Audio::IsEnabled())
        {
            SetChannelVolume(-1, volume);
        }
    }

    void Audio::Enable(bool enabled)
    {
        m_enabled = enabled;
    }

    void SoundEffect::Load(const std::string& path)
    {
        if(Audio::IsEnabled())
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
    }

    void SoundEffect::Play()
    {
        if(Audio::IsEnabled())
        {
            m_channelID = Mix_PlayChannel(-1, m_soundEffect, 0);
        }
    }

    void Music::Load(const std::string& path)
    {
        if(Audio::IsEnabled())
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

            m_loop = 0;
        }
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
        m_channelID = Mix_PlayMusic(m_music, m_loop);
    }

    void Music::Pause()
    {
        if(Audio::IsEnabled())
        {
            PauseMusic();
        }
    }

    void Music::Resume()
    {
        if(Audio::IsEnabled())
        {
            ResumeMusic();
        }
    }

    void Music::Stop()
    {
        if(Audio::IsEnabled())
        {
            StopMusic();
        }
    }

    void Playlist::Load(const std::string& path)
    {
        if(Audio::IsEnabled())
        {
            std::string str;

            m_tracks.clear();

            for(std::string::size_type found; auto&& entry : std::filesystem::directory_iterator(path))
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
            m_loop = 0;
        }
    }

    void Playlist::Shuffle()
    {
        if(Audio::IsEnabled())
        {
            std::random_shuffle(m_tracks.begin(), m_tracks.end());
        }
    }

    void Playlist::Loop(int loop)
    {
        m_loop = loop;
    }

    void Playlist::Play()
    {
        if(Audio::IsEnabled())
        {
            if(m_it > 0 && m_it != m_tracks.size())
            {
                Mix_FreeMusic(m_music);
            }

            if(m_it != m_tracks.size())
            {
                m_music = nullptr;
                m_music = Mix_LoadMUS(m_tracks.at(m_it).c_str());
                m_channelID = Mix_PlayMusic(m_music, m_loop);
                m_it++;
            }
        }
    }

    void Playlist::Pause()
    {
        if(Audio::IsEnabled())
        {
            PauseMusic();
        }
    }

    void Playlist::Resume()
    {
        if(Audio::IsEnabled())
        {
            ResumeMusic();
        }
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
        if(Audio::IsEnabled())
        {
            if(!IsPlaying())
            {
                if(m_it > 0 && m_it < m_tracks.size())
                {
                    Play();
                }
            }
        }
    }

    void Playlist::Stop()
    {
        if(Audio::IsEnabled())
        {
        StopMusic();
            m_it = 0;
        }
    }

    void Playlist::SetVolume(int volume)
    {
        if(Audio::IsEnabled())
        {
            SetChannelVolume(m_channelID, volume);
        }
    }

    void Music::SetVolume(int volume)
    {
        if(Audio::IsEnabled())
        {
            SetChannelVolume(m_channelID, volume);
        }
    }

    void SoundEffect::SetVolume(int volume)
    {
        if(Audio::IsEnabled())
        {
            SetChannelVolume(m_channelID, volume);
        }
    }
}