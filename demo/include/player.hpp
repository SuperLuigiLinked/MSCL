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
};

extern Player* player_xaudio2();
extern Player* player_wasapi();
