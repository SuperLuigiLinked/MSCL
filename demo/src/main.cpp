/**
 * @file demo/main.cpp
 *
 * @brief Demo Program for MSCL library.
 */

#include <mscl.h>
#include "player.hpp"
#include "utils.h"

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

	constexpr mscl_time sps = 44'100.0;
	constexpr size_t num_samples = size_t(sps);
	float samples[num_samples];
	
	for (size_t i = 0; i < num_samples; ++i)
	{
		const mscl_time secs = mscl_time(i) / sps;
		const mscl_sample freq = 440.0;
		samples[i] = mscl_sample(0.20) * sin(mscl_time(MSCL_TAU) * secs * freq); 
	}

	const mscl_time song_len = mscl_time(num_samples) / sps;

	LOG("[MSCL] Playing...\n");
	player->play(num_samples, samples);

	std::this_thread::sleep_for(std::chrono::duration<mscl_time>(song_len));

	LOG("[MSCL] Exiting...\n");
    return EXIT_SUCCESS;
}
