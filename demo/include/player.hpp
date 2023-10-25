/**
 * @file demo/player.hpp
 */

#pragma once

#include <mscl.h>

class Player
{
public:
    virtual ~Player() = default;
    
    virtual void play(size_t num_samples, const float* samples, mscl_time sps) = 0;
    virtual void stop() = 0;
    
    virtual void pause() = 0;
    virtual void unpause() = 0;

    virtual bool playing() = 0;
    virtual size_t pos() = 0;
};

extern Player* player_xaudio2();
extern Player* player_wasapi();
