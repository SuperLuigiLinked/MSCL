/**
 * @file demo/main.cpp
 *
 * @brief Demo Program for MSCL library.
 */

#include <mscl.h>

#include "utils.h"
#include "player.hpp"
#include "songs.hpp"

#include <span>
#include <vector>
#include <memory>
#include <chrono>
#include <thread>

static int play_song(const Song song, const size_t loops = 0)
{
	const std::unique_ptr<Player> player{ player_xaudio2() };
	if (!player) return EXIT_FAILURE;
	
	ASSERT(loops != MSCL_LOOP_INFINITE);

	constexpr mscl_time sps = 44'100.0;

	struct Sampler
	{
		Channel channel;
		mscl_time song_len;

		mscl_sample sample;
		mscl_engine engine;
	};

	const size_t num_channels = song.channels.size();
	std::vector<Sampler> samplers(num_channels);
	
	mscl_time max_len = 0.0;
	[[maybe_unused]] size_t main_channel = 0;

	for (size_t i = 0; i < num_channels; ++i)
	{
		samplers[i].channel = song.channels.begin()[i];
		samplers[i].song_len = mscl_estimate(samplers[i].channel.size(), samplers[i].channel.data(), loops);
		if (samplers[i].song_len > max_len)
		{
			max_len = samplers[i].song_len;
			main_channel = i;
		}
	}
	const mscl_time speed = song.tempo / mscl_time(60.0);
	const mscl_time song_len = max_len / speed;

	const size_t num_samples = size_t(sps * song_len);
	std::vector<float> samples(num_samples);

	LOG("[MSCL] Generating...\n");
	for (float& sample : samples)
	{
		mscl_sample data = 0.0;
		for (Sampler& sampler : samplers)
		{
			sampler.sample = mscl_advance(&sampler.engine, sps, speed, sampler.channel.size(), sampler.channel.data());
			data += sampler.sample;
		}
		sample = float(data);
	}

	LOG("[MSCL] Playing...\n");
	player->play(num_samples, samples.data(), sps);

	LOG("[MSCL] Sleeping... [%f]\n", double(song_len));
	std::this_thread::sleep_for(std::chrono::duration<mscl_time>(song_len));

	LOG("[MSCL] Stopping...\n");
    return EXIT_SUCCESS;
}

#ifdef _WIN32
#   include <Windows.h>
int WINAPI wWinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPWSTR, _In_ int)
#else
int main(void)
#endif
{
	return play_song(song_Demo1, 0);
}
