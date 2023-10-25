/**
 * @file demo/songs.hpp
 */

#pragma once

#include <mscl.h>

#include <array>
#include <cmath>

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
	return a - b * floorf(a / b);
}

inline auto normf(const auto x)
{
	return x - floorf(x);
}

inline auto clampf(const auto x, const auto a, const auto b)
{
	if (x < a) return a;
	if (x > b) return b;
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
	return clampf(mscl_sample(1.0) - mscl_sample(1.25) * mscl_sample(secs), mscl_sample(0.0), mscl_sample(1.0));
}

// ================================================================================================================================

inline mscl_sample rel_drop(const mscl_time secs [[maybe_unused]])
{
	return mscl_sample(0.0);
}

inline mscl_sample rel_fade(const mscl_time secs)
{
	return clampf(mscl_sample(1.0) - mscl_sample(2.0) * mscl_sample(secs), mscl_sample(0.0), mscl_sample(1.0));
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

#define SONG_NAME demo1

inline static constexpr std::array CONCAT(SONG_NAME, c0) = {
	mscl_event{mscl_event_volume, {.volume = mscl_sample(0.20) }},
	mscl_event{mscl_event_sustain, {.sustain = env_hold }},
	mscl_event{mscl_event_release, {.release = rel_fade }},
	mscl_event{mscl_event_vibrato, {.vibrato = vib_some }},
	mscl_event{mscl_event_waveform, {.waveform = wav_saw }},
	mscl_event{mscl_event_length, {.length = mscl_time(1.0 / 4.0) }},
	mscl_event{mscl_event_tone, {.tone = MSCL_TONE(MSCL_C, 4) }},
	mscl_event{mscl_event_tone, {.tone = MSCL_REST }},
	mscl_event{mscl_event_length, {.length = mscl_time(1.0 / 8.0) }},
	mscl_event{mscl_event_tone, {.tone = MSCL_TONE(MSCL_E, 4) }},
	mscl_event{mscl_event_tone, {.tone = MSCL_TONE(MSCL_F, 4) }},
	mscl_event{mscl_event_tone, {.tone = MSCL_TONE(MSCL_G, 4) }},
	mscl_event{mscl_event_tone, {.tone = MSCL_TONE(MSCL_B, 5) }},
	mscl_event{mscl_event_length, {.length = mscl_time(1.0 / 2.0) }},
	mscl_event{mscl_event_tone, {.tone = MSCL_TONE(MSCL_C, 5) }},
	mscl_event{mscl_event_tone, {.tone = MSCL_REST }},
};

#undef SONG_NAME

// ================================================================================================================================

#undef SONG_NAME
#define SONG_NAME demo2

inline static constexpr std::array CONCAT(SONG_NAME, c0) = {
	mscl_event{mscl_event_volume, {.volume = 0.20f }},
	mscl_event{mscl_event_sustain, {.sustain = env_fade }},
	mscl_event{mscl_event_release, {.release = rel_drop }},
	mscl_event{mscl_event_vibrato, {.vibrato = vib_medium }},
	mscl_event{mscl_event_waveform, {.waveform = wav_square }},

	mscl_event{mscl_event_length, {.length = mscl_time(1.0 / 8.0) }},
	mscl_event{mscl_event_tone, {.tone = MSCL_TONE(MSCL_C, 2) }},
	mscl_event{mscl_event_length, {.length = mscl_time(1.0 / 4.0) }},
	mscl_event{mscl_event_tone, {.tone = MSCL_TONE(MSCL_C, 1) }},
	mscl_event{mscl_event_tone, {.tone = MSCL_TONE(MSCL_C, 1) }},
	mscl_event{mscl_event_length, {.length = mscl_time(1.0 / 8.0) }},
	mscl_event{mscl_event_tone, {.tone = MSCL_TONE(MSCL_C, 1) }},
	mscl_event{mscl_event_tone, {.tone = MSCL_TONE(MSCL_B - 1, 3) }},
	mscl_event{mscl_event_tone, {.tone = MSCL_TONE(MSCL_C, 3) }},

	mscl_event{mscl_event_length, {.length = mscl_time(1.0 / 8.0) }},
	mscl_event{mscl_event_tone, {.tone = MSCL_TONE(MSCL_C, 2) }},
	mscl_event{mscl_event_length, {.length = mscl_time(1.0 / 4.0) }},
	mscl_event{mscl_event_tone, {.tone = MSCL_TONE(MSCL_C, 1) }},
	mscl_event{mscl_event_tone, {.tone = MSCL_TONE(MSCL_C, 1) }},
	mscl_event{mscl_event_length, {.length = mscl_time(1.0 / 8.0) }},
	mscl_event{mscl_event_tone, {.tone = MSCL_TONE(MSCL_C, 1) }},
	mscl_event{mscl_event_tone, {.tone = MSCL_TONE(MSCL_B - 1, 3) }},
	mscl_event{mscl_event_tone, {.tone = MSCL_TONE(MSCL_C, 3) }},

	mscl_event{mscl_event_length, {.length = mscl_time(1.0 / 8.0) }},
	mscl_event{mscl_event_tone, {.tone = MSCL_TONE(MSCL_B - 1, 3) }},
	mscl_event{mscl_event_tone, {.tone = MSCL_TONE(MSCL_C, 2) }},
	mscl_event{mscl_event_tone, {.tone = MSCL_TONE(MSCL_C, 1) }},
	mscl_event{mscl_event_length, {.length = mscl_time(1.0 / 4.0) }},
	mscl_event{mscl_event_tone, {.tone = MSCL_TONE(MSCL_C, 1) }},
	mscl_event{mscl_event_length, {.length = mscl_time(1.0 / 8.0) }},
	mscl_event{mscl_event_tone, {.tone = MSCL_TONE(MSCL_C, 1) }},
	mscl_event{mscl_event_tone, {.tone = MSCL_TONE(MSCL_B - 1, 3) }},
	mscl_event{mscl_event_tone, {.tone = MSCL_TONE(MSCL_C, 3) }},

	mscl_event{mscl_event_length, {.length = mscl_time(1.0 / 8.0) }},
	mscl_event{mscl_event_tone, {.tone = MSCL_TONE(MSCL_C, 2) }},
	mscl_event{mscl_event_length, {.length = mscl_time(1.0 / 4.0) }},
	mscl_event{mscl_event_tone, {.tone = MSCL_TONE(MSCL_C, 1) }},
	mscl_event{mscl_event_tone, {.tone = MSCL_TONE(MSCL_C, 1) }},
	mscl_event{mscl_event_length, {.length = mscl_time(1.0 / 8.0) }},
	mscl_event{mscl_event_tone, {.tone = MSCL_TONE(MSCL_C, 1) }},
	mscl_event{mscl_event_length, {.length = mscl_time(1.0 / 2.0) }},
	mscl_event{mscl_event_tone, {.tone = MSCL_TONE(MSCL_B - 1, 3) }},
};

#undef SONG_NAME

// ================================================================================================================================
