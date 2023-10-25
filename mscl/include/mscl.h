/**
 * @file mscl.h
 *
 * @brief MuSiCaL: a Music Synthesis Coding Language
 * 
 * MSCL (aka MuSiCaL) is a library that allows you to synthesize music using basic commands written in code.
 */

#pragma once

#ifndef MSCL_H
#define MSCL_H

typedef float mscl_sample;
typedef float mscl_time;

#define MSCL_PI 3.14159265358979323846
#define MSCL_TAU 6.28318530717958647692

#ifdef __cplusplus
#	define mscl_pow(base, exp) pow(base, exp)
#else
#	define mscl_pow(base, exp) _Generic((base + exp), float: powf(base, exp), double: pow(base, exp), long double: powl(base, exp), default: pow(base, exp))
#endif

enum mscl_note
{
	MSCL_C = 3,
	MSCL_Cf = MSCL_C - 1,
	MSCL_Cs = MSCL_C + 1,

	MSCL_D = 5,
	MSCL_Df = MSCL_D - 1,
	MSCL_Ds = MSCL_D + 1,

	MSCL_E = 7,
	MSCL_Ef = MSCL_E - 1,
	MSCL_Es = MSCL_E + 1,

	MSCL_F = 8,
	MSCL_Ff = MSCL_F - 1,
	MSCL_Fs = MSCL_F + 1,

	MSCL_G = 10,
	MSCL_Gf = MSCL_G - 1,
	MSCL_Gs = MSCL_G + 1,

	MSCL_A = 12,
	MSCL_Af = MSCL_A - 1,
	MSCL_As = MSCL_A + 1,

	MSCL_B = 14,
	MSCL_Bf = MSCL_B - 1,
	MSCL_Bs = MSCL_B + 1,
};
typedef enum mscl_note mscl_note;

#define MSCL_TONE(octave, note) ((mscl_sample)(octave) + ((mscl_sample)(note) / (mscl_sample)(12)))
#define MSCL_FREQ(tone) ((mscl_sample)(13.75) * (mscl_sample)(mscl_pow((mscl_sample)(2), (mscl_sample)(tone))))
#define MSCL_REST ((mscl_sample)0)

typedef mscl_sample (mscl_envelope)(mscl_time seconds);

enum mscl_event_type
{
	mscl_event_tone,
	mscl_event_length,
	mscl_event_volume,
	mscl_event_waveform,
	mscl_event_sustain,
	mscl_event_release,
	mscl_event_vibrato,
};
typedef enum mscl_event_type mscl_event_type;

union mscl_event_data
{
	mscl_sample tone;
	mscl_time length;
	mscl_sample volume;
	mscl_envelope* waveform;
	mscl_envelope* sustain;
	mscl_envelope* release;
	mscl_envelope* vibrato;
};
typedef union mscl_event_data mscl_event_data;

struct mscl_event
{
	mscl_event_type type;
	mscl_event_data data;
};
typedef struct mscl_event mscl_event;

struct mscl_engine
{
	size_t sample_idx;
	size_t event_idx;
	size_t loop_idx;
	
	mscl_envelope* waveform;
	mscl_envelope* sustain;
	mscl_envelope* release;
	mscl_envelope* vibrato;

	mscl_sample volume;
	mscl_sample frequency;
	
	mscl_time length;
	mscl_time next_event;
	mscl_time event_s;
	mscl_time event_r;
};
typedef struct mscl_engine mscl_engine;

extern
#ifdef __cplusplus
"C"
#endif
mscl_time mscl_estimate(size_t num_events, const mscl_event* events);

extern
#ifdef __cplusplus
"C"
#endif
mscl_sample mscl_advance(mscl_engine* engine, mscl_time sps, mscl_time speed, size_t num_events, const mscl_event* events);

#endif
