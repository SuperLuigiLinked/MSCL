/**
 * @file mscl_demo/songs/Ghosts.hpp
 */

#pragma once

#include <mscl.h>
#include <mscl_player.hpp>
#include "instruments.hpp"

namespace songs::Ghosts
{
// ================================================================================================================================

inline static constexpr mscl_event c0[] = {
	{mscl_event_loop_begin, {.loop_begin = MSCL_LOOP_INFINITE }},

	{mscl_event_loop_begin, {.loop_begin = 15 }},
	{mscl_event_sustain, {.sustain = env_fade }},
	{mscl_event_release, {.release = rel_fade }},
	{mscl_event_vibrato, {.vibrato = vib_medium }},
	{mscl_event_waveform, {.waveform = wav_fin }},
	{mscl_event_volume, {.volume = mscl_sample(0.25) }},
	{mscl_event_length, {.length = mscl_time(1.0 / 2.0) }},
	{mscl_event_tone, {.tone = MSCL_TONE(2, MSCL_B) }},
	{mscl_event_tone, {.tone = MSCL_TONE(2, MSCL_B) }},
	{mscl_event_length, {.length = mscl_time(1.0 / 4.0) }},
	{mscl_event_tone, {.tone = MSCL_TONE(3, MSCL_D) }},
	{mscl_event_tone, {.tone = MSCL_TONE(3, MSCL_Ds) }},
	{mscl_event_length, {.length = mscl_time(1.0 / 2.0) }},
	{mscl_event_tone, {.tone = MSCL_TONE(3, MSCL_Fs) }},
	{mscl_event_tone, {.tone = MSCL_TONE(3, MSCL_A) }},
	{mscl_event_tone, {.tone = MSCL_TONE(3, MSCL_A) }},
	{mscl_event_tone, {.tone = MSCL_TONE(3, MSCL_E) }},
	{mscl_event_tone, {.tone = MSCL_TONE(3, MSCL_E) }},
	{mscl_event_loop_end, {}},

	{mscl_event_loop_begin, {.loop_begin = 1 }},
	{mscl_event_sustain, {.sustain = env_fade_slow }},
	{mscl_event_release, {.release = rel_fade }},
	{mscl_event_vibrato, {.vibrato = vib_medium }},
	{mscl_event_waveform, {.waveform = wav_fin }},
	{mscl_event_volume, {.volume = mscl_sample(0.15) }},
	{mscl_event_length, {.length = mscl_time(3.0 / 6.0) }},
	{mscl_event_tone, {.tone = MSCL_TONE(3, MSCL_B) }},
	{mscl_event_tone, {.tone = MSCL_TONE(3, MSCL_B) }},
	{mscl_event_tone, {.tone = MSCL_TONE(3, MSCL_B) }},
	{mscl_event_tone, {.tone = MSCL_TONE(3, MSCL_B) }},
	{mscl_event_tone, {.tone = MSCL_TONE(3, MSCL_B) }},
	{mscl_event_tone, {.tone = MSCL_TONE(3, MSCL_B) }},
	{mscl_event_tone, {.tone = MSCL_TONE(3, MSCL_A) }},
	{mscl_event_tone, {.tone = MSCL_TONE(3, MSCL_A) }},
	{mscl_event_tone, {.tone = MSCL_TONE(3, MSCL_A) }},
	{mscl_event_tone, {.tone = MSCL_TONE(3, MSCL_A) }},
	{mscl_event_tone, {.tone = MSCL_TONE(3, MSCL_A) }},
	{mscl_event_tone, {.tone = MSCL_TONE(3, MSCL_A) }},
	{mscl_event_length, {.length = mscl_time(1.0 / 2.0) }},
	{mscl_event_tone, {.tone = MSCL_TONE(3, MSCL_A) }},
	{mscl_event_tone, {.tone = MSCL_TONE(3, MSCL_A) }},
	{mscl_event_length, {.length = mscl_time(1.0 / 4.0) }},
	{mscl_event_tone, {.tone = MSCL_TONE(3, MSCL_A) }},
	{mscl_event_tone, {.tone = MSCL_TONE(3, MSCL_A) }},
	{mscl_event_length, {.length = mscl_time(1.0 / 2.0) }},
	{mscl_event_tone, {.tone = MSCL_TONE(3, MSCL_A) }},
	{mscl_event_length, {.length = mscl_time(3.0 / 6.0) }},
	{mscl_event_tone, {.tone = MSCL_TONE(3, MSCL_Gs) }},
	{mscl_event_tone, {.tone = MSCL_TONE(3, MSCL_Gs) }},
	{mscl_event_tone, {.tone = MSCL_TONE(3, MSCL_Gs) }},
	{mscl_event_tone, {.tone = MSCL_TONE(3, MSCL_Gs) }},
	{mscl_event_tone, {.tone = MSCL_TONE(3, MSCL_Gs) }},
	{mscl_event_tone, {.tone = MSCL_TONE(3, MSCL_Gs) }},
	{mscl_event_tone, {.tone = MSCL_TONE(3, MSCL_E) }},
	{mscl_event_tone, {.tone = MSCL_TONE(3, MSCL_E) }},
	{mscl_event_tone, {.tone = MSCL_TONE(3, MSCL_E) }},
	{mscl_event_tone, {.tone = MSCL_TONE(3, MSCL_E) }},
	{mscl_event_tone, {.tone = MSCL_TONE(3, MSCL_E) }},
	{mscl_event_tone, {.tone = MSCL_TONE(3, MSCL_E) }},
	{mscl_event_length, {.length = mscl_time(1.0 / 2.0) }},
	{mscl_event_tone, {.tone = MSCL_TONE(3, MSCL_E) }},
	{mscl_event_tone, {.tone = MSCL_TONE(3, MSCL_E) }},
	{mscl_event_length, {.length = mscl_time(1.0 / 4.0) }},
	{mscl_event_tone, {.tone = MSCL_TONE(3, MSCL_E) }},
	{mscl_event_tone, {.tone = MSCL_TONE(3, MSCL_E) }},
	{mscl_event_length, {.length = mscl_time(1.0 / 2.0) }},
	{mscl_event_tone, {.tone = MSCL_TONE(3, MSCL_E) }},
	{mscl_event_loop_end, {}},

	{mscl_event_loop_end, {}},
};

// --------------------------------------------------------------------------------------------------------------------------------

inline static constexpr mscl_event c1[] = {
	{mscl_event_sustain, {.sustain = env_fade }},
	{mscl_event_release, {.release = rel_drop }},
	{mscl_event_vibrato, {.vibrato = vib_medium }},

	{mscl_event_loop_begin, {.loop_begin = MSCL_LOOP_INFINITE }},

	{mscl_event_length, {.length = mscl_time(4.0 * 4) }},
	{mscl_event_rest, {}},

	{mscl_event_waveform, {.waveform = wav_sine }},
	{mscl_event_volume, {.volume = mscl_sample(0.25) }},

	{mscl_event_length, {.length = mscl_time(1.0 / 2.0) }},
	{mscl_event_rest, {}},
	{mscl_event_length, {.length = mscl_time(1.0 / 4.0) }},
	{mscl_event_tone, {.tone = MSCL_TONE(4, MSCL_B) }},
	{mscl_event_tone, {.tone = MSCL_TONE(4, MSCL_B) }},
	{mscl_event_length, {.length = mscl_time(1.0 / 2.0) }},
	{mscl_event_tone, {.tone = MSCL_TONE(5, MSCL_Ds) }},
	{mscl_event_tone, {.tone = MSCL_TONE(4, MSCL_B) }},
	{mscl_event_tone, {.tone = MSCL_TONE(5, MSCL_Cs) }},
	{mscl_event_tone, {.tone = MSCL_TONE(4, MSCL_A) }},
	{mscl_event_length, {.length = mscl_time(1.0 / 1.0) }},
	{mscl_event_rest, {}},

	{mscl_event_length, {.length = mscl_time(1.0 / 1.0) }},
	{mscl_event_rest, {}},
	{mscl_event_length, {.length = mscl_time(1.0 / 4.0) }},
	{mscl_event_tone, {.tone = MSCL_TONE(4, MSCL_B) }},
	{mscl_event_tone, {.tone = MSCL_TONE(4, MSCL_B) }},
	{mscl_event_tone, {.tone = MSCL_TONE(4, MSCL_B) }},
	{mscl_event_tone, {.tone = MSCL_TONE(4, MSCL_B) }},
	{mscl_event_length, {.length = mscl_time(1.0 / 2.0) }},
	{mscl_event_tone, {.tone = MSCL_TONE(4, MSCL_A) }},
	{mscl_event_tone, {.tone = MSCL_TONE(4, MSCL_B) }},
	{mscl_event_length, {.length = mscl_time(1.0 / 1.0) }},
	{mscl_event_rest, {}},

	{mscl_event_length, {.length = mscl_time(1.0 / 2.0) }},
	{mscl_event_rest, {}},
	{mscl_event_length, {.length = mscl_time(1.0 / 4.0) }},
	{mscl_event_tone, {.tone = MSCL_TONE(4, MSCL_B) }},
	{mscl_event_tone, {.tone = MSCL_TONE(4, MSCL_B) }},
	{mscl_event_length, {.length = mscl_time(1.0 / 2.0) }},
	{mscl_event_tone, {.tone = MSCL_TONE(5, MSCL_Ds) }},
	{mscl_event_tone, {.tone = MSCL_TONE(4, MSCL_B) }},
	{mscl_event_tone, {.tone = MSCL_TONE(5, MSCL_Cs) }},
	{mscl_event_tone, {.tone = MSCL_TONE(4, MSCL_A) }},
	{mscl_event_length, {.length = mscl_time(1.0 / 1.0) }},
	{mscl_event_rest, {}},

	{mscl_event_length, {.length = mscl_time(1.0 / 1.0) }},
	{mscl_event_rest, {}},
	{mscl_event_length, {.length = mscl_time(1.0 / 4.0) }},
	{mscl_event_tone, {.tone = MSCL_TONE(4, MSCL_B) }},
	{mscl_event_tone, {.tone = MSCL_TONE(4, MSCL_B) }},
	{mscl_event_tone, {.tone = MSCL_TONE(4, MSCL_B) }},
	{mscl_event_tone, {.tone = MSCL_TONE(4, MSCL_B) }},
	{mscl_event_length, {.length = mscl_time(1.0 / 2.0) }},
	{mscl_event_tone, {.tone = MSCL_TONE(4, MSCL_A) }},
	{mscl_event_tone, {.tone = MSCL_TONE(5, MSCL_Cs) }},
	{mscl_event_tone, {.tone = MSCL_TONE(4, MSCL_B) }},
	{mscl_event_waveform, {.waveform = wav_square }},
	{mscl_event_volume, {.volume = mscl_sample(0.15) }},
	{mscl_event_length, {.length = mscl_time(1.0 / 4.0) }},
	{mscl_event_tone, {.tone = MSCL_TONE(4, MSCL_B) }},
	{mscl_event_tone, {.tone = MSCL_TONE(4, MSCL_B) }},

	{mscl_event_length, {.length = mscl_time(1.0 / 2.0) }},
	{mscl_event_tone, {.tone = MSCL_TONE(5, MSCL_D) }},
	{mscl_event_tone, {.tone = MSCL_TONE(4, MSCL_B) }},
	{mscl_event_length, {.length = mscl_time(1.0 / 1.0) }},
	{mscl_event_tone, {.tone = MSCL_TONE(5, MSCL_D) }},
	{mscl_event_rest, {}},
	{mscl_event_length, {.length = mscl_time(1.0 / 4.0) }},
	{mscl_event_rest, {}},
	{mscl_event_rest, {}},
	{mscl_event_tone, {.tone = MSCL_TONE(4, MSCL_B) }},
	{mscl_event_tone, {.tone = MSCL_TONE(4, MSCL_A) }},

	{mscl_event_length, {.length = mscl_time(1.0 / 2.0) }},
	{mscl_event_tone, {.tone = MSCL_TONE(4, MSCL_B) }},
	{mscl_event_tone, {.tone = MSCL_TONE(4, MSCL_B) }},
	{mscl_event_length, {.length = mscl_time(1.0 / 1.0) }},
	{mscl_event_tone, {.tone = MSCL_TONE(4, MSCL_B) }},
	{mscl_event_rest, {}},
	{mscl_event_rest, {}},

	{mscl_event_length, {.length = mscl_time(1.0 / 4.0) }},
	{mscl_event_tone, {.tone = MSCL_TONE(5, MSCL_D) }},
	{mscl_event_tone, {.tone = MSCL_TONE(4, MSCL_B) }},
	{mscl_event_tone, {.tone = MSCL_TONE(4, MSCL_B) }},
	{mscl_event_tone, {.tone = MSCL_TONE(4, MSCL_B) }},
	{mscl_event_length, {.length = mscl_time(1.0 / 1.0) }},
	{mscl_event_tone, {.tone = MSCL_TONE(4, MSCL_B) }},
	{mscl_event_rest, {}},
	{mscl_event_tone, {.tone = MSCL_TONE(5, MSCL_Fs) }},

	{mscl_event_length, {.length = mscl_time(1.0 / 2.0) }},
	{mscl_event_tone, {.tone = MSCL_TONE(5, MSCL_Fs) }},
	{mscl_event_tone, {.tone = MSCL_TONE(5, MSCL_Fs) }},
	{mscl_event_length, {.length = mscl_time(1.0 / 1.0) }},
	{mscl_event_rest, {}},
	{mscl_event_rest, {}},
	{mscl_event_length, {.length = mscl_time(1.0 / 4.0) }},
	{mscl_event_rest, {}},
	{mscl_event_rest, {}},
	{mscl_event_tone, {.tone = MSCL_TONE(4, MSCL_B) }},
	{mscl_event_tone, {.tone = MSCL_TONE(4, MSCL_B) }},

	{mscl_event_length, {.length = mscl_time(1.0 / 2.0) }},
	{mscl_event_tone, {.tone = MSCL_TONE(5, MSCL_D) }},
	{mscl_event_tone, {.tone = MSCL_TONE(4, MSCL_B) }},
	{mscl_event_length, {.length = mscl_time(1.0 / 1.0) }},
	{mscl_event_tone, {.tone = MSCL_TONE(5, MSCL_D) }},
	{mscl_event_rest, {}},
	{mscl_event_length, {.length = mscl_time(1.0 / 4.0) }},
	{mscl_event_rest, {}},
	{mscl_event_rest, {}},
	{mscl_event_tone, {.tone = MSCL_TONE(4, MSCL_B) }},
	{mscl_event_tone, {.tone = MSCL_TONE(4, MSCL_A) }},

	{mscl_event_length, {.length = mscl_time(1.0 / 2.0) }},
	{mscl_event_tone, {.tone = MSCL_TONE(4, MSCL_B) }},
	{mscl_event_tone, {.tone = MSCL_TONE(4, MSCL_B) }},
	{mscl_event_length, {.length = mscl_time(1.0 / 1.0) }},
	{mscl_event_tone, {.tone = MSCL_TONE(4, MSCL_B) }},
	{mscl_event_rest, {}},
	{mscl_event_rest, {}},

	{mscl_event_length, {.length = mscl_time(1.0 / 4.0) }},
	{mscl_event_tone, {.tone = MSCL_TONE(5, MSCL_D) }},
	{mscl_event_tone, {.tone = MSCL_TONE(4, MSCL_B) }},
	{mscl_event_tone, {.tone = MSCL_TONE(4, MSCL_B) }},
	{mscl_event_tone, {.tone = MSCL_TONE(4, MSCL_B) }},
	{mscl_event_length, {.length = mscl_time(1.0 / 1.0) }},
	{mscl_event_tone, {.tone = MSCL_TONE(4, MSCL_B) }},
	{mscl_event_rest, {}},
	{mscl_event_tone, {.tone = MSCL_TONE(5, MSCL_Fs) }},

	{mscl_event_length, {.length = mscl_time(1.0 / 2.0) }},
	{mscl_event_tone, {.tone = MSCL_TONE(5, MSCL_Fs) }},
	{mscl_event_tone, {.tone = MSCL_TONE(5, MSCL_Fs) }},
	{mscl_event_length, {.length = mscl_time(1.0 / 1.0) }},
	{mscl_event_rest, {}},
	{mscl_event_rest, {}},
	{mscl_event_length, {.length = mscl_time(1.0 / 4.0) }},
	{mscl_event_rest, {}},
	{mscl_event_rest, {}},
	{mscl_event_length, {.length = mscl_time(1.0 / 2.0) }},
	{mscl_event_waveform, {.waveform = wav_saw }},
	{mscl_event_volume, {.volume = mscl_sample(0.15) }},
	{mscl_event_tone, {.tone = MSCL_TONE(4, MSCL_B) }},

	{mscl_event_length, {.length = mscl_time(3.0 / 4.0) }},
	{mscl_event_tone, {.tone = MSCL_TONE(5, MSCL_D) }},
	{mscl_event_length, {.length = mscl_time(1.0 / 4.0) }},
	{mscl_event_tone, {.tone = MSCL_TONE(4, MSCL_B) }},
	{mscl_event_rest, {}},
	{mscl_event_rest, {}},
	{mscl_event_length, {.length = mscl_time(3.0 / 4.0) }},
	{mscl_event_tone, {.tone = MSCL_TONE(5, MSCL_D) }},
	{mscl_event_length, {.length = mscl_time(1.0 / 4.0) }},
	{mscl_event_tone, {.tone = MSCL_TONE(4, MSCL_B) }},
	{mscl_event_rest, {}},
	{mscl_event_rest, {}},
	{mscl_event_length, {.length = mscl_time(3.0 / 4.0) }},
	{mscl_event_tone, {.tone = MSCL_TONE(5, MSCL_D) }},
	{mscl_event_length, {.length = mscl_time(1.0 / 4.0) }},
	{mscl_event_tone, {.tone = MSCL_TONE(4, MSCL_B) }},

	{mscl_event_length, {.length = mscl_time(1.0 / 4.0) }},
	{mscl_event_rest, {}},
	{mscl_event_rest, {}},
	{mscl_event_length, {.length = mscl_time(3.0 / 4.0) }},
	{mscl_event_tone, {.tone = MSCL_TONE(5, MSCL_D) }},
	{mscl_event_length, {.length = mscl_time(1.0 / 4.0) }},
	{mscl_event_tone, {.tone = MSCL_TONE(4, MSCL_B) }},
	{mscl_event_rest, {}},
	{mscl_event_rest, {}},
	{mscl_event_length, {.length = mscl_time(1.0 / 2.0) }},
	{mscl_event_tone, {.tone = MSCL_TONE(5, MSCL_D) }},
	{mscl_event_tone, {.tone = MSCL_TONE(4, MSCL_B) }},
	{mscl_event_length, {.length = mscl_time(1.0 / 4.0) }},
	{mscl_event_tone, {.tone = MSCL_TONE(4, MSCL_A) }},
	{mscl_event_tone, {.tone = MSCL_TONE(4, MSCL_As) }},
	{mscl_event_length, {.length = mscl_time(1.0 / 2.0) }},
	{mscl_event_tone, {.tone = MSCL_TONE(4, MSCL_B) }},

	{mscl_event_length, {.length = mscl_time(3.0 / 4.0) }},
	{mscl_event_tone, {.tone = MSCL_TONE(5, MSCL_D) }},
	{mscl_event_length, {.length = mscl_time(1.0 / 4.0) }},
	{mscl_event_tone, {.tone = MSCL_TONE(4, MSCL_B) }},
	{mscl_event_rest, {}},
	{mscl_event_rest, {}},
	{mscl_event_length, {.length = mscl_time(3.0 / 4.0) }},
	{mscl_event_tone, {.tone = MSCL_TONE(5, MSCL_D) }},
	{mscl_event_length, {.length = mscl_time(1.0 / 4.0) }},
	{mscl_event_tone, {.tone = MSCL_TONE(4, MSCL_B) }},
	{mscl_event_rest, {}},
	{mscl_event_rest, {}},
	{mscl_event_length, {.length = mscl_time(3.0 / 4.0) }},
	{mscl_event_tone, {.tone = MSCL_TONE(5, MSCL_D) }},
	{mscl_event_length, {.length = mscl_time(1.0 / 4.0) }},
	{mscl_event_tone, {.tone = MSCL_TONE(4, MSCL_B) }},

	{mscl_event_length, {.length = mscl_time(1.0 / 4.0) }},
	{mscl_event_rest, {}},
	{mscl_event_rest, {}},
	{mscl_event_length, {.length = mscl_time(3.0 / 4.0) }},
	{mscl_event_tone, {.tone = MSCL_TONE(5, MSCL_D) }},
	{mscl_event_length, {.length = mscl_time(1.0 / 4.0) }},
	{mscl_event_tone, {.tone = MSCL_TONE(4, MSCL_B) }},
	{mscl_event_rest, {}},
	{mscl_event_rest, {}},
	{mscl_event_length, {.length = mscl_time(1.0 / 2.0) }},
	{mscl_event_tone, {.tone = MSCL_TONE(5, MSCL_D) }},
	{mscl_event_tone, {.tone = MSCL_TONE(4, MSCL_B) }},
	{mscl_event_length, {.length = mscl_time(1.0 / 4.0) }},
	{mscl_event_tone, {.tone = MSCL_TONE(4, MSCL_A) }},
	{mscl_event_tone, {.tone = MSCL_TONE(4, MSCL_As) }},
	{mscl_event_length, {.length = mscl_time(1.0 / 2.0) }},
	{mscl_event_tone, {.tone = MSCL_TONE(4, MSCL_B) }},

	{mscl_event_waveform, {.waveform = wav_saw }},
	{mscl_event_volume, {.volume = mscl_sample(0.15) }},
	{mscl_event_length, {.length = mscl_time(3.0 / 4.0) }},
	{mscl_event_tone, {.tone = MSCL_TONE(5, MSCL_D) }},
	{mscl_event_length, {.length = mscl_time(1.0 / 4.0) }},
	{mscl_event_tone, {.tone = MSCL_TONE(4, MSCL_B) }},
	{mscl_event_rest, {}},
	{mscl_event_rest, {}},
	{mscl_event_length, {.length = mscl_time(3.0 / 4.0) }},
	{mscl_event_tone, {.tone = MSCL_TONE(5, MSCL_D) }},
	{mscl_event_length, {.length = mscl_time(1.0 / 4.0) }},
	{mscl_event_tone, {.tone = MSCL_TONE(4, MSCL_B) }},
	{mscl_event_rest, {}},
	{mscl_event_rest, {}},
	{mscl_event_length, {.length = mscl_time(3.0 / 4.0) }},
	{mscl_event_tone, {.tone = MSCL_TONE(5, MSCL_D) }},
	{mscl_event_length, {.length = mscl_time(1.0 / 4.0) }},
	{mscl_event_tone, {.tone = MSCL_TONE(4, MSCL_B) }},

	{mscl_event_length, {.length = mscl_time(1.0 / 4.0) }},
	{mscl_event_rest, {}},
	{mscl_event_rest, {}},
	{mscl_event_length, {.length = mscl_time(3.0 / 4.0) }},
	{mscl_event_tone, {.tone = MSCL_TONE(5, MSCL_D) }},
	{mscl_event_length, {.length = mscl_time(1.0 / 4.0) }},
	{mscl_event_tone, {.tone = MSCL_TONE(4, MSCL_B) }},
	{mscl_event_rest, {}},
	{mscl_event_rest, {}},
	{mscl_event_length, {.length = mscl_time(1.0 / 2.0) }},
	{mscl_event_tone, {.tone = MSCL_TONE(5, MSCL_D) }},
	{mscl_event_tone, {.tone = MSCL_TONE(4, MSCL_B) }},
	{mscl_event_length, {.length = mscl_time(1.0 / 4.0) }},
	{mscl_event_tone, {.tone = MSCL_TONE(4, MSCL_A) }},
	{mscl_event_tone, {.tone = MSCL_TONE(4, MSCL_As) }},
	{mscl_event_length, {.length = mscl_time(1.0 / 2.0) }},
	{mscl_event_tone, {.tone = MSCL_TONE(4, MSCL_B) }},

	{mscl_event_length, {.length = mscl_time(3.0 / 4.0) }},
	{mscl_event_tone, {.tone = MSCL_TONE(5, MSCL_D) }},
	{mscl_event_length, {.length = mscl_time(1.0 / 4.0) }},
	{mscl_event_tone, {.tone = MSCL_TONE(4, MSCL_B) }},
	{mscl_event_rest, {}},
	{mscl_event_rest, {}},
	{mscl_event_length, {.length = mscl_time(3.0 / 4.0) }},
	{mscl_event_tone, {.tone = MSCL_TONE(5, MSCL_D) }},
	{mscl_event_length, {.length = mscl_time(1.0 / 4.0) }},
	{mscl_event_tone, {.tone = MSCL_TONE(4, MSCL_B) }},
	{mscl_event_rest, {}},
	{mscl_event_rest, {}},
	{mscl_event_length, {.length = mscl_time(3.0 / 4.0) }},
	{mscl_event_tone, {.tone = MSCL_TONE(5, MSCL_D) }},
	{mscl_event_length, {.length = mscl_time(1.0 / 4.0) }},
	{mscl_event_tone, {.tone = MSCL_TONE(4, MSCL_B) }},

	{mscl_event_length, {.length = mscl_time(1.0 / 4.0) }},
	{mscl_event_rest, {}},
	{mscl_event_rest, {}},
	{mscl_event_length, {.length = mscl_time(3.0 / 4.0) }},
	{mscl_event_tone, {.tone = MSCL_TONE(5, MSCL_D) }},
	{mscl_event_length, {.length = mscl_time(1.0 / 4.0) }},
	{mscl_event_tone, {.tone = MSCL_TONE(4, MSCL_B) }},
	{mscl_event_rest, {}},
	{mscl_event_rest, {}},
	{mscl_event_length, {.length = mscl_time(1.0 / 2.0) }},
	{mscl_event_tone, {.tone = MSCL_TONE(5, MSCL_D) }},
	{mscl_event_tone, {.tone = MSCL_TONE(4, MSCL_B) }},
	{mscl_event_length, {.length = mscl_time(1.0 / 4.0) }},
	{mscl_event_tone, {.tone = MSCL_TONE(4, MSCL_A) }},
	{mscl_event_tone, {.tone = MSCL_TONE(4, MSCL_As) }},
	{mscl_event_length, {.length = mscl_time(1.0 / 2.0) }},
	{mscl_event_tone, {.tone = MSCL_TONE(4, MSCL_B) }},

	{mscl_event_loop_end, {}},
};

// --------------------------------------------------------------------------------------------------------------------------------

inline static constexpr mscl_event c2[] = {
	{mscl_event_sustain, {.sustain = env_fade }},
	{mscl_event_release, {.release = rel_drop }},
	{mscl_event_vibrato, {.vibrato = vib_medium }},

	{mscl_event_loop_begin, {.loop_begin = MSCL_LOOP_INFINITE }},

	{mscl_event_waveform, {.waveform = wav_tri }},
	
	{mscl_event_loop_begin, {.loop_begin = 0 }},
	{mscl_event_volume, {.volume = mscl_sample(0.25) }},
	{mscl_event_loop_begin, {.loop_begin = 2 }},
	{mscl_event_length, {.length = mscl_time(2.0 / 1.0) }},
	{mscl_event_rest, {}},
	{mscl_event_length, {.length = mscl_time(1.0 / 1.0) }},
	{mscl_event_tone, {.tone = MSCL_TONE(5, MSCL_A) }},
	{mscl_event_tone, {.tone = MSCL_TONE(5, MSCL_Gs) }},
	{mscl_event_loop_end, {}},
	{mscl_event_length, {.length = mscl_time(2.0 / 1.0) }},
	{mscl_event_rest, {}},
	{mscl_event_length, {.length = mscl_time(1.0 / 2.0) }},
	{mscl_event_tone, {.tone = MSCL_TONE(5, MSCL_A) }},
	{mscl_event_tone, {.tone = MSCL_TONE(5, MSCL_A) }},
	{mscl_event_length, {.length = mscl_time(1.0 / 1.0) }},
	{mscl_event_tone, {.tone = MSCL_TONE(5, MSCL_Gs) }},
	{mscl_event_loop_end, {}},

	// {mscl_event_length, {.length = mscl_time(16.0 * 1) }},
	// {mscl_event_rest, {}},
	{mscl_event_loop_begin, {.loop_begin = 0 }},
	{mscl_event_volume, {.volume = mscl_sample(0.175) }},
	{mscl_event_loop_begin, {.loop_begin = 2 }},
	{mscl_event_length, {.length = mscl_time(2.0 / 1.0) }},
	{mscl_event_rest, {}},
	{mscl_event_length, {.length = mscl_time(1.0 / 1.0) }},
	{mscl_event_tone, {.tone = MSCL_TONE(5, MSCL_A) }},
	{mscl_event_tone, {.tone = MSCL_TONE(5, MSCL_Gs) }},
	{mscl_event_loop_end, {}},
	{mscl_event_length, {.length = mscl_time(2.0 / 1.0) }},
	{mscl_event_rest, {}},
	{mscl_event_length, {.length = mscl_time(1.0 / 2.0) }},
	{mscl_event_tone, {.tone = MSCL_TONE(5, MSCL_A) }},
	{mscl_event_tone, {.tone = MSCL_TONE(5, MSCL_A) }},
	{mscl_event_length, {.length = mscl_time(1.0 / 1.0) }},
	{mscl_event_tone, {.tone = MSCL_TONE(5, MSCL_Gs) }},
	{mscl_event_loop_end, {}},

	{mscl_event_loop_begin, {.loop_begin = 1 }},
	{mscl_event_volume, {.volume = mscl_sample(0.25) }},
	{mscl_event_loop_begin, {.loop_begin = 2 }},
	{mscl_event_length, {.length = mscl_time(2.0 / 1.0) }},
	{mscl_event_rest, {}},
	{mscl_event_length, {.length = mscl_time(1.0 / 1.0) }},
	{mscl_event_tone, {.tone = MSCL_TONE(5, MSCL_A) }},
	{mscl_event_tone, {.tone = MSCL_TONE(5, MSCL_Gs) }},
	{mscl_event_loop_end, {}},
	{mscl_event_length, {.length = mscl_time(2.0 / 1.0) }},
	{mscl_event_rest, {}},
	{mscl_event_length, {.length = mscl_time(1.0 / 2.0) }},
	{mscl_event_tone, {.tone = MSCL_TONE(5, MSCL_A) }},
	{mscl_event_tone, {.tone = MSCL_TONE(5, MSCL_A) }},
	{mscl_event_length, {.length = mscl_time(1.0 / 1.0) }},
	{mscl_event_tone, {.tone = MSCL_TONE(5, MSCL_Gs) }},
	{mscl_event_loop_end, {}},

	{mscl_event_waveform, {.waveform = wav_saw }},
	{mscl_event_volume, {.volume = mscl_sample(0.175) }},

	{mscl_event_loop_begin, {.loop_begin = 1 }},
	{mscl_event_length, {.length = mscl_time(3.0 / 4.0) }},
	{mscl_event_tone, {.tone = MSCL_TONE(4, MSCL_Fs) }},
	{mscl_event_length, {.length = mscl_time(1.0 / 4.0) }},
	{mscl_event_tone, {.tone = MSCL_TONE(4, MSCL_D) }},
	{mscl_event_rest, {}},
	{mscl_event_rest, {}},
	{mscl_event_length, {.length = mscl_time(3.0 / 4.0) }},
	{mscl_event_tone, {.tone = MSCL_TONE(4, MSCL_Fs) }},
	{mscl_event_length, {.length = mscl_time(1.0 / 4.0) }},
	{mscl_event_tone, {.tone = MSCL_TONE(4, MSCL_D) }},
	{mscl_event_rest, {}},
	{mscl_event_rest, {}},
	{mscl_event_length, {.length = mscl_time(3.0 / 4.0) }},
	{mscl_event_tone, {.tone = MSCL_TONE(4, MSCL_Fs) }},
	{mscl_event_length, {.length = mscl_time(1.0 / 4.0) }},
	{mscl_event_tone, {.tone = MSCL_TONE(4, MSCL_D) }},

	{mscl_event_length, {.length = mscl_time(1.0 / 4.0) }},
	{mscl_event_rest, {}},
	{mscl_event_rest, {}},
	{mscl_event_length, {.length = mscl_time(3.0 / 4.0) }},
	{mscl_event_tone, {.tone = MSCL_TONE(4, MSCL_Fs) }},
	{mscl_event_length, {.length = mscl_time(1.0 / 4.0) }},
	{mscl_event_tone, {.tone = MSCL_TONE(4, MSCL_D) }},
	{mscl_event_rest, {}},
	{mscl_event_rest, {}},
	{mscl_event_length, {.length = mscl_time(1.0 / 2.0) }},
	{mscl_event_tone, {.tone = MSCL_TONE(4, MSCL_Fs) }},
	{mscl_event_tone, {.tone = MSCL_TONE(4, MSCL_D) }},
	{mscl_event_length, {.length = mscl_time(1.0 / 4.0) }},
	{mscl_event_tone, {.tone = MSCL_TONE(4, MSCL_C) }},
	{mscl_event_tone, {.tone = MSCL_TONE(4, MSCL_Cs) }},
	{mscl_event_length, {.length = mscl_time(1.0 / 2.0) }},
	{mscl_event_tone, {.tone = MSCL_TONE(4, MSCL_D) }},
	{mscl_event_loop_end, {}},

	// {mscl_event_length, {.length = mscl_time(16.0 * 1) }},
	// {mscl_event_rest, {}},

	{mscl_event_length, {.length = mscl_time(3.0 / 4.0) }},
	{mscl_event_tone, {.tone = MSCL_TONE(5, MSCL_Fs) }},
	{mscl_event_length, {.length = mscl_time(1.0 / 4.0) }},
	{mscl_event_tone, {.tone = MSCL_TONE(5, MSCL_D) }},
	{mscl_event_rest, {}},
	{mscl_event_rest, {}},
	{mscl_event_length, {.length = mscl_time(3.0 / 4.0) }},
	{mscl_event_tone, {.tone = MSCL_TONE(5, MSCL_Fs) }},
	{mscl_event_length, {.length = mscl_time(1.0 / 4.0) }},
	{mscl_event_tone, {.tone = MSCL_TONE(5, MSCL_D) }},
	{mscl_event_rest, {}},
	{mscl_event_rest, {}},
	{mscl_event_length, {.length = mscl_time(3.0 / 4.0) }},
	{mscl_event_tone, {.tone = MSCL_TONE(5, MSCL_Fs) }},
	{mscl_event_length, {.length = mscl_time(1.0 / 4.0) }},
	{mscl_event_tone, {.tone = MSCL_TONE(5, MSCL_D) }},

	{mscl_event_length, {.length = mscl_time(1.0 / 4.0) }},
	{mscl_event_rest, {}},
	{mscl_event_rest, {}},
	{mscl_event_length, {.length = mscl_time(3.0 / 4.0) }},
	{mscl_event_tone, {.tone = MSCL_TONE(5, MSCL_Fs) }},
	{mscl_event_length, {.length = mscl_time(1.0 / 4.0) }},
	{mscl_event_tone, {.tone = MSCL_TONE(5, MSCL_D) }},
	{mscl_event_rest, {}},
	{mscl_event_rest, {}},
	{mscl_event_length, {.length = mscl_time(1.0 / 2.0) }},
	{mscl_event_tone, {.tone = MSCL_TONE(5, MSCL_Fs) }},
	{mscl_event_tone, {.tone = MSCL_TONE(5, MSCL_D) }},
	{mscl_event_length, {.length = mscl_time(1.0 / 4.0) }},
	{mscl_event_tone, {.tone = MSCL_TONE(5, MSCL_C) }},
	{mscl_event_tone, {.tone = MSCL_TONE(5, MSCL_Cs) }},
	{mscl_event_length, {.length = mscl_time(1.0 / 2.0) }},
	{mscl_event_tone, {.tone = MSCL_TONE(5, MSCL_D) }},

	{mscl_event_length, {.length = mscl_time(3.0 / 4.0) }},
	{mscl_event_tone, {.tone = MSCL_TONE(5, MSCL_Fs) }},
	{mscl_event_length, {.length = mscl_time(1.0 / 4.0) }},
	{mscl_event_tone, {.tone = MSCL_TONE(5, MSCL_D) }},
	{mscl_event_rest, {}},
	{mscl_event_rest, {}},
	{mscl_event_length, {.length = mscl_time(3.0 / 4.0) }},
	{mscl_event_tone, {.tone = MSCL_TONE(5, MSCL_Fs) }},
	{mscl_event_length, {.length = mscl_time(1.0 / 4.0) }},
	{mscl_event_tone, {.tone = MSCL_TONE(5, MSCL_D) }},
	{mscl_event_rest, {}},
	{mscl_event_rest, {}},
	{mscl_event_length, {.length = mscl_time(3.0 / 4.0) }},
	{mscl_event_tone, {.tone = MSCL_TONE(5, MSCL_Fs) }},
	{mscl_event_length, {.length = mscl_time(1.0 / 4.0) }},
	{mscl_event_tone, {.tone = MSCL_TONE(5, MSCL_D) }},

	{mscl_event_length, {.length = mscl_time(1.0 / 4.0) }},
	{mscl_event_rest, {}},
	{mscl_event_rest, {}},
	{mscl_event_length, {.length = mscl_time(3.0 / 4.0) }},
	{mscl_event_tone, {.tone = MSCL_TONE(5, MSCL_Fs) }},
	{mscl_event_length, {.length = mscl_time(1.0 / 4.0) }},
	{mscl_event_tone, {.tone = MSCL_TONE(5, MSCL_D) }},
	{mscl_event_rest, {}},
	{mscl_event_rest, {}},
	{mscl_event_length, {.length = mscl_time(1.0 / 1.0) }},
	{mscl_event_tone, {.tone = MSCL_TONE(5, MSCL_B) }},
	{mscl_event_tone, {.tone = MSCL_TONE(5, MSCL_B) }},

	{mscl_event_loop_end, {}},
};

// --------------------------------------------------------------------------------------------------------------------------------

inline static constexpr mscl_event c3[] = {
	{mscl_event_sustain, {.sustain = env_fade }},
	{mscl_event_release, {.release = rel_drop }},
	{mscl_event_vibrato, {.vibrato = vib_medium }},

	{mscl_event_loop_begin, {.loop_begin = MSCL_LOOP_INFINITE }},

	{mscl_event_waveform, {.waveform = wav_tri }},
	
	{mscl_event_loop_begin, {.loop_begin = 0 }},
	{mscl_event_volume, {.volume = mscl_sample(0.125) }},
	{mscl_event_loop_begin, {.loop_begin = 2 }},
	{mscl_event_length, {.length = mscl_time(2.0 / 1.0) }},
	{mscl_event_rest, {}},
	{mscl_event_length, {.length = mscl_time(1.0 / 1.0) }},
	{mscl_event_tone, {.tone = MSCL_TONE(5, MSCL_E) }},
	{mscl_event_tone, {.tone = MSCL_TONE(5, MSCL_E) }},
	{mscl_event_loop_end, {}},
	{mscl_event_length, {.length = mscl_time(2.0 / 1.0) }},
	{mscl_event_rest, {}},
	{mscl_event_length, {.length = mscl_time(1.0 / 2.0) }},
	{mscl_event_tone, {.tone = MSCL_TONE(5, MSCL_E) }},
	{mscl_event_tone, {.tone = MSCL_TONE(5, MSCL_E) }},
	{mscl_event_length, {.length = mscl_time(1.0 / 1.0) }},
	{mscl_event_tone, {.tone = MSCL_TONE(5, MSCL_E) }},
	{mscl_event_loop_end, {}},

	// {mscl_event_length, {.length = mscl_time(16.0 * 1) }},
	// {mscl_event_rest, {}},

	{mscl_event_loop_begin, {.loop_begin = 0 }},
	{mscl_event_volume, {.volume = mscl_sample(0.125) }},
	{mscl_event_loop_begin, {.loop_begin = 2 }},
	{mscl_event_length, {.length = mscl_time(2.0 / 1.0) }},
	{mscl_event_rest, {}},
	{mscl_event_length, {.length = mscl_time(1.0 / 1.0) }},
	{mscl_event_tone, {.tone = MSCL_TONE(5, MSCL_E) }},
	{mscl_event_tone, {.tone = MSCL_TONE(5, MSCL_E) }},
	{mscl_event_loop_end, {}},
	{mscl_event_length, {.length = mscl_time(2.0 / 1.0) }},
	{mscl_event_rest, {}},
	{mscl_event_length, {.length = mscl_time(1.0 / 2.0) }},
	{mscl_event_tone, {.tone = MSCL_TONE(5, MSCL_E) }},
	{mscl_event_tone, {.tone = MSCL_TONE(5, MSCL_E) }},
	{mscl_event_length, {.length = mscl_time(1.0 / 1.0) }},
	{mscl_event_tone, {.tone = MSCL_TONE(5, MSCL_E) }},
	{mscl_event_loop_end, {}},

	{mscl_event_loop_begin, {.loop_begin = 1 }},
	{mscl_event_volume, {.volume = mscl_sample(0.125) }},
	{mscl_event_loop_begin, {.loop_begin = 2 }},
	{mscl_event_length, {.length = mscl_time(2.0 / 1.0) }},
	{mscl_event_rest, {}},
	{mscl_event_length, {.length = mscl_time(1.0 / 1.0) }},
	{mscl_event_tone, {.tone = MSCL_TONE(5, MSCL_E) }},
	{mscl_event_tone, {.tone = MSCL_TONE(5, MSCL_E) }},
	{mscl_event_loop_end, {}},
	{mscl_event_length, {.length = mscl_time(2.0 / 1.0) }},
	{mscl_event_rest, {}},
	{mscl_event_length, {.length = mscl_time(1.0 / 2.0) }},
	{mscl_event_tone, {.tone = MSCL_TONE(5, MSCL_E) }},
	{mscl_event_tone, {.tone = MSCL_TONE(5, MSCL_E) }},
	{mscl_event_length, {.length = mscl_time(1.0 / 1.0) }},
	{mscl_event_tone, {.tone = MSCL_TONE(5, MSCL_E) }},
	{mscl_event_loop_end, {}},

	{mscl_event_length, {.length = mscl_time(16.0 * 2) }},
	{mscl_event_rest, {}},

	{mscl_event_loop_end, {}},
};

// --------------------------------------------------------------------------------------------------------------------------------

inline static constexpr mscl_event c4[] = {
	{mscl_event_sustain, {.sustain = env_fade }},
	{mscl_event_release, {.release = rel_drop }},
	{mscl_event_vibrato, {.vibrato = vib_medium }},

	{mscl_event_loop_begin, {.loop_begin = MSCL_LOOP_INFINITE }},

	{mscl_event_waveform, {.waveform = wav_tri }},
	
	{mscl_event_loop_begin, {.loop_begin = 0 }},
	{mscl_event_volume, {.volume = mscl_sample(0.125) }},
	{mscl_event_loop_begin, {.loop_begin = 2 }},
	{mscl_event_length, {.length = mscl_time(2.0 / 1.0) }},
	{mscl_event_rest, {}},
	{mscl_event_length, {.length = mscl_time(1.0 / 1.0) }},
	{mscl_event_tone, {.tone = MSCL_TONE(5, MSCL_Cs) }},
	{mscl_event_tone, {.tone = MSCL_TONE(4, MSCL_B) }},
	{mscl_event_loop_end, {}},
	{mscl_event_length, {.length = mscl_time(2.0 / 1.0) }},
	{mscl_event_rest, {}},
	{mscl_event_length, {.length = mscl_time(1.0 / 2.0) }},
	{mscl_event_tone, {.tone = MSCL_TONE(5, MSCL_Cs) }},
	{mscl_event_tone, {.tone = MSCL_TONE(5, MSCL_Cs) }},
	{mscl_event_length, {.length = mscl_time(1.0 / 1.0) }},
	{mscl_event_tone, {.tone = MSCL_TONE(4, MSCL_B) }},
	{mscl_event_loop_end, {}},

	// {mscl_event_length, {.length = mscl_time(16.0 * 1) }},
	// {mscl_event_rest, {}},

	{mscl_event_loop_begin, {.loop_begin = 0 }},
	{mscl_event_volume, {.volume = mscl_sample(0.125) }},
	{mscl_event_loop_begin, {.loop_begin = 2 }},
	{mscl_event_length, {.length = mscl_time(2.0 / 1.0) }},
	{mscl_event_rest, {}},
	{mscl_event_length, {.length = mscl_time(1.0 / 1.0) }},
	{mscl_event_tone, {.tone = MSCL_TONE(5, MSCL_Cs) }},
	{mscl_event_tone, {.tone = MSCL_TONE(4, MSCL_B) }},
	{mscl_event_loop_end, {}},
	{mscl_event_length, {.length = mscl_time(2.0 / 1.0) }},
	{mscl_event_rest, {}},
	{mscl_event_length, {.length = mscl_time(1.0 / 2.0) }},
	{mscl_event_tone, {.tone = MSCL_TONE(5, MSCL_Cs) }},
	{mscl_event_tone, {.tone = MSCL_TONE(5, MSCL_Cs) }},
	{mscl_event_length, {.length = mscl_time(1.0 / 1.0) }},
	{mscl_event_tone, {.tone = MSCL_TONE(4, MSCL_B) }},
	{mscl_event_loop_end, {}},

	{mscl_event_loop_begin, {.loop_begin = 1 }},
	{mscl_event_volume, {.volume = mscl_sample(0.125) }},
	{mscl_event_loop_begin, {.loop_begin = 2 }},
	{mscl_event_length, {.length = mscl_time(2.0 / 1.0) }},
	{mscl_event_rest, {}},
	{mscl_event_length, {.length = mscl_time(1.0 / 1.0) }},
	{mscl_event_tone, {.tone = MSCL_TONE(5, MSCL_Cs) }},
	{mscl_event_tone, {.tone = MSCL_TONE(4, MSCL_B) }},
	{mscl_event_loop_end, {}},
	{mscl_event_length, {.length = mscl_time(2.0 / 1.0) }},
	{mscl_event_rest, {}},
	{mscl_event_length, {.length = mscl_time(1.0 / 2.0) }},
	{mscl_event_tone, {.tone = MSCL_TONE(5, MSCL_Cs) }},
	{mscl_event_tone, {.tone = MSCL_TONE(5, MSCL_Cs) }},
	{mscl_event_length, {.length = mscl_time(1.0 / 1.0) }},
	{mscl_event_tone, {.tone = MSCL_TONE(4, MSCL_B) }},
	{mscl_event_loop_end, {}},

	{mscl_event_length, {.length = mscl_time(16.0 * 2) }},
	{mscl_event_rest, {}},

	{mscl_event_loop_end, {}},
};

// --------------------------------------------------------------------------------------------------------------------------------

inline static constexpr mscl_event c5[] = {

	{mscl_event_loop_begin, {.loop_begin = MSCL_LOOP_INFINITE }},

	{mscl_event_length, {.length = mscl_time(16.0 * 4.0) }},
	{mscl_event_rest, {}},

	{mscl_event_loop_begin, {.loop_begin = 1 }},
	{mscl_event_sustain, {.sustain = env_fade_slow }},
	{mscl_event_release, {.release = rel_fade }},
	{mscl_event_vibrato, {.vibrato = vib_some }},
	{mscl_event_waveform, {.waveform = wav_saw }},
	{mscl_event_volume, {.volume = mscl_sample(0.15) }},
	{mscl_event_length, {.length = mscl_time(3.0 / 1.0) }},
	{mscl_event_tone, {.tone = MSCL_TONE(2, MSCL_B) }},
	{mscl_event_tone, {.tone = MSCL_TONE(2, MSCL_A) }},
	{mscl_event_length, {.length = mscl_time(1.0 / 2.0) }},
	{mscl_event_tone, {.tone = MSCL_TONE(2, MSCL_A) }},
	{mscl_event_tone, {.tone = MSCL_TONE(2, MSCL_A) }},
	{mscl_event_length, {.length = mscl_time(1.0 / 4.0) }},
	{mscl_event_tone, {.tone = MSCL_TONE(2, MSCL_A) }},
	{mscl_event_tone, {.tone = MSCL_TONE(2, MSCL_A) }},
	{mscl_event_length, {.length = mscl_time(1.0 / 2.0) }},
	{mscl_event_tone, {.tone = MSCL_TONE(2, MSCL_A) }},
	{mscl_event_length, {.length = mscl_time(3.0 / 1.0) }},
	{mscl_event_tone, {.tone = MSCL_TONE(2, MSCL_Gs) }},
	{mscl_event_tone, {.tone = MSCL_TONE(2, MSCL_E) }},
	{mscl_event_length, {.length = mscl_time(1.0 / 2.0) }},
	{mscl_event_tone, {.tone = MSCL_TONE(2, MSCL_E) }},
	{mscl_event_tone, {.tone = MSCL_TONE(2, MSCL_E) }},
	{mscl_event_length, {.length = mscl_time(1.0 / 4.0) }},
	{mscl_event_tone, {.tone = MSCL_TONE(2, MSCL_E) }},
	{mscl_event_tone, {.tone = MSCL_TONE(2, MSCL_E) }},
	{mscl_event_length, {.length = mscl_time(1.0 / 2.0) }},
	{mscl_event_tone, {.tone = MSCL_TONE(2, MSCL_E) }},
	{mscl_event_loop_end, {}},

	{mscl_event_loop_end, {}},
};

// --------------------------------------------------------------------------------------------------------------------------------

inline static constexpr mscl::Song song
{
    "Ghostbusters",
    120.0,
    {c0, c1, c2, c3, c4, c5}
};

// ================================================================================================================================
}
