/**
 * @file mscl_player/mscl_player.hpp
 */

#pragma once

#include <mscl.h>

#include <span>
#include <initializer_list>

// ================================================================================================================================

namespace mscl
{
    class Player
    {
    public:
        static Player* xaudio2();
        static Player* wasapi();

    public:
        virtual ~Player() = default;
        
        virtual void submit(size_t num_samples, const float* samples, mscl_time sps) = 0;
        
        virtual void play() = 0;
        virtual void pause() = 0;
        virtual void stop() = 0;

        virtual bool playing() = 0;
        virtual size_t pos() = 0;
    };
}

// ================================================================================================================================

namespace mscl
{
    using Channel = std::span<const mscl_event>;
    using Channels = std::initializer_list<const Channel>;
    struct Song { const char* name; mscl_time tempo; Channels channels; };

    extern int gui(std::span<const Song> song_list, const int width, const int height, const bool fullscreen = false);
}

// ================================================================================================================================
