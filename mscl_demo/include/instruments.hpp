/**
 * @file mscl_demo/instruments.hpp
 */

#pragma once

#include <mscl.h>

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
	//return (normf(mscl_sample(pc)) < mscl_time(0.5) ? mscl_sample(0.5) : mscl_sample(-0.5));
	return clampf(mscl_sample(25.0) * std::sin(normf(pc) * mscl_time(MSCL_TAU)), mscl_sample(-0.5), mscl_sample(0.5));
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

inline mscl_sample wav_fin(const mscl_time pc)
{
	constexpr mscl_sample exp = mscl_sample(1.0 / 2.0);
	const mscl_sample xs = fmodf(mscl_sample(pc), mscl_sample(0.5));
	const mscl_sample xn = normf(mscl_sample(pc));
	const mscl_sample sine = std::pow(std::sin(mscl_sample(MSCL_PI) * xs), exp) - mscl_sample(0.5);
	const mscl_sample sign = (xn < mscl_sample(0.5) ? mscl_sample(1.0) : mscl_sample(-1.0));
	return sine * sign;
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

inline mscl_sample env_fade_slow(const mscl_time secs)
{
	return clampn(mscl_sample(1.0) - mscl_sample(0.50) * mscl_sample(secs));
}

inline mscl_sample env_fade_fast(const mscl_time secs)
{
	return clampn(mscl_sample(1.0) - mscl_sample(2.00) * mscl_sample(secs));
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
	if (secs < delay) return mscl_sample(0.0);
	const mscl_time time = secs - delay;
	const mscl_sample offs = mscl_sample(time) * mscl_sample(MSCL_TAU) * mscl_sample(speed);
	return std::sin(offs) * depth / mscl_sample(-24);
}

inline mscl_sample vib_none(const mscl_time secs [[maybe_unused]])
{
	return mscl_sample(0.0);
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
