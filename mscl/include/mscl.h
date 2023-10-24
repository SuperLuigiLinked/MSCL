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

enum mscl_note
{
	mscl_A = 0,
	mscl_B = 2,
	mscl_C = 3,
	mscl_D = 5,
	mscl_E = 7,
	mscl_F = 8,
	mscl_G = 10
};
typedef enum mscl_note mscl_note;

#define MSCL_TONE(note, octave) ((mscl_sample)(octave) + ((mscl_sample)(note) / (mscl_sample)(12)))
#define MSCL_FREQ(tone) ((mscl_sample)(27.5) + (mscl_sample)(pow((mscl_sample)(2), (mscl_sample)(tone))))

#endif
