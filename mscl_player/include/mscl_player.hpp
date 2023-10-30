/**
 * @file mscl_player/mscl_player.hpp
 */

#pragma once

#include <mscl.h>

// ================================================================================================================================

namespace mscl
{
    class Player
    {
    public:
        static Player* xaudio2();

    public:
        virtual ~Player() = default;
        
        virtual void submit(size_t num_samples, const float* samples, mscl_fp sps) = 0;
        
        virtual void play() = 0;
        virtual void pause() = 0;
        virtual void stop() = 0;

        virtual bool playing() = 0;
        virtual size_t pos() = 0;
    };
}

// ================================================================================================================================
