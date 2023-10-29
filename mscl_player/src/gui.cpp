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
#include <format>

#include <mscl.h>
#include "mscl_player.hpp"
#include "mscl_gui.hpp"
#include "utils.hpp"

// ================================================================================================================================

inline static std::string time_format(const mscl_fp seconds)
{
	const mscl_fp tm = std::floor(seconds / mscl_fp(60));
	const mscl_fp ts = std::floor(seconds) - mscl_fp(60) * tm;
	const mscl_fp tf = std::floor((seconds - std::floor(seconds)) * mscl_fp(1'000));

	if (tm > 0)
		return std::format("{}:{:02}.{:03}", tm, ts, tf);
	else
		return std::format("{}.{:03}", ts, tf);
}

inline static constexpr auto imodf(const auto a, const auto b) noexcept
{
	return (a % b) + b * ((a % b) && ((a ^ b) < 0));
}

// ================================================================================================================================

class MsclGUI : public olc::PixelGameEngine
{
private:

	struct Synth
	{
		mscl::Channel channel;
		mscl_metadata metadata;
		mscl_engine engine;
		mscl_fp sample;
	};

	inline static constexpr mscl_fp sps = 48'000.0;

private:
	
	std::span<const mscl::Song> songs = {};
	size_t song_idx = size_t(-1);
	size_t loaded_idx = size_t(-1);
	
	size_t main_channel = {};
	mscl_fp song_seconds = {};

	std::unique_ptr<mscl::Player> player = {};
	std::vector<float> samples = {};
	std::vector<Synth> synths = {};

	bool loop = false;
	bool paused = false;
	bool loading = false;

public:

	MsclGUI(const std::span<const mscl::Song> song_list);
	bool OnUserCreate() final;
	bool OnUserUpdate(float fElapsedTime) final;

private:

	void update();
	void render();

	bool init_player();
	void init_engines();

	void select_song(size_t idx);
	void load_song();
};

// ================================================================================================================================

MsclGUI::MsclGUI(const std::span<const mscl::Song> song_list)
	:
	songs{ song_list }
{
	this->sAppName = "MuSiCaL Player";
}

bool MsclGUI::OnUserCreate()
{
	if (!init_player()) return false;
	select_song(0);
	return true;
}

bool MsclGUI::OnUserUpdate(float fElapsedTime [[maybe_unused]])
{
	update();
	render();
	return true;
}

// --------------------------------------------------------------------------------------------------------------------------------

void MsclGUI::update()
{
	bool playing = player->playing();

	if (this->GetKey(olc::Key::BACK).bPressed)
	{
		paused = false;
		playing = false;

		player->stop();
	}

	if (loading || (!playing && loop))
	{
		load_song();
		loading = false;
		paused = false;
		playing = true;

		const double offs_pc = 0.625 * !(playing && loop) * 0;
		const size_t offs_sp = size_t(double(samples.size()) * offs_pc);
		const size_t size = samples.size() - offs_sp;
		const float* const data = samples.data() + offs_sp;
		player->submit(size, data, sps);
		player->play();
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

	if (this->GetKey(olc::Key::ENTER).bPressed)
	{
		loop = !loop;
		if (!playing && loop) loading = true;
	}

	if (this->GetKey(olc::Key::LEFT).bPressed || this->GetKey(olc::Key::UP).bPressed)
	{
		select_song(song_idx - 1);
		if (loop) loading = true;
	}

	if (this->GetKey(olc::Key::RIGHT).bPressed || this->GetKey(olc::Key::DOWN).bPressed)
	{
		select_song(song_idx + 1);
		if (loop) loading = true;
	}
	if (!playing) paused = false;
}

// --------------------------------------------------------------------------------------------------------------------------------

void MsclGUI::render()
{
	constexpr int font = 8;

	this->Clear(olc::Pixel(0x18, 0x18, 0x18));
	const auto [scw, sch] = this->GetScreenSize();

	this->DrawLine({0, sch / 2}, {scw, sch / 2}, olc::Pixel(0x40, 0x40, 0x40));

	const float half = float(sch) / 2;
	const size_t num_samples = samples.size();
	const size_t sample_pos = player->pos();
	const bool playing = player->playing();
	const mscl_fp seconds = mscl_fp(sample_pos) / sps;
	
	const std::string track = std::format("<{}:{}>", song_idx + 1, songs.size());
	const std::string label = std::format(" {}", songs[song_idx].name);
	const std::string times = std::format("{} / {}", time_format(seconds), time_format(song_seconds));
	const int len_ui = int(std::max(track.size() + label.size(), times.size()));
	const float ui_limit = float(scw) / float(font * len_ui);
	const int scale_ui = std::clamp(int(ui_limit), 1, 2);

	const olc::Pixel timer_color = (loop ? olc::Pixel(0x00, 0xFF, 0x00) : olc::Pixel(0xA0, 0xA0, 0xA0));

	this->DrawString({font+(font*scale_ui)*0                , font+(font+font*scale_ui)*0}, track, olc::DARK_GREY, uint32_t(scale_ui));
	this->DrawString({font+(font*scale_ui)*int(track.size()), font+(font+font*scale_ui)*0}, label, olc::WHITE, uint32_t(scale_ui));
	this->DrawString({font+(font*scale_ui)*0                , font+(font+font*scale_ui)*1}, times, timer_color, uint32_t(scale_ui));
	
	if (playing && !loading)
	{
		for (int x = 0; x <= scw; ++x)
		{
			const int px = x - (scw / 2) - 1;
			const int nx = x - (scw / 2);

			const size_t pi = sample_pos + size_t(px);
			const size_t ni = sample_pos + size_t(nx);

			const float poffs = (pi < num_samples) ? samples[pi] : 0.0; 
			const float noffs = (ni < num_samples) ? samples[ni] : 0.0; 

			const int py = static_cast<int>(half - half * poffs);
			const int ny = static_cast<int>(half - half * noffs);
			this->DrawLine({x-1, py}, {x, ny}, olc::Pixel(0xFF, 0xFF, 0xFF));
		}
	}

	{
		std::string msg{};
		olc::Pixel color = olc::WHITE;

		if (loading || (loop & !playing))
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

// --------------------------------------------------------------------------------------------------------------------------------

bool MsclGUI::init_player()
{
	this->player.reset(mscl::Player::xaudio2());
	return bool(player);
}

void MsclGUI::init_engines()
{
	for (Synth& synth : synths) synth.engine = mscl_engine{};
}

void MsclGUI::select_song(const size_t idx)
{
	const size_t sel_idx = size_t(imodf(intptr_t(idx), intptr_t(songs.size())));

	if (song_idx != sel_idx)
	{
		player->stop();
		song_idx = sel_idx;

		const size_t num_channels = songs[song_idx].channels.size();
		synths.resize(num_channels);

		mscl_fp max_beats = 0.0;
		for (size_t i = 0; i < num_channels; ++i)
		{
			synths[i].channel = songs[song_idx].channels.begin()[i];
			synths[i].metadata = mscl_estimate(synths[i].channel.size(), synths[i].channel.data());
			const mscl_fp channel_beats = synths[i].metadata.intro_beats + synths[i].metadata.loop_beats;
			if (channel_beats > max_beats)
			{
				max_beats = channel_beats;
				main_channel = i;
			}
		}
		const mscl_fp song_speed = songs[song_idx].bpm / mscl_fp(60);
		song_seconds = (song_speed > 0) ? (max_beats / song_speed) : 0.0;
	}
}

void MsclGUI::load_song()
{
	if (loaded_idx != song_idx)
	{
		player->stop();
		loaded_idx = song_idx;

		init_engines();
		samples.resize(size_t(song_seconds * sps));

		for (float& sample : samples)
		{
			mscl_fp data = 0.0;
			for (Synth& synth : synths)
			{
				synth.sample = mscl_advance(&synth.engine, sps, songs[song_idx].bpm, synth.channel.size(), synth.channel.data());
				data += synth.sample;
			}
			sample = float(data);
		}
	}
}

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
