/**
 * @file mscl_player/gui.cpp
 *
 * @brief Demo Program for MSCL library.
 */

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Weverything"
#define OLC_PGE_APPLICATION
#include <olcPixelGameEngine.h>
#pragma clang diagnostic pop

#include <vector>
#include <memory>
#include <chrono>
#include <thread>
#include <format>

#include <mscl.h>
#include "mscl_player.hpp"
#include "utils.hpp"

// ================================================================================================================================

struct Sampler
{
	mscl::Channel channel;
	mscl_time song_len;

	mscl_sample sample;
	mscl_engine engine;
};

inline static std::string time_format(const mscl_time seconds)
{
	const mscl_time tm = std::floor(seconds / mscl_time(60));
	const mscl_time ts = std::floor(seconds) - mscl_time(60) * tm;
	const mscl_time tf = std::floor((seconds - std::floor(seconds)) * mscl_time(1'000));

	if (tm > 0)
		return std::format("{}:{:02}.{:03}", tm, ts, tf);
	else
		return std::format("{}.{:03}", ts, tf);
}

// ================================================================================================================================

class MsclGUI : public olc::PixelGameEngine
{
private:

	inline static constexpr mscl_time sps = 48'000.0;
	
	std::span<const mscl::Song> songs = {};
	size_t song_idx = {};
	size_t loops = 0;
	
	size_t main_channel = {};
	mscl_time speed = {};
	mscl_time song_len = {};

	std::unique_ptr<mscl::Player> player = {};
	std::vector<float> samples = {};
	std::vector<Sampler> samplers = {};

	bool paused = false;
	bool loading = false;

private:

	bool init_player()
	{
		this->player.reset(mscl::Player::xaudio2());
		select_song(song_idx);

		return bool(player);
	}

	void select_song(size_t idx)
	{
		player->stop();
		
		const size_t num_songs = songs.size();
		while (intptr_t(idx) < 0) idx += num_songs;
		idx %= num_songs;

		song_idx = idx;
		init_samplers();
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

	void reset_engines()
	{
		for (Sampler& sampler : samplers) sampler.engine = mscl_engine{};
	}

	void init_samples()
	{
		player->stop();

		reset_engines();
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

	MsclGUI(const std::span<const mscl::Song> song_list)
		:
		songs{ song_list }
	{
		this->sAppName = "MuSiCaL Player";
	}

	bool OnUserCreate() final
	{
		if (!init_player()) return false;
		select_song(song_idx);
		return true;
	}

	bool OnUserUpdate(float fElapsedTime [[maybe_unused]]) final
	{
		// Update
		{
			const bool playing = player->playing();

			if (loading)
			{
				init_samples();
				reset_engines();
				
				player->submit(samples.size(), samples.data(), sps);
				player->play();
				paused = false;

				loading = false;
			}
			
			if (this->GetKey(olc::Key::SPACE).bPressed)
			{
				if (!playing)
				{
					loading = true;
				}
				else
				{
					if (paused)
						player->play();
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
				select_song(song_idx - 1);
			}

			if (this->GetKey(olc::Key::RIGHT).bPressed || this->GetKey(olc::Key::DOWN).bPressed)
			{
				select_song(song_idx + 1);
			}

			if (!playing) paused = false;
		}

		// Render
		{
			constexpr int font = 8;

			this->Clear(olc::Pixel(0x18, 0x18, 0x18));
			const auto [scw, sch] = this->GetScreenSize();

			this->DrawLine({0, sch / 2}, {scw, sch / 2}, olc::Pixel(0x40, 0x40, 0x40));

			const float half = float(sch) / 2;
			const size_t num_samples = samples.size();
			const size_t sample_pos = player->pos();
			const bool playing = player->playing();
			const mscl_time seconds = mscl_time(sample_pos) / sps;
			
			const std::string track = std::format("<{}:{}>", song_idx + 1, songs.size());
			const std::string label = std::format(" {}", songs[song_idx].name);
			const std::string times = std::format("{} / {}", time_format(seconds), time_format(song_len));
			const int len_ui = int(std::max(track.size() + label.size(), times.size()));
			const float ui_limit = float(scw) / float(font * len_ui);
			const int scale_ui = std::clamp(int(ui_limit), 1, 2);

			this->DrawString({font+(font*scale_ui)*0                , font+(font+font*scale_ui)*0}, track, olc::DARK_GREY, uint32_t(scale_ui));
			this->DrawString({font+(font*scale_ui)*int(track.size()), font+(font+font*scale_ui)*0}, label, olc::WHITE, uint32_t(scale_ui));
			this->DrawString({font+(font*scale_ui)*0                , font+(font+font*scale_ui)*1}, times, olc::Pixel(0xA0, 0xA0, 0xA0), uint32_t(scale_ui));
			
			if (playing)
			{
				for (int x = 0; x <= scw; ++x)
				{
					const int px = x - (scw / 2) - 1;
					const int nx = x - (scw / 2);

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

				if (loading)
				{
					msg = "LOADING...";
					color = olc::GREY;
				}
				else if (paused)
				{
					msg = "PAUSED";
					color = olc::RED;
				}
				else if (!playing)
				{
					msg = "Press SPACE to play!";
				}

				const int chars = int(msg.size());
				const float x_limit = float(scw) / float(font * chars);
				const float y_limit = float(sch) / float(font * 1);
				const int scale = std::clamp(std::min(int(x_limit), int(y_limit)), 1, 4);
				const int tw = (scale * font) * chars;
				const int th = (scale * font) * 1;
				const int tx = (scw - tw) / 2;
				const int ty = (sch - th) / 2;
				this->DrawString({tx, ty}, msg, color, uint32_t(scale));
			}
		}

		return true;
	}
};

// ================================================================================================================================

namespace mscl
{
	extern int gui(std::span<const mscl::Song> song_list, const int width, const int height, const bool fullscreen)
	{
		MsclGUI demo{ song_list };
		if (!demo.Construct(width, height, 1, 1, fullscreen, true)) return EXIT_FAILURE;

		demo.Start();
		return EXIT_SUCCESS;
	}
}

// ================================================================================================================================
