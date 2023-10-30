/**
 * @file mscl_demo/songs/DemoFM.hpp
 */

#pragma once

#include <mscl.h>
#include <mscl_gui.hpp>
#include "instruments.hpp"

namespace songs::DemoFM
{
// ================================================================================================================================

inline static constexpr mscl_event c0[] = {
	{mscl_event_volume, {.volume = mscl_fp(0.20) }},
	{mscl_event_sustain, {.sustain = [](const mscl_fp pc){ return clerp(mscl_fp(1.0), mscl_fp(0.0), pc / 4); } }},
	{mscl_event_release, {.release = [](const mscl_fp pc){ return clerp(mscl_fp(1.0), mscl_fp(0.0), pc / 2); } }},
	{mscl_event_vibrato, {.vibrato = vib_none }},
	{mscl_event_waveform, {.waveform = wav_fm }},
    
	{mscl_event_length, {.length = mscl_fp(4.0 / 1.0) }},
	{mscl_event_tone, {.tone = MSCL_TONE(5, MSCL_C) }},
	{mscl_event_length, {.length = mscl_fp(2.0 / 1.0) }},
	{mscl_event_tone, {.tone = MSCL_TONE(5, MSCL_C+2) }},
	{mscl_event_length, {.length = mscl_fp(2.0 / 1.0) }},
	{mscl_event_tone, {.tone = MSCL_TONE(5, MSCL_C-2) }},
	{mscl_event_rest, {}},
};

// --------------------------------------------------------------------------------------------------------------------------------

inline static constexpr mscl::Song song
{
    "Demo-FM",
    60.0,
    {c0}
};

// ================================================================================================================================
}
