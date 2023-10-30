/**
 * @file mscl_demo/songs/Demo1.hpp
 */

#pragma once

#include <mscl.h>
#include <mscl_gui.hpp>
#include "instruments.hpp"

namespace songs::Demo1
{
// ================================================================================================================================

inline static constexpr mscl_event c0[] = {
	{mscl_event_volume, {.volume = mscl_fp(0.20) }},
	{mscl_event_sustain, {.sustain = env_hold }},
	{mscl_event_release, {.release = rel_fade }},
	{mscl_event_vibrato, {.vibrato = vib_some }},
	{mscl_event_waveform, {.waveform = wav_saw }},
	{mscl_event_length, {.length = mscl_fp(1.0 / 4.0) }},
	{mscl_event_tone, {.tone = MSCL_TONE(5, MSCL_C) }},
	{mscl_event_rest, {}},
	{mscl_event_length, {.length = mscl_fp(1.0 / 8.0) }},
	{mscl_event_tone, {.tone = MSCL_TONE(5, MSCL_E) }},
	{mscl_event_tone, {.tone = MSCL_TONE(5, MSCL_F) }},
	{mscl_event_tone, {.tone = MSCL_TONE(5, MSCL_G) }},
	{mscl_event_tone, {.tone = MSCL_TONE(5, MSCL_B) }},
	{mscl_event_length, {.length = mscl_fp(1.0 / 2.0) }},
	{mscl_event_tone, {.tone = MSCL_TONE(6, MSCL_C) }},
	{mscl_event_rest, {}},
};

// --------------------------------------------------------------------------------------------------------------------------------

inline static constexpr mscl::Song song
{
    "Demo-1",
    60.0,
    {c0}
};

// ================================================================================================================================
}
