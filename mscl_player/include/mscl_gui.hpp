/**
 * @file mscl_player/mscl_gui.hpp
 *
 * @brief Utils for passing Songs to the MSCL GUI.
 */

#pragma once

#include <mscl.h>

#include <span>
#include <initializer_list>

// ================================================================================================================================

namespace mscl
{
    /**
     * @brief A list of MSCL Events.
     */
    using Channel = std::span<const mscl_event>;

    /**
     * @brief A list of Channels.
     */
    using Channels = std::initializer_list<const Channel>;

    /**
     * @brief A collection of MSCL Events and Song Metadata.
     */
    struct Song { const char* name; mscl_fp bpm; Channels channels; };

    /**
     * @brief Runs the MSCL Player in a Window until it is closed by the user.
     * @param song_list The list of Songs playable in the player.
     * @param width The Width of the Window, in pixels.
     * @param height The Height of the Window, in pixels.
     * @param fullscreen Whether or not to launch in Fullscreen Mode.
     * @return `EXIT_SUCCESS` if launched successfully, `EXIT_FAILURE` otherwise.
     */
    extern int gui(std::span<const Song> song_list, int width, int height, bool fullscreen = false);
}

// ================================================================================================================================
