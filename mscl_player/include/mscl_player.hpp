/**
 * @file mscl_player/mscl_player.hpp
 *
 * @brief A cross-platform audio player. 
 */

#pragma once

#include <mscl.h>

// ================================================================================================================================

namespace mscl
{
    /**
     * @brief Interface to MSCL Audio Players.
     */
    class Player
    {
    public:

        /**
         * @brief Constructs a Player using the XAudio2 Backend.
         * @return A Player-derived class, allocated by `new`.
         * @note Platforms: [Windows]
         */
        static Player* xaudio2();

    public:

        /**
         * @brief Defaulted virtual Destructor.
         * @note If a Player is destroyed, it implicitly stops audio playback and releases all buffers passed to it.
         */
        virtual ~Player() = default;
        
        /**
         * @brief Appends a sample buffer to the player's queue.
         * @param num_samples Number of samples in the buffer.
         * @param samples Pointer to sample buffer.
         * @param sps Samples-per-Second to play at.
         * @warning While `playing() == true`, the contents of the buffer must remain unmodified. 
         */
        virtual void submit(size_t num_samples, const float* samples, mscl_fp sps) = 0;
        
        /**
         * @brief Starts/Unpauses audio playback.
         */
        virtual void play() = 0;

        /**
         * @brief Temporarily stops audio playback.
         */
        virtual void pause() = 0;

        /**
         * @brief Stops audio playback and releases all pending buffers.
         */
        virtual void stop() = 0;

        /**
         * @brief Queries the playback status.
         * @return `true` if buffers are queued/playing/paused, `false` if stopped/empty.
         */
        virtual bool playing() = 0;

        /**
         * @brief Queries the playback position.
         * @return The index into the sample buffer of the sample currently being played.
         */
        virtual size_t pos() = 0;
    };
}

// ================================================================================================================================
