/**
 * @file mscl/mscl.c
 *
 * @brief MuSiCaL: a Music Synthesis Coding Language
 */

#include <mscl.h>

extern mscl_metadata mscl_estimate(const size_t num_events, const mscl_event* const events)
{
	mscl_time song_beats = 0.0;
	mscl_time length = 0.0;

	size_t loop_event[MSCL_MAX_LOOPS] = {0};
	size_t loop_count[MSCL_MAX_LOOPS] = {0};
	size_t loop_iters[MSCL_MAX_LOOPS] = {0};
	size_t loop_idx = 0;

	mscl_metadata metadata = {0};

	for (size_t event_idx = 0; event_idx < num_events; ++event_idx)
	{
		switch (events[event_idx].type)
		{
		case mscl_event_rest:
		case mscl_event_tone:
			song_beats += length;
		break;

		case mscl_event_length:
			length = events[event_idx].data.length;
		break;

		case mscl_event_loop_begin:
			if (loop_idx < MSCL_MAX_LOOPS)
			{
				loop_event[loop_idx] = event_idx;
				loop_count[loop_idx] = events[event_idx].data.loop_begin;
				loop_iters[loop_idx] = 0;
				if (loop_count[loop_idx] == MSCL_LOOP_INFINITE) metadata.intro_beats = song_beats;
			}
			++loop_idx;
		break;

		case mscl_event_loop_end:
			if (loop_idx > 0)
			{
				--loop_idx;
				if (loop_idx < MSCL_MAX_LOOPS)
				{
					if (loop_count[loop_idx] == MSCL_LOOP_INFINITE) goto break_loop;

					++loop_iters[loop_idx];
					if (loop_iters[loop_idx] <= loop_count[loop_idx])
					{
						event_idx = loop_event[loop_idx];
						++loop_idx;
					}
				}
			}
			else // Unbalanced LOOP-END statements are treated as Infinite Loops.
			{
				goto break_loop;
			}
		break;

		case mscl_event_volume:
		case mscl_event_waveform:
		case mscl_event_sustain:
		case mscl_event_release:
		case mscl_event_vibrato:
		break;
		}
	}
break_loop:
	metadata.loop_beats = song_beats - metadata.intro_beats;
	return metadata;
}

extern mscl_sample mscl_advance(mscl_engine* const engine, const mscl_time sps, const mscl_time speed, const size_t num_events, const mscl_event* const events)
{
	if (!engine) return 0;

	const mscl_time seconds = (mscl_time)engine->sample_idx / sps;
	const mscl_time beats = seconds * speed;

	while ((engine->event_idx < num_events) && (beats >= engine->next_event))
	{
		const mscl_event* const event = events + engine->event_idx;
		switch (event->type)
		{
			case mscl_event_rest:
				engine->next_event += engine->length;
			break;

			case mscl_event_tone:
				engine->frequency = MSCL_FREQ(event->data.tone);
				engine->event_s = engine->next_event;
				engine->event_r = engine->next_event + engine->length;
				engine->next_event += engine->length;
			break;

			case mscl_event_length:
				engine->length = event->data.length;
			break;

			case mscl_event_volume:
				engine->volume = event->data.volume;
			break;

			case mscl_event_loop_begin:
				if (engine->loop_idx < MSCL_MAX_LOOPS)
				{
					engine->loop_event[engine->loop_idx] = engine->event_idx;
					engine->loop_count[engine->loop_idx] = event->data.loop_begin;
					engine->loop_iters[engine->loop_idx] = 0;
				}
				++engine->loop_idx;
			break;

			case mscl_event_loop_end:
				if (engine->loop_idx > 0)
				{
					--engine->loop_idx;
					if (engine->loop_idx < MSCL_MAX_LOOPS)
					{
						++engine->loop_iters[engine->loop_idx];
						if (engine->loop_iters[engine->loop_idx] <= engine->loop_count[engine->loop_idx])
						{
							engine->event_idx = engine->loop_event[engine->loop_idx];
							++engine->loop_idx;
						}
					}
				}
				else // Unbalanced LOOP-END statements are treated as Infinite Loops.
				{
					engine->event_idx = 0;
				}
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

	const mscl_time sustain_beats = beats - engine->event_s;
	const mscl_time release_beats = beats - engine->event_r;
	const mscl_time tone_beats = engine->event_r - engine->event_s;

	const mscl_time sustain_seconds = sustain_beats / speed;
	const mscl_time release_seconds = release_beats / speed;
	const mscl_time tone_seconds = tone_beats / speed;

	const mscl_sample d_sample = engine->vibrato
		? MSCL_POW((mscl_sample)2, engine->vibrato(sustain_seconds) / (mscl_sample)12)
		: (mscl_sample)1.0;
	
	const mscl_sample w_sample = engine->waveform
		? engine->waveform(sustain_seconds, engine->frequency * d_sample)
		: (mscl_sample)0.0;

	const mscl_sample e_sample = (release_seconds < 0)
		? (engine->sustain ? engine->sustain(sustain_seconds) : (mscl_sample)1.0)
		: (engine->release ? engine->sustain(tone_seconds) * engine->release(release_seconds) : (mscl_sample)0.0);

	const mscl_sample sample = w_sample * e_sample * engine->volume; 

	++engine->sample_idx;
	return sample;
}
