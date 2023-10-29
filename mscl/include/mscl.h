/**
 * @file mscl/mscl.h
 *
 * @brief MuSiCaL: a Music Synthesis Coding Language
 * 
 * MSCL (aka MuSiCaL) is a library that allows you to synthesize music using basic commands written in code.
 * 
 * A song is specified as an array of `mscl_event`.
 * Users start by initializing a `mscl_engine`.
 * The Engine, Events, and other Data must then be passed to the `mscl_advance` function in order to generate Samples.
 * Generated Samples may then be modified and passed to an external Audio API for playback. 
 */

#pragma once

#ifndef MSCL_H
#define MSCL_H

#ifdef __cplusplus
#	include <cstddef>
#	include <cmath>
#else
#	include <stddef.h>
#	include <math.h>
#endif

/**
 * @brief Data type used for calculating samples.
 */
typedef float mscl_fp;

/**
 * @brief Function that samples a waveform at a given time and frequency.
 */
typedef mscl_fp (mscl_waveform)(mscl_fp seconds, mscl_fp frequency);

/**
 * @brief Function that returns a modifier at a given time.
 */
typedef mscl_fp (mscl_envelope)(mscl_fp seconds);

/**
 * @brief Convenience PI constant.
 */
#define MSCL_PI 3.14159265358979323846

/**
 * @brief Convenience TAU constant.
 */
#define MSCL_TAU 6.28318530717958647692

/**
 * @brief A type-generic POW function.
 */
#ifdef __cplusplus
#	define MSCL_POW(base, exp) std::pow(base, exp)
#else
#	define MSCL_POW(base, exp) _Generic((base + exp), float: powf(base, exp), double: pow(base, exp), long double: powl(base, exp), default: pow(base, exp))
#endif

/**
 * @brief Maximum number of nested loops a MSCL Engine can process.
 * @warning While the nesting limit is exceeded, any additional loops are ignored.
 */
#define MSCL_MAX_LOOPS 4

/**
 * @brief Indicator that a section should loop indefinitely.
 */
#define MSCL_LOOP_INFINITE ((size_t)-1)

/**
 * @brief Calculates the Tone representing an (Octave, Note) pair.
 * @note A value of `MSCL_TONE(4, MSCL_C)` represents Middle C.
 */
#define MSCL_TONE(octave, note) ((mscl_fp)(octave) + ((mscl_fp)(note) / (mscl_fp)(12)))

/**
 * @brief Calculates the Frequency for a given Tone.
 * @note This function is tuned such that an input of `MSCL_TONE(4, MSCL_A)` returns 440 Hz.
 */
#define MSCL_FREQ(tone) ((mscl_fp)(13.75) * (mscl_fp)(MSCL_POW((mscl_fp)(2), (mscl_fp)(tone))))

/**
 * @brief Constants for different Notes in an Octave.
 * @note The values are specified in Semitones from the A Note of the lower octave.
 */
enum mscl_note
{
	MSCL_C =  3,  MSCL_Cf = MSCL_C - 1,  MSCL_Cs = MSCL_C + 1,
	MSCL_D =  5,  MSCL_Df = MSCL_D - 1,  MSCL_Ds = MSCL_D + 1,
	MSCL_E =  7,  MSCL_Ef = MSCL_E - 1,  MSCL_Es = MSCL_E + 1,
	MSCL_F =  8,  MSCL_Ff = MSCL_F - 1,  MSCL_Fs = MSCL_F + 1,
	MSCL_G = 10,  MSCL_Gf = MSCL_G - 1,  MSCL_Gs = MSCL_G + 1,
	MSCL_A = 12,  MSCL_Af = MSCL_A - 1,  MSCL_As = MSCL_A + 1,
	MSCL_B = 14,  MSCL_Bf = MSCL_B - 1,  MSCL_Bs = MSCL_B + 1,
};
typedef enum mscl_note mscl_note;

/**
 * @brief Tag for MSCL Events.
 */
enum mscl_event_type
{
	mscl_event_rest,       ///< Continues without playing any notes.
	mscl_event_tone,       ///< Starts a note of the given tone.
	mscl_event_length,     ///< Specifies the length of time to sustain upcoming notes.
	mscl_event_volume,     ///< Specifies the volume of upcoming notes.
	mscl_event_loop_begin, ///< Indicates the beginning of a loop.
	mscl_event_loop_end,   ///< Indicates the end of a loop.
	mscl_event_waveform,   ///< Envelope describing a Waveform.
	mscl_event_sustain,    ///< Envelope describing Sustain volume, relative the currently set volume. 
	mscl_event_release,    ///< Envelope describing Release volume, relative to the sustain volume at the end of the last played note.
	mscl_event_vibrato,    ///< Envelope describing Vibrato. 
};
typedef enum mscl_event_type mscl_event_type;

/**
 * @brief Data for MSCL Events.
 */
union mscl_event_data
{
	mscl_fp tone;            ///< A note tone, as returned by `MSCL_TONE`.
	mscl_fp length;          ///< A note length, in Beats.
	mscl_fp volume;          ///< A note volume, preferably in the range [0.0, 1.0].
	size_t loop_begin;       ///< Count of times to repeat the loop. A value of `MSCL_LOOP_INFINITE` causes the loop to repeat indefinitely.
	mscl_waveform* waveform; ///< Pointer to function that returns Sample values, preferably in the range [-1.0, +1.0].
	mscl_envelope* sustain;  ///< Pointer to function that returns Volume values, preferably in the range [0.0, 1.0].
	mscl_envelope* release;  ///< Pointer to function that returns Volume values, preferably in the range [0.0, 1.0].
	mscl_envelope* vibrato;  ///< Pointer to function that returns the amount of Semitones to adjust the frequency by.
};
typedef union mscl_event_data mscl_event_data;

/**
 * @brief Tagged union representing MSCL Events.
 */
struct mscl_event
{
	mscl_event_type type; ///< The event type tag.
	mscl_event_data data; ///< The event data associated with the tag.
};
typedef struct mscl_event mscl_event;

/**
 * @brief Engine for synthesizing music, containing all state used internally.
 * @note All members should be initialized to 0 before beginning to generate samples from a new list of events. 
 */
struct mscl_engine
{
	size_t sample_idx; ///< Current sample index.
	size_t event_idx;  ///< Current event index.

	size_t loop_event[MSCL_MAX_LOOPS]; ///< Event index of loop begin.
	size_t loop_count[MSCL_MAX_LOOPS]; ///< Remaining number of times to repeat loop.
	size_t loop_idx;                   ///< Indicates loop nest-level.
	
	mscl_waveform* waveform; ///< Pointer to currently selected Waveform Envelope. NULL defaults to an output value of 0.0.
	mscl_envelope* sustain;  ///< Pointer to currently selected Sustain Envelope. NULL defaults to an output value of 1.0.
	mscl_envelope* release;  ///< Pointer to currently selected Release Envelope. NULL defaults to an output value of 0.0.
	mscl_envelope* vibrato;  ///< Pointer to currently selected Vibrato Envelope. NULL defaults to an output value of 0.0.

	mscl_fp frequency; ///< Current note frequency.
	mscl_fp volume;    ///< Current note volume.
	mscl_fp length;    ///< Current note length.
	
	mscl_fp next_event; ///< Timepoint (Beat) of the start of the next event.
	mscl_fp event_s;    ///< Timepoint (Beat) at which Note was started.
	mscl_fp event_r;    ///< Timepoint (Beat) at which Note was released.
};
typedef struct mscl_engine mscl_engine;

/**
 * @brief Metadata describing a list of events.
 */
struct mscl_metadata
{
	mscl_fp intro_beats; ///< Length of the section before the first Infinite Loop, or 0.0 if there are none.
	mscl_fp loop_beats;  ///< Length of the section after the Intro.
};
typedef struct mscl_metadata mscl_metadata;

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Estimates how long a list of events is.
 * @param num_events Number of events.
 * @param[in] events Pointer to events.
 * @return The calculated metadata.
 */
extern mscl_metadata mscl_estimate(size_t num_events, const mscl_event* events);

/**
 * @brief Generates an audio sample from a list of MSCL Events.
 * @param[in,out] engine The engine responsible for synthesizing audio.
 * @param sps Samples-per-Second to output at.
 * @param bpm Beats-per-Minute of the song.
 * @param num_events Number of events.
 * @param[in] events Pointer to events.
 * @return The generated Sample.
 * @warning If any of the parameters are changed between calls without re-initializing the engine, the results may be unexpected.
 */
extern mscl_fp mscl_advance(mscl_engine* engine, mscl_fp sps, mscl_fp bpm, size_t num_events, const mscl_event* events);

#ifdef __cplusplus
}
#endif

#endif
