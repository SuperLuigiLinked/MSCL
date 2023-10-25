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

static int play_song(const std::span<const mscl_event> song)
{
	const std::unique_ptr<Player> player{ player_xaudio2() };
	if (!player) return EXIT_FAILURE;

	const size_t num_events = song.size();
	const mscl_event* const events = song.data();

	constexpr mscl_time sps = 44'100.0;
	constexpr mscl_time speed = 1.00;
	const mscl_time song_len = mscl_estimate(num_events, events) / speed;

	const size_t num_samples = size_t(sps * song_len);
	std::vector<float> samples(num_samples);

	LOG("[MSCL] Generating...\n");
	mscl_engine engine = {};
	for (float& sample : samples)
	{
		const mscl_sample data = mscl_advance(&engine, sps / speed, num_events, events);
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
	return play_song(demo1_c0);
}
