/**
 * @file mscl_player/mscl_gui.hpp
 */

#pragma once

#include <mscl.h>

#include <span>
#include <initializer_list>

// ================================================================================================================================

namespace mscl
{
    using Channel = std::span<const mscl_event>;
    using Channels = std::initializer_list<const Channel>;
    struct Song { const char* name; mscl_fp bpm; Channels channels; };

    extern int gui(std::span<const Song> song_list, const int width, const int height, const bool fullscreen = false);
}

// ================================================================================================================================
