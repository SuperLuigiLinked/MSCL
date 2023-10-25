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
	inline static constexpr std::array songs = {
		song_Demo1,
		song_Demo2,
		song_Menuet,
	};

	size_t song_idx = 0;
	size_t loops = 0;
	
	size_t main_channel = {};
	mscl_time speed = {};
	mscl_time song_len = {};

	std::unique_ptr<Player> player = {};
	std::vector<float> samples = {};
	std::vector<Sampler> samplers = {};

	bool paused = false;

private:

	bool init_player()
	{
		this->player.reset(player_xaudio2());
		return bool(player);
	}

	void select_song(const size_t idx)
	{
		player->stop();
		
		ASSERT(idx < songs.size());
		song_idx = idx;
	}

	void init_samplers()
	{
		const size_t num_channels = songs[song_idx].channels.size();
		samplers.clear();
		samplers.resize(num_channels);

		mscl_time max_len = 0.0;
		for (size_t i = 0; i < num_channels; ++i)
		{
			samplers[i].channel = songs[song_idx].channels.begin()[i];
			samplers[i].song_len = mscl_estimate(samplers[i].channel.size(), samplers[i].channel.data(), loops);
			if (samplers[i].song_len > max_len)
			{
				max_len = samplers[i].song_len;
				main_channel = i;
			}
		}
		speed = songs[song_idx].tempo / mscl_time(60.0);
		song_len = max_len / speed;
	}

	void init_samples()
	{
		player->stop();

		init_samplers();
		samples.clear();
		samples.resize(size_t(song_len * sps));

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
		return true;
	}
	

	bool OnUserUpdate(float fElapsedTime [[maybe_unused]]) final
	{
		// Update
		{
			using usize = size_t;
			using isize = intptr_t;

			const bool playing = player->playing();

			if (this->GetKey(olc::Key::SPACE).bPressed)
			{
				if (!playing)
				{
					init_samples();
					player->play(samples.size(), samples.data(), sps);
					paused = false;
				}
				else
				{
					if (paused)
						player->unpause();
					else
						player->pause();

					paused = !paused;
				}
			}

			if (this->GetKey(olc::Key::BACK).bPressed)
			{
				player->stop();
				paused = false;
			}

			if (this->GetKey(olc::Key::LEFT).bPressed || this->GetKey(olc::Key::UP).bPressed)
			{
				select_song((usize)imodf(isize(song_idx - 1), isize(songs.size())));
			}

			if (this->GetKey(olc::Key::RIGHT).bPressed || this->GetKey(olc::Key::DOWN).bPressed)
			{
				select_song((usize)imodf(isize(song_idx + 1), isize(songs.size())));
			}

			if (!playing) paused = false;
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
			
			this->DrawString({8+16*0, 8+16*0}, songs[song_idx].name, olc::WHITE, 2);

			if (playing)
			{
				for (int x = 0; x <= width; ++x)
				{
					const int px = x - (width / 2) - 1;
					const int nx = x - (width / 2);

					const size_t pi = sample_pos + size_t(px);
					const size_t ni = sample_pos + size_t(nx);

					const float poffs = (pi < num_samples) ? samples[pi] : 0.0; 
					const float noffs = (ni < num_samples) ? samples[ni] : 0.0; 

					const int py = static_cast<int>(half + half * poffs);
					const int ny = static_cast<int>(half + half * noffs);
					this->DrawLine({x-1, py}, {x, ny}, olc::Pixel(0xFF, 0xFF, 0xFF));
				}
			}

			{
				std::string msg{};
				olc::Pixel color = olc::WHITE;

				if (paused)
				{
					msg = "PAUSED";
					color = olc::RED;
				}
				else if (!playing)
				{
					msg = "Press SPACE to play!";
				}

				constexpr float sc = 4.0f;
				constexpr float fs = 8.0f;
				const float ww = float(width);
				const float wh = float(height);
				const float tw = (sc * fs) * float(msg.size());
				const float th = (sc * fs);
				const float tx = (ww - tw) * 0.5f;
				const float ty = (wh - th) * 0.5f;
				this->DrawString({int(tx), int(ty)}, msg, color, uint32_t(sc));
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
