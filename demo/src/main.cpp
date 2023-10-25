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
#include <format>

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Weverything"
#define OLC_PGE_APPLICATION
#include <olcPixelGameEngine.h>
#pragma clang diagnostic pop

// ================================================================================================================================

struct Sampler
{
	Channel channel;
	mscl_time song_len;

	mscl_sample sample;
	mscl_engine engine;
};

// ================================================================================================================================

class Demo : public olc::PixelGameEngine
{
private:

	inline static constexpr mscl_time sps = 48'000.0;

	Song song = song_Demo1;
	size_t loops = 0;
	
	size_t main_channel = {};
	mscl_time speed = {};
	mscl_time song_len = {};

	std::unique_ptr<Player> player = {};
	std::vector<float> samples = {};
	std::vector<Sampler> samplers = {};

private:

	bool init_player()
	{
		this->player.reset(player_xaudio2());
		return bool(player);
	}

	void select_song(const Song track)
	{
		song = track;

		const size_t num_channels = song.channels.size();
		samplers.clear();
		samplers.resize(num_channels);

		mscl_time max_len = 0.0;
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
		speed = song.tempo / mscl_time(60.0);
		song_len = max_len / speed;
	}

	void init_samples()
	{
		const size_t num_samples = size_t(sps * song_len);
		samples.clear();
		samples.resize(num_samples);

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
	}

public:

	Demo()
	{
		this->sAppName = "MuSiCaL Demo";
	}

	bool OnUserCreate() final
	{
		if (!init_player()) return false;
		select_song(song);
		init_samples();

		return true;
	}

	bool OnUserUpdate(float fElapsedTime [[maybe_unused]]) final
	{
		// Update
		{
			if (this->GetKey(olc::Key::SPACE).bPressed)
				player->play(samples.size(), samples.data(), sps);
		}

		// Render
		{
			this->Clear(olc::Pixel(0x18, 0x18, 0x18));
			const auto [width, height] = this->GetWindowSize();

			this->DrawLine({0, height / 2}, {width, height / 2}, olc::Pixel(0x40, 0x40, 0x40));

			const float half = float(height) / 2;
			const size_t num_samples = samples.size();
			const size_t sample_pos = player->pos();
			const bool playing = player->playing();
			
			this->DrawString({8, 8}, song.name, olc::WHITE, 2);

			if (playing)
			{
				for (int x = 0; x <= width; ++x)
				{
					const int px = x - 1;
					const int nx = x;

					const size_t pi = sample_pos + size_t(px);
					const size_t ni = sample_pos + size_t(nx);

					const float poffs = (pi < num_samples) ? samples[pi] : 0.0; 
					const float noffs = (ni < num_samples) ? samples[ni] : 0.0; 

					const int py = static_cast<int>(half + half * poffs);
					const int ny = static_cast<int>(half + half * noffs);
					this->DrawLine({px, py}, {nx, ny}, olc::Pixel(0xFF, 0xFF, 0xFF));
				}
			}
			else
			{
				constexpr float sc = 4.0f;
				constexpr float fs = 8.0f;
				const float ww = float(width);
				const float wh = float(height);
				const float tw = (sc * fs) * 20.0f;
				const float th = (sc * fs);
				const float tx = (ww - tw) * 0.5f;
				const float ty = (wh - th) * 0.5f;
				this->DrawString({int(tx), int(ty)}, "Press SPACE to play!", olc::WHITE, uint32_t(sc));
			}
		}

		return true;
	}
};

// ================================================================================================================================

static int olc_main()
{
	Demo demo = {};
	if (!demo.Construct(1280, 720, 1, 1, false, true)) return EXIT_FAILURE;

	demo.Start();
	return EXIT_SUCCESS;
}

#ifdef _WIN32
#   include <Windows.h>
int WINAPI wWinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPWSTR, _In_ int)
#else
int main(void)
#endif
{
	return olc_main();
}

// ================================================================================================================================
