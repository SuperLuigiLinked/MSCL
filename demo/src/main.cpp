/**
 * @file demo/main.cpp
 *
 * @brief Demo Program for MSCL library.
 */

#include <mscl.h>

#include "utils.h"
#include "player.hpp"
#include "songs.hpp"

#include <vector>
#include <memory>
#include <chrono>
#include <thread>

#ifdef _WIN32
#   include <Windows.h>
int WINAPI wWinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPWSTR, _In_ int)
#else
int main(void)
#endif
{
	const std::unique_ptr<Player> player{ player_xaudio2() };
	if (!player) return EXIT_FAILURE;

	const size_t num_events = demo1_n0.size();
	const mscl_event* const events = demo1_n0.data();

	constexpr mscl_time sps = 44'100.0;
	const mscl_time song_len = mscl_estimate(num_events, events);

	const size_t num_samples = size_t(sps * song_len);
	std::vector<float> samples(num_samples);

	LOG("[MSCL] Generating...\n");
	mscl_engine engine = {};
	for (float& sample : samples)
	{
		const mscl_sample data = mscl_advance(&engine, sps, num_events, events);
		sample = float(data);
	}

	LOG("[MSCL] Playing...\n");
	player->play(num_samples, samples.data(), sps);

	LOG("[MSCL] Sleeping... [%f]\n", double(song_len));
	std::this_thread::sleep_for(std::chrono::duration<mscl_time>(song_len));

	LOG("[MSCL] Exiting...\n");
    return EXIT_SUCCESS;
}
