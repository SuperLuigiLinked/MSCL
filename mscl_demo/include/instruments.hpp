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

template <typename T> inline static T clerp(const T a, const T b, const T t) noexcept
{
    return a + (b - a) * clampn(t);
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

template <typename T> inline static T sinus(const T pc, const T duty) noexcept
{
	const T npc = normf(pc);
	return (npc < duty) ? std::sin(T(MSCL_PI) * (npc / duty)) : std::sin(T(MSCL_PI) * ((npc - duty) / (duty - 1.0)));
}

// ================================================================================================================================

inline mscl_fp wav_sine(const mscl_fp s, const mscl_fp f)
{
	return nsine(s * f);
}

inline mscl_fp wav_square(const mscl_fp s, const mscl_fp f)
{
	//return (normf(mscl_fp(pc)) < mscl_fp(0.5) ? mscl_fp(0.5) : mscl_fp(-0.5));
	return clampf(mscl_fp(25.0) * nsine(s * f), mscl_fp(-0.5), mscl_fp(0.5));
}

inline mscl_fp wav_pulse_25(const mscl_fp s, const mscl_fp f)
{
	return mscl_fp(0.5) * pulse(s * f, mscl_fp(0.25));
}

inline mscl_fp wav_pulse_125(const mscl_fp s, const mscl_fp f)
{
	return mscl_fp(0.5) * pulse(s * f, mscl_fp(0.125));
}

inline mscl_fp wav_saw(const mscl_fp s, const mscl_fp f)
{
	return normf(s * f) - mscl_fp(0.5);
}

inline mscl_fp wav_tri(const mscl_fp s, const mscl_fp f)
{
	return std::fabs(normf(s * f) - mscl_fp(0.5)) * mscl_fp(2.0) - mscl_fp(0.5);
}

inline mscl_fp wav_fin(const mscl_fp s, const mscl_fp f)
{
	constexpr mscl_fp exp = mscl_fp(1.0 / 2.0);
	const mscl_fp xs = fmodf(s * f, mscl_fp(0.5));
	const mscl_fp xn = normf(s * f);
	const mscl_fp sine = std::pow(std::sin(mscl_fp(MSCL_PI) * xs), exp) - mscl_fp(0.5);
	const mscl_fp sign = (xn < mscl_fp(0.5) ? mscl_fp(1.0) : mscl_fp(-1.0));
	return sine * sign;
}

inline mscl_fp wav_noise(const mscl_fp s [[maybe_unused]], const mscl_fp f [[maybe_unused]])
{
	return mscl_fp(rand()) / mscl_fp(RAND_MAX) - mscl_fp(0.5);
}

inline mscl_fp wav_fm(const mscl_fp s, const mscl_fp f)
{
	const mscl_fp pc = s * f;
	return harmonic(pc, mscl_fp(1))
		+ harmonic(pc, mscl_fp(2))
		+ harmonic(pc, mscl_fp(3))
	;
}

// ================================================================================================================================

inline mscl_fp env_hold(const mscl_fp s [[maybe_unused]])
{
	return mscl_fp(1.0);
}

inline mscl_fp env_fade(const mscl_fp s)
{
	return clampn(mscl_fp(1.0) - mscl_fp(1.25) * s);
}

inline mscl_fp env_fade_slow(const mscl_fp s)
{
	return clampn(mscl_fp(1.0) - mscl_fp(0.50) * s);
}

inline mscl_fp env_fade_fast(const mscl_fp s)
{
	return clampn(mscl_fp(1.0) - mscl_fp(2.00) * s);
}

// ================================================================================================================================

inline mscl_fp rel_drop(const mscl_fp s [[maybe_unused]])
{
	return mscl_fp(0.0);
}

inline mscl_fp rel_fade(const mscl_fp s)
{
	return clampn(mscl_fp(1.0) - mscl_fp(2.0) * s);
}

// ================================================================================================================================

inline mscl_fp vibrato(const mscl_fp s, const mscl_fp delay, const mscl_fp speed, const mscl_fp depth)
{
	if (s < delay) return mscl_fp(0.0);
	const mscl_fp time = s - delay;
	const mscl_fp offs = mscl_fp(time) * mscl_fp(MSCL_TAU) * mscl_fp(speed);
	return std::sin(offs) * depth / mscl_fp(-24);
}

inline mscl_fp vib_none(const mscl_fp s [[maybe_unused]])
{
	return mscl_fp(0.0);
}

inline mscl_fp vib_some(const mscl_fp s)
{
	return vibrato(s, mscl_fp(0.5), mscl_fp(4.0), mscl_fp(1.0));
}

inline mscl_fp vib_medium(const mscl_fp s)
{
	return vibrato(s, mscl_fp(0.125), mscl_fp(6.0), mscl_fp(1.0));
}

// ================================================================================================================================
