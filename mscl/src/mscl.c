/**
 * @file mscl.c
 *
 * @brief MuSiCaL: a Music Synthesis Coding Language
 */

#include <mscl.h>
#include <math.h>

#if !defined(NDEBUG)
    #include <stdio.h>
    #include <stdlib.h>

    #define LOG(...) (void)fprintf(stderr, __VA_ARGS__)
    #define DBG_ASSERT(expr) if (expr) {} else (LOG("ASSERTION FAILED:\n" #expr "\n"), abort())
#else
    #define LOG(...) (void)0
    #define DBG_ASSERT(expr) (void)0
#endif

extern mscl_time mscl_estimate(const size_t num_events, const mscl_event* const events)
{
	mscl_time time = 0.0;
    mscl_time length = 0.0;

	for (size_t i = 0; i < num_events; ++i)
	{
        if (events[i].type == mscl_event_length)
            length = events[i].data.length;
        
        if (events[i].type == mscl_event_tone)
            time += length;
	}
	return time;
}

extern mscl_sample mscl_advance(mscl_engine* const engine, const mscl_time sps, const mscl_time speed, const size_t num_events, const mscl_event* const events)
{
    if (!engine) return 0;

    const mscl_time seconds = (mscl_time)engine->sample_idx / (sps / speed);

    while ((engine->event_idx < num_events) && (seconds >= engine->next_event))
    {
        const mscl_event* const event = events + engine->event_idx;
        switch (event->type)
        {
            case mscl_event_tone:
                if (event->data.tone != MSCL_REST)
                {
                    engine->event_s = engine->next_event;
                    engine->event_r = engine->next_event + engine->length;
                    engine->frequency = MSCL_FREQ(event->data.tone);
                }
                engine->next_event += engine->length;
            break;

            case mscl_event_length:
                engine->length = event->data.length;
            break;
            
            case mscl_event_volume:
                engine->volume = event->data.volume;
            break;
            
            case mscl_event_waveform:
                engine->waveform = event->data.waveform;
            break;
            
            case mscl_event_sustain:
                engine->sustain = event->data.sustain;
            break;
            
            case mscl_event_release:
                engine->release = event->data.release;
            break;

            case mscl_event_vibrato:
                engine->vibrato = event->data.vibrato;
            break;
        }
        ++engine->event_idx;
    }

    const mscl_time sus_secs = (seconds - engine->event_s) / speed;
    const mscl_time rel_secs = (seconds - engine->event_r) / speed;
    const mscl_time tone_len = (engine->event_r - engine->event_s) / speed;

    const mscl_sample v_sample = engine->vibrato ? engine->vibrato(sus_secs) : (mscl_sample)1.0;
    const mscl_sample w_sample = engine->waveform ? engine->waveform(sus_secs * (engine->frequency * v_sample)) : (mscl_sample)0.0;
    const mscl_sample e_sample = (rel_secs >= 0) ? (engine->release ? engine->sustain(tone_len) * engine->release(rel_secs) : (mscl_sample)0.0) : (engine->sustain ? engine->sustain(sus_secs) : (mscl_sample)0.0);
    const mscl_sample sample = w_sample * e_sample * engine->volume; 

    ++engine->sample_idx;
    return sample;
}
