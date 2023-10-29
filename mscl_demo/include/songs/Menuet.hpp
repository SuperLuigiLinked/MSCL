/**
 * @file mscl_demo/songs/Menuet.hpp
 */

#pragma once

#include <mscl.h>
#include <mscl_player.hpp>
#include "instruments.hpp"

namespace songs::Menuet
{
// ================================================================================================================================

inline static constexpr mscl_event c0[] = {
	{mscl_event_loop_begin, {.loop_begin = MSCL_LOOP_INFINITE }},

	{mscl_event_volume, {.volume = mscl_fp(0.15) }},
	{mscl_event_sustain, {.sustain = env_fade_fast }},
	{mscl_event_release, {.release = rel_fade }},
	{mscl_event_vibrato, {.vibrato = vib_some }},
	{mscl_event_waveform, {.waveform = wav_pulse_25 }},

	{mscl_event_length, {.length = mscl_fp(1.0 / 2.0) }},

	// Section 1A

	{mscl_event_loop_begin, {.loop_begin = 1 }},
	{mscl_event_tone, {.tone = MSCL_TONE(4, MSCL_A) }},
	{mscl_event_tone, {.tone = MSCL_TONE(5, MSCL_Cs) }},
	{mscl_event_tone, {.tone = MSCL_TONE(5, MSCL_Fs) }},
	{mscl_event_tone, {.tone = MSCL_TONE(5, MSCL_Cs) }},
	{mscl_event_tone, {.tone = MSCL_TONE(4, MSCL_Gs) }},
	{mscl_event_tone, {.tone = MSCL_TONE(5, MSCL_Cs) }},
	{mscl_event_tone, {.tone = MSCL_TONE(4, MSCL_A) }},
	{mscl_event_tone, {.tone = MSCL_TONE(5, MSCL_Cs) }},
	{mscl_event_tone, {.tone = MSCL_TONE(4, MSCL_Fs) }},
	{mscl_event_tone, {.tone = MSCL_TONE(5, MSCL_Cs) }},
	{mscl_event_tone, {.tone = MSCL_TONE(4, MSCL_F) }},
	{mscl_event_tone, {.tone = MSCL_TONE(5, MSCL_Cs) }},
	{mscl_event_loop_end, {}},

	{mscl_event_tone, {.tone = MSCL_TONE(4, MSCL_A) }},
	{mscl_event_tone, {.tone = MSCL_TONE(5, MSCL_Cs) }},
	{mscl_event_tone, {.tone = MSCL_TONE(4, MSCL_A) }},
	{mscl_event_tone, {.tone = MSCL_TONE(4, MSCL_Fs) }},
	{mscl_event_tone, {.tone = MSCL_TONE(5, MSCL_D) }},
	{mscl_event_tone, {.tone = MSCL_TONE(4, MSCL_B) }},
	{mscl_event_tone, {.tone = MSCL_TONE(4, MSCL_Gs) }},
	{mscl_event_tone, {.tone = MSCL_TONE(4, MSCL_B) }},
	{mscl_event_tone, {.tone = MSCL_TONE(4, MSCL_Gs) }},
	{mscl_event_tone, {.tone = MSCL_TONE(4, MSCL_E) }},
	{mscl_event_tone, {.tone = MSCL_TONE(5, MSCL_Cs) }},
	{mscl_event_tone, {.tone = MSCL_TONE(4, MSCL_A) }},

	{mscl_event_tone, {.tone = MSCL_TONE(4, MSCL_Fs) }},
	{mscl_event_tone, {.tone = MSCL_TONE(5, MSCL_Cs) }},
	{mscl_event_tone, {.tone = MSCL_TONE(4, MSCL_B) }},
	{mscl_event_tone, {.tone = MSCL_TONE(4, MSCL_A) }},
	{mscl_event_tone, {.tone = MSCL_TONE(4, MSCL_Gs) }},
	{mscl_event_tone, {.tone = MSCL_TONE(4, MSCL_Fs) }},
	{mscl_event_tone, {.tone = MSCL_TONE(4, MSCL_F) }},
	{mscl_event_tone, {.tone = MSCL_TONE(4, MSCL_Cs) }},
	{mscl_event_tone, {.tone = MSCL_TONE(4, MSCL_F) }},
	{mscl_event_tone, {.tone = MSCL_TONE(4, MSCL_Gs) }},
	{mscl_event_tone, {.tone = MSCL_TONE(5, MSCL_Cs) }},
	{mscl_event_tone, {.tone = MSCL_TONE(4, MSCL_B) }},

	// Section 1B

	{mscl_event_loop_begin, {.loop_begin = 1 }},
	{mscl_event_tone, {.tone = MSCL_TONE(4, MSCL_A) }},
	{mscl_event_tone, {.tone = MSCL_TONE(5, MSCL_Cs) }},
	{mscl_event_tone, {.tone = MSCL_TONE(5, MSCL_Fs) }},
	{mscl_event_tone, {.tone = MSCL_TONE(5, MSCL_Cs) }},
	{mscl_event_tone, {.tone = MSCL_TONE(4, MSCL_Gs) }},
	{mscl_event_tone, {.tone = MSCL_TONE(5, MSCL_Cs) }},
	{mscl_event_tone, {.tone = MSCL_TONE(4, MSCL_A) }},
	{mscl_event_tone, {.tone = MSCL_TONE(5, MSCL_Cs) }},
	{mscl_event_tone, {.tone = MSCL_TONE(4, MSCL_Fs) }},
	{mscl_event_tone, {.tone = MSCL_TONE(5, MSCL_Cs) }},
	{mscl_event_tone, {.tone = MSCL_TONE(4, MSCL_F) }},
	{mscl_event_tone, {.tone = MSCL_TONE(5, MSCL_Cs) }},
	{mscl_event_loop_end, {}},

	{mscl_event_tone, {.tone = MSCL_TONE(4, MSCL_A) }},
	{mscl_event_tone, {.tone = MSCL_TONE(5, MSCL_Cs) }},
	{mscl_event_tone, {.tone = MSCL_TONE(4, MSCL_A) }},
	{mscl_event_tone, {.tone = MSCL_TONE(4, MSCL_Fs) }},
	{mscl_event_tone, {.tone = MSCL_TONE(5, MSCL_D) }},
	{mscl_event_tone, {.tone = MSCL_TONE(4, MSCL_B) }},
	{mscl_event_tone, {.tone = MSCL_TONE(4, MSCL_Gs) }},
	{mscl_event_tone, {.tone = MSCL_TONE(4, MSCL_B) }},
	{mscl_event_tone, {.tone = MSCL_TONE(4, MSCL_Gs) }},
	{mscl_event_tone, {.tone = MSCL_TONE(4, MSCL_E) }},
	{mscl_event_tone, {.tone = MSCL_TONE(5, MSCL_E) }},
	{mscl_event_tone, {.tone = MSCL_TONE(4, MSCL_B) }},

	{mscl_event_tone, {.tone = MSCL_TONE(5, MSCL_Cs) }},
	{mscl_event_tone, {.tone = MSCL_TONE(5, MSCL_E) }},
	{mscl_event_tone, {.tone = MSCL_TONE(5, MSCL_Cs) }},
	{mscl_event_tone, {.tone = MSCL_TONE(4, MSCL_A) }},
	{mscl_event_tone, {.tone = MSCL_TONE(4, MSCL_E) }},
	{mscl_event_tone, {.tone = MSCL_TONE(4, MSCL_Gs) }},
	{mscl_event_length, {.length = mscl_fp(1.0 / 1.0) }},
	{mscl_event_tone, {.tone = MSCL_TONE(4, MSCL_A) }},
	{mscl_event_rest, {}},
	{mscl_event_rest, {}},

	// End
	{mscl_event_loop_end, {}},
};

// --------------------------------------------------------------------------------------------------------------------------------

inline static constexpr mscl_event c1[] = {
	{mscl_event_loop_begin, {.loop_begin = MSCL_LOOP_INFINITE }},

	{mscl_event_volume, {.volume = mscl_fp(0.15) }},
	{mscl_event_sustain, {.sustain = env_fade_fast }},
	{mscl_event_release, {.release = rel_fade }},
	{mscl_event_vibrato, {.vibrato = vib_some }},
	{mscl_event_waveform, {.waveform = wav_pulse_25 }},

	// Section 1A

	{mscl_event_length, {.length = mscl_fp(1.0 / 1.0) }},
	{mscl_event_tone, {.tone = MSCL_TONE(3, MSCL_Fs) }},
	{mscl_event_tone, {.tone = MSCL_TONE(4, MSCL_Fs) }},
	{mscl_event_tone, {.tone = MSCL_TONE(4, MSCL_F) }},
	{mscl_event_tone, {.tone = MSCL_TONE(3, MSCL_Fs) }},
	{mscl_event_tone, {.tone = MSCL_TONE(3, MSCL_A) }},
	{mscl_event_tone, {.tone = MSCL_TONE(4, MSCL_Cs) }},

	{mscl_event_length, {.length = mscl_fp(1.0 / 1.0) }},
	{mscl_event_tone, {.tone = MSCL_TONE(4, MSCL_Fs) }},
	{mscl_event_tone, {.tone = MSCL_TONE(4, MSCL_D) }},
	{mscl_event_tone, {.tone = MSCL_TONE(4, MSCL_Cs) }},
	{mscl_event_tone, {.tone = MSCL_TONE(4, MSCL_Fs) }},
	{mscl_event_tone, {.tone = MSCL_TONE(3, MSCL_A) }},
	{mscl_event_tone, {.tone = MSCL_TONE(4, MSCL_Cs) }},

	{mscl_event_length, {.length = mscl_fp(1.0 / 1.0) }},
	{mscl_event_tone, {.tone = MSCL_TONE(3, MSCL_Fs) }},
	{mscl_event_tone, {.tone = MSCL_TONE(4, MSCL_Fs) }},
	{mscl_event_tone, {.tone = MSCL_TONE(3, MSCL_B) }},
	{mscl_event_tone, {.tone = MSCL_TONE(3, MSCL_E) }},
	{mscl_event_tone, {.tone = MSCL_TONE(4, MSCL_E) }},
	{mscl_event_tone, {.tone = MSCL_TONE(3, MSCL_A) }},

	{mscl_event_length, {.length = mscl_fp(1.0 / 1.0) }},
	{mscl_event_tone, {.tone = MSCL_TONE(3, MSCL_D) }},
	{mscl_event_tone, {.tone = MSCL_TONE(4, MSCL_D) }},
	{mscl_event_tone, {.tone = MSCL_TONE(3, MSCL_B) }},
	{mscl_event_length, {.length = mscl_fp(1.0 / 2.0) }},
	{mscl_event_tone, {.tone = MSCL_TONE(4, MSCL_Cs) }},
	{mscl_event_tone, {.tone = MSCL_TONE(4, MSCL_D) }},
	{mscl_event_tone, {.tone = MSCL_TONE(4, MSCL_Cs) }},
	{mscl_event_tone, {.tone = MSCL_TONE(3, MSCL_B) }},
	{mscl_event_tone, {.tone = MSCL_TONE(3, MSCL_A) }},
	{mscl_event_tone, {.tone = MSCL_TONE(3, MSCL_Gs) }},

	// Section 1B

	{mscl_event_length, {.length = mscl_fp(1.0 / 1.0) }},
	{mscl_event_tone, {.tone = MSCL_TONE(3, MSCL_Fs) }},
	{mscl_event_tone, {.tone = MSCL_TONE(4, MSCL_Fs) }},
	{mscl_event_tone, {.tone = MSCL_TONE(4, MSCL_F) }},
	{mscl_event_tone, {.tone = MSCL_TONE(3, MSCL_Fs) }},
	{mscl_event_tone, {.tone = MSCL_TONE(3, MSCL_A) }},
	{mscl_event_tone, {.tone = MSCL_TONE(4, MSCL_Cs) }},

	{mscl_event_length, {.length = mscl_fp(1.0 / 1.0) }},
	{mscl_event_tone, {.tone = MSCL_TONE(4, MSCL_Fs) }},
	{mscl_event_tone, {.tone = MSCL_TONE(4, MSCL_D) }},
	{mscl_event_tone, {.tone = MSCL_TONE(4, MSCL_Cs) }},
	{mscl_event_tone, {.tone = MSCL_TONE(4, MSCL_Fs) }},
	{mscl_event_tone, {.tone = MSCL_TONE(3, MSCL_A) }},
	{mscl_event_tone, {.tone = MSCL_TONE(4, MSCL_Cs) }},

	{mscl_event_length, {.length = mscl_fp(1.0 / 1.0) }},
	{mscl_event_tone, {.tone = MSCL_TONE(3, MSCL_Fs) }},
	{mscl_event_tone, {.tone = MSCL_TONE(4, MSCL_Fs) }},
	{mscl_event_tone, {.tone = MSCL_TONE(3, MSCL_B) }},
	{mscl_event_tone, {.tone = MSCL_TONE(3, MSCL_E) }},
	{mscl_event_tone, {.tone = MSCL_TONE(4, MSCL_E) }},
	{mscl_event_tone, {.tone = MSCL_TONE(3, MSCL_Gs) }},

	{mscl_event_length, {.length = mscl_fp(1.0 / 1.0) }},
	{mscl_event_tone, {.tone = MSCL_TONE(3, MSCL_A) }},
	{mscl_event_tone, {.tone = MSCL_TONE(4, MSCL_Cs) }},
	{mscl_event_tone, {.tone = MSCL_TONE(4, MSCL_Cs) }},
	{mscl_event_tone, {.tone = MSCL_TONE(3, MSCL_A) }},
	{mscl_event_tone, {.tone = MSCL_TONE(3, MSCL_E) }},
	{mscl_event_tone, {.tone = MSCL_TONE(2, MSCL_A) }},
	
	// End
	{mscl_event_loop_end, {}},
};

// --------------------------------------------------------------------------------------------------------------------------------

inline static constexpr mscl::Song song
{
    "Menuet",
    148.0,
    {c0, c1}
};

// ================================================================================================================================
}
