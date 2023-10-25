/**
 * @file demo/songs.hpp
 */

#pragma once

#include <mscl.h>

#include <cmath>

#include <span>
#include <array>
#include <initializer_list>

// ================================================================================================================================

using Channel = std::span<const mscl_event>;
using Channels = std::initializer_list<const Channel>;
struct Song { mscl_time tempo; Channels channels; };

// ================================================================================================================================

inline auto idivf(const auto a, const auto b)
{
	return (a / b) - ((a % b) && ((a ^ b) < 0));
}

inline auto imodf(const auto a, const auto b)
{
	return (a % b) + b * ((a % b) && ((a ^ b) < 0));
}

inline auto fmodf(const auto a, const auto b)
{
	return a - b * std::floor(a / b);
}

inline auto normf(const auto x)
{
	return x - std::floor(x);
}

inline auto clampf(const auto x, const auto a, const auto b) -> decltype(x)
{
	if (x < a) return a;
	if (x > b) return b;
	return x;
}

inline auto clampn(const auto x) -> decltype(x)
{
	if (x < 0) return 0;
	if (x > 1) return 1;
	return x;
}

// ================================================================================================================================

inline mscl_sample wav_sine(const mscl_time pc)
{
	return std::sin(normf(pc) * mscl_time(MSCL_TAU));
}

inline mscl_sample wav_square(const mscl_time pc)
{
	return (normf(mscl_sample(pc)) < mscl_time(0.5) ? mscl_sample(0.5) : mscl_sample(-0.5));
}

inline mscl_sample wav_pulse_25(const mscl_time pc)
{
	return (normf(mscl_sample(pc)) < mscl_time(0.25) ? mscl_sample(0.5) : mscl_sample(-0.5));
}

inline mscl_sample wav_pulse_125(const mscl_time pc)
{
	return (normf(mscl_sample(pc)) < mscl_time(0.125) ? mscl_sample(0.5) : mscl_sample(-0.5));
}

inline mscl_sample wav_saw(const mscl_time pc)
{
	return normf(mscl_sample(pc)) - mscl_sample(0.5);
}

inline mscl_sample wav_tri(const mscl_time pc)
{
	return std::fabs(normf(mscl_sample(pc)) - mscl_sample(0.5)) * mscl_sample(2.0) - mscl_sample(0.5);
}

inline mscl_sample wav_noise(const mscl_time pc [[maybe_unused]])
{
	return mscl_sample(rand()) / mscl_sample(RAND_MAX) - mscl_sample(0.5);
}

// ================================================================================================================================

inline mscl_sample env_hold(const mscl_time secs [[maybe_unused]])
{
	return mscl_sample(1.0);
}

inline mscl_sample env_fade(const mscl_time secs)
{
	return clampn(mscl_sample(1.0) - mscl_sample(1.25) * mscl_sample(secs));
}

inline mscl_sample env_fade_2(const mscl_time secs)
{
	return clampn(mscl_sample(1.0) - mscl_sample(2.0) * mscl_sample(secs));
}

// ================================================================================================================================

inline mscl_sample rel_drop(const mscl_time secs [[maybe_unused]])
{
	return mscl_sample(0.0);
}

inline mscl_sample rel_fade(const mscl_time secs)
{
	return clampn(mscl_sample(1.0) - mscl_sample(2.0) * mscl_sample(secs));
}

// ================================================================================================================================

inline mscl_sample vibrato(const mscl_time secs, const mscl_time delay, const mscl_time speed, const mscl_sample depth)
{
	if (secs < delay) return mscl_sample(1.0);

	const mscl_sample offs = std::sin(mscl_sample(secs - delay) * mscl_sample(MSCL_TAU) * mscl_sample(speed)) * depth;
	return std::pow(mscl_sample(2), offs / mscl_sample(-288));
}

inline mscl_sample vib_none(const mscl_time secs [[maybe_unused]])
{
	return mscl_sample(1.0);
}

inline mscl_sample vib_some(const mscl_time secs)
{
	return vibrato(secs, mscl_time(0.5), mscl_time(4.0), mscl_sample(1.0));
}

inline mscl_sample vib_medium(const mscl_time secs)
{
	return vibrato(secs, mscl_time(0.125), mscl_time(6.0), mscl_sample(1.0));
}

// ================================================================================================================================

#define CONCAT_IMPL(name, var) name ## _ ## var
#define CONCAT(name, var) CONCAT_IMPL(name, var)

// ================================================================================================================================

#define SONG_NAME Demo1

inline static constexpr std::array CONCAT(SONG_NAME, c0) = {
	mscl_event{mscl_event_volume, {.volume = mscl_sample(0.20) }},
	mscl_event{mscl_event_sustain, {.sustain = env_hold }},
	mscl_event{mscl_event_release, {.release = rel_fade }},
	mscl_event{mscl_event_vibrato, {.vibrato = vib_some }},
	mscl_event{mscl_event_waveform, {.waveform = wav_saw }},
	mscl_event{mscl_event_length, {.length = mscl_time(1.0 / 4.0) }},
	mscl_event{mscl_event_tone, {.tone = MSCL_TONE(5, MSCL_C) }},
	mscl_event{mscl_event_tone, {.tone = MSCL_REST }},
	mscl_event{mscl_event_length, {.length = mscl_time(1.0 / 8.0) }},
	mscl_event{mscl_event_tone, {.tone = MSCL_TONE(5, MSCL_E) }},
	mscl_event{mscl_event_tone, {.tone = MSCL_TONE(5, MSCL_F) }},
	mscl_event{mscl_event_tone, {.tone = MSCL_TONE(5, MSCL_G) }},
	mscl_event{mscl_event_tone, {.tone = MSCL_TONE(5, MSCL_B) }},
	mscl_event{mscl_event_length, {.length = mscl_time(1.0 / 2.0) }},
	mscl_event{mscl_event_tone, {.tone = MSCL_TONE(6, MSCL_C) }},
	mscl_event{mscl_event_tone, {.tone = MSCL_REST }},
};

inline static constexpr Song CONCAT(song, SONG_NAME){ 60.0, {CONCAT(SONG_NAME, c0)} }; 

#undef SONG_NAME

// ================================================================================================================================

#define SONG_NAME Demo2

inline static constexpr std::array CONCAT(SONG_NAME, c0) = {
	mscl_event{mscl_event_volume, {.volume = 0.20f }},
	mscl_event{mscl_event_sustain, {.sustain = env_fade }},
	mscl_event{mscl_event_release, {.release = rel_drop }},
	mscl_event{mscl_event_vibrato, {.vibrato = vib_medium }},
	mscl_event{mscl_event_waveform, {.waveform = wav_square }},

	mscl_event{mscl_event_length, {.length = mscl_time(1.0 / 8.0) }},
	mscl_event{mscl_event_tone, {.tone = MSCL_TONE(3, MSCL_C) }},
	mscl_event{mscl_event_length, {.length = mscl_time(1.0 / 4.0) }},
	mscl_event{mscl_event_tone, {.tone = MSCL_TONE(2, MSCL_C) }},
	mscl_event{mscl_event_tone, {.tone = MSCL_TONE(2, MSCL_C) }},
	mscl_event{mscl_event_length, {.length = mscl_time(1.0 / 8.0) }},
	mscl_event{mscl_event_tone, {.tone = MSCL_TONE(2, MSCL_C) }},
	mscl_event{mscl_event_tone, {.tone = MSCL_TONE(3, MSCL_As) }},
	mscl_event{mscl_event_tone, {.tone = MSCL_TONE(4, MSCL_C) }},

	mscl_event{mscl_event_length, {.length = mscl_time(1.0 / 8.0) }},
	mscl_event{mscl_event_tone, {.tone = MSCL_TONE(3, MSCL_C) }},
	mscl_event{mscl_event_length, {.length = mscl_time(1.0 / 4.0) }},
	mscl_event{mscl_event_tone, {.tone = MSCL_TONE(2, MSCL_C) }},
	mscl_event{mscl_event_tone, {.tone = MSCL_TONE(2, MSCL_C) }},
	mscl_event{mscl_event_length, {.length = mscl_time(1.0 / 8.0) }},
	mscl_event{mscl_event_tone, {.tone = MSCL_TONE(2, MSCL_C) }},
	mscl_event{mscl_event_tone, {.tone = MSCL_TONE(3, MSCL_As) }},
	mscl_event{mscl_event_tone, {.tone = MSCL_TONE(4, MSCL_C) }},

	mscl_event{mscl_event_length, {.length = mscl_time(1.0 / 8.0) }},
	mscl_event{mscl_event_tone, {.tone = MSCL_TONE(3, MSCL_As) }},
	mscl_event{mscl_event_tone, {.tone = MSCL_TONE(3, MSCL_C) }},
	mscl_event{mscl_event_tone, {.tone = MSCL_TONE(2, MSCL_C) }},
	mscl_event{mscl_event_length, {.length = mscl_time(1.0 / 4.0) }},
	mscl_event{mscl_event_tone, {.tone = MSCL_TONE(2, MSCL_C) }},
	mscl_event{mscl_event_length, {.length = mscl_time(1.0 / 8.0) }},
	mscl_event{mscl_event_tone, {.tone = MSCL_TONE(2, MSCL_C) }},
	mscl_event{mscl_event_tone, {.tone = MSCL_TONE(3, MSCL_As) }},
	mscl_event{mscl_event_tone, {.tone = MSCL_TONE(4, MSCL_C) }},

	mscl_event{mscl_event_length, {.length = mscl_time(1.0 / 8.0) }},
	mscl_event{mscl_event_tone, {.tone = MSCL_TONE(3, MSCL_C) }},
	mscl_event{mscl_event_length, {.length = mscl_time(1.0 / 4.0) }},
	mscl_event{mscl_event_tone, {.tone = MSCL_TONE(2, MSCL_C) }},
	mscl_event{mscl_event_tone, {.tone = MSCL_TONE(2, MSCL_C) }},
	mscl_event{mscl_event_length, {.length = mscl_time(1.0 / 8.0) }},
	mscl_event{mscl_event_tone, {.tone = MSCL_TONE(2, MSCL_C) }},
	mscl_event{mscl_event_length, {.length = mscl_time(1.0 / 2.0) }},
	mscl_event{mscl_event_tone, {.tone = MSCL_TONE(3, MSCL_As) }},
};

inline static constexpr Song CONCAT(song, SONG_NAME){ 60.0, {CONCAT(SONG_NAME, c0)} }; 

#undef SONG_NAME

// ================================================================================================================================

#define SONG_NAME Menuet

inline static constexpr std::array CONCAT(SONG_NAME, c0) = {
	mscl_event{mscl_event_loop_begin, {.loop_begin = MSCL_LOOP_INFINITE }},

	mscl_event{mscl_event_volume, {.volume = mscl_sample(0.15) }},
	mscl_event{mscl_event_sustain, {.sustain = env_fade_2 }},
	mscl_event{mscl_event_release, {.release = rel_fade }},
	mscl_event{mscl_event_vibrato, {.vibrato = vib_some }},
	mscl_event{mscl_event_waveform, {.waveform = wav_pulse_25 }},

	mscl_event{mscl_event_length, {.length = mscl_time(1.0 / 2.0) }},

	// Section 1A

	mscl_event{mscl_event_loop_begin, {.loop_begin = 1 }},
	mscl_event{mscl_event_tone, {.tone = MSCL_TONE(4, MSCL_A) }},
	mscl_event{mscl_event_tone, {.tone = MSCL_TONE(5, MSCL_Cs) }},
	mscl_event{mscl_event_tone, {.tone = MSCL_TONE(5, MSCL_Fs) }},
	mscl_event{mscl_event_tone, {.tone = MSCL_TONE(5, MSCL_Cs) }},
	mscl_event{mscl_event_tone, {.tone = MSCL_TONE(4, MSCL_Gs) }},
	mscl_event{mscl_event_tone, {.tone = MSCL_TONE(5, MSCL_Cs) }},
	mscl_event{mscl_event_tone, {.tone = MSCL_TONE(4, MSCL_A) }},
	mscl_event{mscl_event_tone, {.tone = MSCL_TONE(5, MSCL_Cs) }},
	mscl_event{mscl_event_tone, {.tone = MSCL_TONE(4, MSCL_Fs) }},
	mscl_event{mscl_event_tone, {.tone = MSCL_TONE(5, MSCL_Cs) }},
	mscl_event{mscl_event_tone, {.tone = MSCL_TONE(4, MSCL_F) }},
	mscl_event{mscl_event_tone, {.tone = MSCL_TONE(5, MSCL_Cs) }},
	mscl_event{mscl_event_loop_end, {}},

	mscl_event{mscl_event_tone, {.tone = MSCL_TONE(4, MSCL_A) }},
	mscl_event{mscl_event_tone, {.tone = MSCL_TONE(5, MSCL_Cs) }},
	mscl_event{mscl_event_tone, {.tone = MSCL_TONE(4, MSCL_A) }},
	mscl_event{mscl_event_tone, {.tone = MSCL_TONE(4, MSCL_Fs) }},
	mscl_event{mscl_event_tone, {.tone = MSCL_TONE(5, MSCL_D) }},
	mscl_event{mscl_event_tone, {.tone = MSCL_TONE(4, MSCL_B) }},
	mscl_event{mscl_event_tone, {.tone = MSCL_TONE(4, MSCL_Gs) }},
	mscl_event{mscl_event_tone, {.tone = MSCL_TONE(4, MSCL_B) }},
	mscl_event{mscl_event_tone, {.tone = MSCL_TONE(4, MSCL_Gs) }},
	mscl_event{mscl_event_tone, {.tone = MSCL_TONE(4, MSCL_E) }},
	mscl_event{mscl_event_tone, {.tone = MSCL_TONE(5, MSCL_Cs) }},
	mscl_event{mscl_event_tone, {.tone = MSCL_TONE(4, MSCL_A) }},

	mscl_event{mscl_event_tone, {.tone = MSCL_TONE(4, MSCL_Fs) }},
	mscl_event{mscl_event_tone, {.tone = MSCL_TONE(5, MSCL_Cs) }},
	mscl_event{mscl_event_tone, {.tone = MSCL_TONE(4, MSCL_B) }},
	mscl_event{mscl_event_tone, {.tone = MSCL_TONE(4, MSCL_A) }},
	mscl_event{mscl_event_tone, {.tone = MSCL_TONE(4, MSCL_Gs) }},
	mscl_event{mscl_event_tone, {.tone = MSCL_TONE(4, MSCL_Fs) }},
	mscl_event{mscl_event_tone, {.tone = MSCL_TONE(4, MSCL_F) }},
	mscl_event{mscl_event_tone, {.tone = MSCL_TONE(4, MSCL_Cs) }},
	mscl_event{mscl_event_tone, {.tone = MSCL_TONE(4, MSCL_F) }},
	mscl_event{mscl_event_tone, {.tone = MSCL_TONE(4, MSCL_Gs) }},
	mscl_event{mscl_event_tone, {.tone = MSCL_TONE(5, MSCL_Cs) }},
	mscl_event{mscl_event_tone, {.tone = MSCL_TONE(4, MSCL_B) }},

	// Section 1B

	mscl_event{mscl_event_loop_begin, {.loop_begin = 1 }},
	mscl_event{mscl_event_tone, {.tone = MSCL_TONE(4, MSCL_A) }},
	mscl_event{mscl_event_tone, {.tone = MSCL_TONE(5, MSCL_Cs) }},
	mscl_event{mscl_event_tone, {.tone = MSCL_TONE(5, MSCL_Fs) }},
	mscl_event{mscl_event_tone, {.tone = MSCL_TONE(5, MSCL_Cs) }},
	mscl_event{mscl_event_tone, {.tone = MSCL_TONE(4, MSCL_Gs) }},
	mscl_event{mscl_event_tone, {.tone = MSCL_TONE(5, MSCL_Cs) }},
	mscl_event{mscl_event_tone, {.tone = MSCL_TONE(4, MSCL_A) }},
	mscl_event{mscl_event_tone, {.tone = MSCL_TONE(5, MSCL_Cs) }},
	mscl_event{mscl_event_tone, {.tone = MSCL_TONE(4, MSCL_Fs) }},
	mscl_event{mscl_event_tone, {.tone = MSCL_TONE(5, MSCL_Cs) }},
	mscl_event{mscl_event_tone, {.tone = MSCL_TONE(4, MSCL_F) }},
	mscl_event{mscl_event_tone, {.tone = MSCL_TONE(5, MSCL_Cs) }},
	mscl_event{mscl_event_loop_end, {}},

	mscl_event{mscl_event_tone, {.tone = MSCL_TONE(4, MSCL_A) }},
	mscl_event{mscl_event_tone, {.tone = MSCL_TONE(5, MSCL_Cs) }},
	mscl_event{mscl_event_tone, {.tone = MSCL_TONE(4, MSCL_A) }},
	mscl_event{mscl_event_tone, {.tone = MSCL_TONE(4, MSCL_Fs) }},
	mscl_event{mscl_event_tone, {.tone = MSCL_TONE(5, MSCL_D) }},
	mscl_event{mscl_event_tone, {.tone = MSCL_TONE(4, MSCL_B) }},
	mscl_event{mscl_event_tone, {.tone = MSCL_TONE(4, MSCL_Gs) }},
	mscl_event{mscl_event_tone, {.tone = MSCL_TONE(4, MSCL_B) }},
	mscl_event{mscl_event_tone, {.tone = MSCL_TONE(4, MSCL_Gs) }},
	mscl_event{mscl_event_tone, {.tone = MSCL_TONE(4, MSCL_E) }},
	mscl_event{mscl_event_tone, {.tone = MSCL_TONE(5, MSCL_E) }},
	mscl_event{mscl_event_tone, {.tone = MSCL_TONE(4, MSCL_B) }},

	mscl_event{mscl_event_tone, {.tone = MSCL_TONE(5, MSCL_Cs) }},
	mscl_event{mscl_event_tone, {.tone = MSCL_TONE(5, MSCL_E) }},
	mscl_event{mscl_event_tone, {.tone = MSCL_TONE(5, MSCL_Cs) }},
	mscl_event{mscl_event_tone, {.tone = MSCL_TONE(4, MSCL_A) }},
	mscl_event{mscl_event_tone, {.tone = MSCL_TONE(4, MSCL_E) }},
	mscl_event{mscl_event_tone, {.tone = MSCL_TONE(4, MSCL_Gs) }},
	mscl_event{mscl_event_length, {.length = mscl_time(1.0 / 1.0) }},
	mscl_event{mscl_event_tone, {.tone = MSCL_TONE(4, MSCL_A) }},
	mscl_event{mscl_event_tone, {.tone = MSCL_REST }},
	mscl_event{mscl_event_tone, {.tone = MSCL_REST }},

	// End
	mscl_event{mscl_event_loop_end, {}},
};

inline static constexpr std::array CONCAT(SONG_NAME, c1) = {
	mscl_event{mscl_event_loop_begin, {.loop_begin = MSCL_LOOP_INFINITE }},

	mscl_event{mscl_event_volume, {.volume = mscl_sample(0.15) }},
	mscl_event{mscl_event_sustain, {.sustain = env_fade_2 }},
	mscl_event{mscl_event_release, {.release = rel_fade }},
	mscl_event{mscl_event_vibrato, {.vibrato = vib_some }},
	mscl_event{mscl_event_waveform, {.waveform = wav_pulse_25 }},

	// Section 1A

	mscl_event{mscl_event_length, {.length = mscl_time(1.0 / 1.0) }},
	mscl_event{mscl_event_tone, {.tone = MSCL_TONE(3, MSCL_Fs) }},
	mscl_event{mscl_event_tone, {.tone = MSCL_TONE(4, MSCL_Fs) }},
	mscl_event{mscl_event_tone, {.tone = MSCL_TONE(4, MSCL_F) }},
	mscl_event{mscl_event_tone, {.tone = MSCL_TONE(3, MSCL_Fs) }},
	mscl_event{mscl_event_tone, {.tone = MSCL_TONE(3, MSCL_A) }},
	mscl_event{mscl_event_tone, {.tone = MSCL_TONE(4, MSCL_Cs) }},

	mscl_event{mscl_event_length, {.length = mscl_time(1.0 / 1.0) }},
	mscl_event{mscl_event_tone, {.tone = MSCL_TONE(4, MSCL_Fs) }},
	mscl_event{mscl_event_tone, {.tone = MSCL_TONE(4, MSCL_D) }},
	mscl_event{mscl_event_tone, {.tone = MSCL_TONE(4, MSCL_Cs) }},
	mscl_event{mscl_event_tone, {.tone = MSCL_TONE(4, MSCL_Fs) }},
	mscl_event{mscl_event_tone, {.tone = MSCL_TONE(3, MSCL_A) }},
	mscl_event{mscl_event_tone, {.tone = MSCL_TONE(4, MSCL_Cs) }},

	mscl_event{mscl_event_length, {.length = mscl_time(1.0 / 1.0) }},
	mscl_event{mscl_event_tone, {.tone = MSCL_TONE(3, MSCL_Fs) }},
	mscl_event{mscl_event_tone, {.tone = MSCL_TONE(4, MSCL_Fs) }},
	mscl_event{mscl_event_tone, {.tone = MSCL_TONE(3, MSCL_B) }},
	mscl_event{mscl_event_tone, {.tone = MSCL_TONE(3, MSCL_E) }},
	mscl_event{mscl_event_tone, {.tone = MSCL_TONE(4, MSCL_E) }},
	mscl_event{mscl_event_tone, {.tone = MSCL_TONE(3, MSCL_A) }},

	mscl_event{mscl_event_length, {.length = mscl_time(1.0 / 1.0) }},
	mscl_event{mscl_event_tone, {.tone = MSCL_TONE(3, MSCL_D) }},
	mscl_event{mscl_event_tone, {.tone = MSCL_TONE(4, MSCL_D) }},
	mscl_event{mscl_event_tone, {.tone = MSCL_TONE(3, MSCL_B) }},
	mscl_event{mscl_event_length, {.length = mscl_time(1.0 / 2.0) }},
	mscl_event{mscl_event_tone, {.tone = MSCL_TONE(4, MSCL_Cs) }},
	mscl_event{mscl_event_tone, {.tone = MSCL_TONE(4, MSCL_D) }},
	mscl_event{mscl_event_tone, {.tone = MSCL_TONE(4, MSCL_Cs) }},
	mscl_event{mscl_event_tone, {.tone = MSCL_TONE(3, MSCL_B) }},
	mscl_event{mscl_event_tone, {.tone = MSCL_TONE(3, MSCL_A) }},
	mscl_event{mscl_event_tone, {.tone = MSCL_TONE(3, MSCL_Gs) }},

	// Section 1B

	mscl_event{mscl_event_length, {.length = mscl_time(1.0 / 1.0) }},
	mscl_event{mscl_event_tone, {.tone = MSCL_TONE(3, MSCL_Fs) }},
	mscl_event{mscl_event_tone, {.tone = MSCL_TONE(4, MSCL_Fs) }},
	mscl_event{mscl_event_tone, {.tone = MSCL_TONE(4, MSCL_F) }},
	mscl_event{mscl_event_tone, {.tone = MSCL_TONE(3, MSCL_Fs) }},
	mscl_event{mscl_event_tone, {.tone = MSCL_TONE(3, MSCL_A) }},
	mscl_event{mscl_event_tone, {.tone = MSCL_TONE(4, MSCL_Cs) }},

	mscl_event{mscl_event_length, {.length = mscl_time(1.0 / 1.0) }},
	mscl_event{mscl_event_tone, {.tone = MSCL_TONE(4, MSCL_Fs) }},
	mscl_event{mscl_event_tone, {.tone = MSCL_TONE(4, MSCL_D) }},
	mscl_event{mscl_event_tone, {.tone = MSCL_TONE(4, MSCL_Cs) }},
	mscl_event{mscl_event_tone, {.tone = MSCL_TONE(4, MSCL_Fs) }},
	mscl_event{mscl_event_tone, {.tone = MSCL_TONE(3, MSCL_A) }},
	mscl_event{mscl_event_tone, {.tone = MSCL_TONE(4, MSCL_Cs) }},

	mscl_event{mscl_event_length, {.length = mscl_time(1.0 / 1.0) }},
	mscl_event{mscl_event_tone, {.tone = MSCL_TONE(3, MSCL_Fs) }},
	mscl_event{mscl_event_tone, {.tone = MSCL_TONE(4, MSCL_Fs) }},
	mscl_event{mscl_event_tone, {.tone = MSCL_TONE(3, MSCL_B) }},
	mscl_event{mscl_event_tone, {.tone = MSCL_TONE(3, MSCL_E) }},
	mscl_event{mscl_event_tone, {.tone = MSCL_TONE(4, MSCL_E) }},
	mscl_event{mscl_event_tone, {.tone = MSCL_TONE(3, MSCL_Gs) }},

	mscl_event{mscl_event_length, {.length = mscl_time(1.0 / 1.0) }},
	mscl_event{mscl_event_tone, {.tone = MSCL_TONE(3, MSCL_A) }},
	mscl_event{mscl_event_tone, {.tone = MSCL_TONE(4, MSCL_Cs) }},
	mscl_event{mscl_event_tone, {.tone = MSCL_TONE(4, MSCL_Cs) }},
	mscl_event{mscl_event_tone, {.tone = MSCL_TONE(3, MSCL_A) }},
	mscl_event{mscl_event_tone, {.tone = MSCL_TONE(3, MSCL_E) }},
	mscl_event{mscl_event_tone, {.tone = MSCL_TONE(2, MSCL_A) }},
	
	// End
	mscl_event{mscl_event_loop_end, {}},
};

inline static constexpr Song CONCAT(song, SONG_NAME){ 148.0, {CONCAT(SONG_NAME, c0), CONCAT(SONG_NAME, c1)} }; 

#undef SONG_NAME

// ================================================================================================================================
