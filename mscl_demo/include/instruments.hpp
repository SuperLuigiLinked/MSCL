/**
 * @file mscl_demo/instruments.hpp
 */

#pragma once

#include <mscl.h>

#include <cmath>

// ================================================================================================================================

template <typename T> inline static auto idivf(const T a, const T b) noexcept
{
	return (a / b) - ((a % b) && ((a ^ b) < 0));
}

template <typename T> inline static T imodf(const T a, const T b) noexcept
{
	return (a % b) + b * ((a % b) && ((a ^ b) < 0));
}

template <typename T> inline static T fmodf(const T a, const T b) noexcept
{
	return a - b * std::floor(a / b);
}

template <typename T> inline static T normf(const T x) noexcept
{
	return x - std::floor(x);
}

template <typename T> inline static T clampf(const T x, const T a, const T b) noexcept
{
	if (x < a) return a;
	if (x > b) return b;
	return x;
}

template <typename T> inline static T clampn(const T x) noexcept
{
	if (x < T(0)) return T(0);
	if (x > T(1)) return T(1);
	return x;
}

template <typename T> inline static T pulse(const T pc, const T duty) noexcept
{
	return (normf(pc) < duty) ? 1.0 : -1.0;
}

template <typename T> inline static T nsine(const T pc) noexcept
{
	return std::sin(T(MSCL_TAU) * normf(pc));
}

template <typename T> inline static T harmonic(const T pc, const T h) noexcept
{
	return std::sin(T(MSCL_TAU) * normf(pc) * h) / h;
}

// ================================================================================================================================

inline mscl_sample wav_sine(const mscl_time s, const mscl_sample f)
{
	return nsine(mscl_sample(s) * f);
}

inline mscl_sample wav_square(const mscl_time s, const mscl_sample f)
{
	//return (normf(mscl_sample(pc)) < mscl_time(0.5) ? mscl_sample(0.5) : mscl_sample(-0.5));
	return clampf(mscl_sample(25.0) * nsine(mscl_sample(s) * f), mscl_sample(-0.5), mscl_sample(0.5));
}

inline mscl_sample wav_pulse_25(const mscl_time s, const mscl_sample f)
{
	return mscl_sample(0.5) * pulse(mscl_sample(s) * f, mscl_sample(0.25));
}

inline mscl_sample wav_pulse_125(const mscl_time s, const mscl_sample f)
{
	return mscl_sample(0.5) * pulse(mscl_sample(s) * f, mscl_sample(0.125));
}

inline mscl_sample wav_saw(const mscl_time s, const mscl_sample f)
{
	return normf(mscl_sample(s) * f) - mscl_sample(0.5);
}

inline mscl_sample wav_tri(const mscl_time s, const mscl_sample f)
{
	return std::fabs(normf(mscl_sample(s) * f) - mscl_sample(0.5)) * mscl_sample(2.0) - mscl_sample(0.5);
}

inline mscl_sample wav_fin(const mscl_time s, const mscl_sample f)
{
	constexpr mscl_sample exp = mscl_sample(1.0 / 2.0);
	const mscl_sample xs = fmodf(mscl_sample(s) * f, mscl_sample(0.5));
	const mscl_sample xn = normf(mscl_sample(s) * f);
	const mscl_sample sine = std::pow(std::sin(mscl_sample(MSCL_PI) * xs), exp) - mscl_sample(0.5);
	const mscl_sample sign = (xn < mscl_sample(0.5) ? mscl_sample(1.0) : mscl_sample(-1.0));
	return sine * sign;
}

inline mscl_sample wav_noise(const mscl_time s [[maybe_unused]], const mscl_sample f [[maybe_unused]])
{
	return mscl_sample(rand()) / mscl_sample(RAND_MAX) - mscl_sample(0.5);
}

// ================================================================================================================================

inline mscl_sample env_hold(const mscl_time s [[maybe_unused]])
{
	return mscl_sample(1.0);
}

inline mscl_sample env_fade(const mscl_time s)
{
	return clampn(mscl_sample(1.0) - mscl_sample(1.25) * mscl_sample(s));
}

inline mscl_sample env_fade_slow(const mscl_time s)
{
	return clampn(mscl_sample(1.0) - mscl_sample(0.50) * mscl_sample(s));
}

inline mscl_sample env_fade_fast(const mscl_time s)
{
	return clampn(mscl_sample(1.0) - mscl_sample(2.00) * mscl_sample(s));
}

// ================================================================================================================================

inline mscl_sample rel_drop(const mscl_time s [[maybe_unused]])
{
	return mscl_sample(0.0);
}

inline mscl_sample rel_fade(const mscl_time s)
{
	return clampn(mscl_sample(1.0) - mscl_sample(2.0) * mscl_sample(s));
}

// ================================================================================================================================

inline mscl_sample vibrato(const mscl_time s, const mscl_time delay, const mscl_time speed, const mscl_sample depth)
{
	if (s < delay) return mscl_sample(0.0);
	const mscl_time time = s - delay;
	const mscl_sample offs = mscl_sample(time) * mscl_sample(MSCL_TAU) * mscl_sample(speed);
	return std::sin(offs) * depth / mscl_sample(-24);
}

inline mscl_sample vib_none(const mscl_time s [[maybe_unused]])
{
	return mscl_sample(0.0);
}

inline mscl_sample vib_some(const mscl_time s)
{
	return vibrato(s, mscl_time(0.5), mscl_time(4.0), mscl_sample(1.0));
}

inline mscl_sample vib_medium(const mscl_time s)
{
	return vibrato(s, mscl_time(0.125), mscl_time(6.0), mscl_sample(1.0));
}

// ================================================================================================================================
