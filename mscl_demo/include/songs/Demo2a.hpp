/**
 * @file mscl_demo/songs/Demo2a.hpp
 */

#pragma once

#include <mscl.h>
#include <mscl_gui.hpp>
#include "instruments.hpp"

namespace songs::Demo2
{
// ================================================================================================================================

inline static constexpr mscl_event c0[] = {
	{mscl_event_volume, {.volume = mscl_fp(0.10) }},
	{mscl_event_sustain, {.sustain = env_fade }},
	{mscl_event_release, {.release = rel_drop }},
	{mscl_event_vibrato, {.vibrato = vib_medium }},
	{mscl_event_waveform, {.waveform = wav_square }},

	{mscl_event_length, {.length = mscl_fp(1.0 / 8.0) }},
	{mscl_event_tone, {.tone = MSCL_TONE(3, MSCL_C) }},
	{mscl_event_length, {.length = mscl_fp(1.0 / 4.0) }},
	{mscl_event_tone, {.tone = MSCL_TONE(2, MSCL_C) }},
	{mscl_event_tone, {.tone = MSCL_TONE(2, MSCL_C) }},
	{mscl_event_length, {.length = mscl_fp(1.0 / 8.0) }},
	{mscl_event_tone, {.tone = MSCL_TONE(2, MSCL_C) }},
	{mscl_event_tone, {.tone = MSCL_TONE(3, MSCL_As) }},
	{mscl_event_tone, {.tone = MSCL_TONE(4, MSCL_C) }},

	{mscl_event_length, {.length = mscl_fp(1.0 / 8.0) }},
	{mscl_event_tone, {.tone = MSCL_TONE(3, MSCL_C) }},
	{mscl_event_length, {.length = mscl_fp(1.0 / 4.0) }},
	{mscl_event_tone, {.tone = MSCL_TONE(2, MSCL_C) }},
	{mscl_event_tone, {.tone = MSCL_TONE(2, MSCL_C) }},
	{mscl_event_length, {.length = mscl_fp(1.0 / 8.0) }},
	{mscl_event_tone, {.tone = MSCL_TONE(2, MSCL_C) }},
	{mscl_event_tone, {.tone = MSCL_TONE(3, MSCL_As) }},
	{mscl_event_tone, {.tone = MSCL_TONE(4, MSCL_C) }},

	{mscl_event_length, {.length = mscl_fp(1.0 / 8.0) }},
	{mscl_event_tone, {.tone = MSCL_TONE(3, MSCL_As) }},
	{mscl_event_tone, {.tone = MSCL_TONE(3, MSCL_C) }},
	{mscl_event_tone, {.tone = MSCL_TONE(2, MSCL_C) }},
	{mscl_event_length, {.length = mscl_fp(1.0 / 4.0) }},
	{mscl_event_tone, {.tone = MSCL_TONE(2, MSCL_C) }},
	{mscl_event_length, {.length = mscl_fp(1.0 / 8.0) }},
	{mscl_event_tone, {.tone = MSCL_TONE(2, MSCL_C) }},
	{mscl_event_tone, {.tone = MSCL_TONE(3, MSCL_As) }},
	{mscl_event_tone, {.tone = MSCL_TONE(4, MSCL_C) }},

	{mscl_event_length, {.length = mscl_fp(1.0 / 8.0) }},
	{mscl_event_tone, {.tone = MSCL_TONE(3, MSCL_C) }},
	{mscl_event_length, {.length = mscl_fp(1.0 / 4.0) }},
	{mscl_event_tone, {.tone = MSCL_TONE(2, MSCL_C) }},
	{mscl_event_tone, {.tone = MSCL_TONE(2, MSCL_C) }},
	{mscl_event_length, {.length = mscl_fp(1.0 / 8.0) }},
	{mscl_event_tone, {.tone = MSCL_TONE(2, MSCL_C) }},
	{mscl_event_length, {.length = mscl_fp(1.0 / 1.0) }},
	{mscl_event_tone, {.tone = MSCL_TONE(3, MSCL_As) }},
};

// --------------------------------------------------------------------------------------------------------------------------------

inline static constexpr mscl::Song song
{
    "Demo-2",
    60.0,
    {c0}
};

// ================================================================================================================================
}
