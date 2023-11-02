/**
 * @file mscl_demo/songs/HappySynth.hpp
 */

#pragma once

#include <mscl.h>
#include <mscl_gui.hpp>
#include "instruments.hpp"

namespace songs::HappySynth
{
// ================================================================================================================================

inline static constexpr mscl_event c0[] = {
	{mscl_event_volume, {.volume = mscl_fp(0.05) }},
	{mscl_event_sustain, {.sustain = env_fade }},
	{mscl_event_release, {.release = rel_fade }},
	{mscl_event_vibrato, {.vibrato = vib_medium }},
	{mscl_event_waveform, {.waveform = wav_square }},
	
	{mscl_event_length, {.length = mscl_fp(1.0 / 3.0) }},
	{mscl_event_tone, {.tone = MSCL_TONE(3, MSCL_F) }},
	{mscl_event_tone, {.tone = MSCL_TONE(4, MSCL_F) }},
	{mscl_event_tone, {.tone = MSCL_TONE(3, MSCL_F) }},
	{mscl_event_tone, {.tone = MSCL_TONE(6, MSCL_C) }},
	{mscl_event_tone, {.tone = MSCL_TONE(5, MSCL_C) }},
	{mscl_event_tone, {.tone = MSCL_TONE(4, MSCL_F) }},
	{mscl_event_tone, {.tone = MSCL_TONE(5, MSCL_F) }},
	{mscl_event_rest, {}},
	{mscl_event_rest, {}},
	{mscl_event_rest, {}},
	{mscl_event_rest, {}},
};

// --------------------------------------------------------------------------------------------------------------------------------

inline static constexpr mscl::Song song
{
    "Happy Synthesizer",
    127.0,
    {c0}
};

// ================================================================================================================================
}
