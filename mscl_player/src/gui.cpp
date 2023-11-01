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
#include <chrono>

#include <mscl.h>
#include "mscl_gui.hpp"
#include "mscl_player.hpp"
#include "utils.hpp"

// ================================================================================================================================

/**
 * @brief Converts time intervals to text.
 * @param seconds The amount of seconds.
 * @return A string formatted as "Minutes:Seconds.milliseconds"
 */
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

/**
 * @brief Integer Modulo based on Floored Division.
 */
template <typename T> inline static constexpr T imodf(const T a, const T b) noexcept
{
	return (a % b) + b * ((a % b) && ((a ^ b) < 0));
}

inline static olc::Pixel hue(const float pc) noexcept
{
	const float npc = pc - std::floor(pc);
	const int offs = int(std::floor((255 * 3) * npc)) % 255;
	const int step = int(npc * 3);
	switch (step)
	{
	case 0: return olc::Pixel(uint8_t(255 - offs), uint8_t(offs), uint8_t(0));
	case 1: return olc::Pixel(uint8_t(0), uint8_t(255 - offs), uint8_t(offs));
	case 2: return olc::Pixel(uint8_t(offs), uint8_t(0), uint8_t(255 - offs));
	default: return olc::Pixel();
	}
}

// ================================================================================================================================

/**
 * @brief GUI responsible for visualizing MSCL Songs and handling user-interaction.
 */
class MsclGUI : public olc::PixelGameEngine
{
private:

	inline static constexpr mscl_fp sps = 48'000.0;
	
	inline static constexpr int fontsize = 8;

	struct Synth
	{
		mscl::Channel channel;
		mscl_metadata metadata;
		mscl_engine engine;
		mscl_fp sample;
	};

	using Clock = std::chrono::steady_clock;
	using Tick = Clock::time_point;
	using Ticks = Clock::duration;

private:
	
	std::span<const mscl::Song> songs = {};
	size_t song_idx = size_t(-1);
	size_t loaded_idx = size_t(-1);
	
	size_t main_channel = {};
	size_t song_channels = {};
	size_t song_samples = {}; 
	mscl_fp song_seconds = {};

	std::unique_ptr<mscl::Player> player = {};
	std::vector<float> samples = {};
	std::vector<float> channels = {};
	std::vector<Synth> synths = {};

	bool loop = false;
	bool paused = false;
	bool loading = false;

	bool multichannel = false;
	bool debug = false;
	Ticks tm_update = {};
	Ticks tm_render = {};
	Ticks tm_select = {};
	Ticks tm_load = {};

private:

	void update();
	void render();

	bool init_player();
	void init_engines();

	void select_song(size_t idx);
	void load_song();

	void draw_waveform(int pixel_x, int pixel_y, int pixel_w, int pixel_h, size_t sample_pos, std::span<const float> sample_buffer, bool loaded, olc::Pixel color_wav = olc::WHITE);
	void draw_text(int center_x, int center_y, int scale, olc::Pixel color, const std::string& text);

public:

	MsclGUI(std::span<const mscl::Song> song_list);
	bool OnUserCreate() final;
	bool OnUserUpdate(float fElapsedTime) final;

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
	const Tick t1 = Clock::now();
	update();
	const Tick t2 = Clock::now();
	render();
	const Tick t3 = Clock::now();

	tm_update = t2 - t1;
	tm_render = t3 - t2;
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

	#if 0
		const size_t offs_sp = (playing && loop) ? 0 : size_t(double(samples.size()) * 0.625);
	#else
		const size_t offs_sp = 0;
	#endif
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

	if (this->GetKey(olc::Key::TAB).bPressed)
	{
		multichannel = !multichannel;
	}

	if (this->GetKey(olc::Key::ESCAPE).bPressed)
	{
		debug = !debug;
	}

	if (!playing) paused = false;
}

// --------------------------------------------------------------------------------------------------------------------------------

void MsclGUI::render()
{
	const size_t sample_pos = player->pos();
	const bool playing = player->playing();

	const auto [screen_w, screen_h] = this->GetScreenSize();
	const int center_x = screen_w / 2;
	const int center_y = screen_h / 2;

	const mscl_fp seconds = mscl_fp(sample_pos) / sps;
	const bool looping = !playing && loop;
	const bool loaded = playing && !loading;
	
	const std::string track = std::format("<{}:{}>", song_idx + 1, songs.size());
	const std::string label = std::format(" {}", songs[song_idx].name);
	const std::string times = std::format("{} / {}", time_format(seconds), time_format(song_seconds));
	const olc::Pixel timer_color = (loop ? olc::Pixel(0x00, 0xFF, 0x00) : olc::Pixel(0xA0, 0xA0, 0xA0));
	
	const int length_ui = int(std::max(track.size() + label.size(), times.size()));
	const float limit_ui = float(screen_w) / float(fontsize * length_ui);
	
	const uint32_t scale_ui = uint32_t(std::clamp(int(limit_ui), 1, 2));
	const int chr_w = fontsize * int(scale_ui);
	const int chr_h = fontsize * int(scale_ui) + fontsize;
	const int ui_x = fontsize + chr_w * 0;
	const int ui_y = fontsize + chr_h * 0;

	const uint32_t scale_dbg = uint32_t(std::max(int(scale_ui) / 2, 1));
	const int dbg_x = fontsize + chr_w * 0;
	const int dbg_y = fontsize + chr_h * 3;
	
	this->Clear(olc::Pixel(0x18, 0x18, 0x18));

	// Draw waveform
	{
		const int wav_x = 0;
		const int wav_y = 0;
		const int wav_w = screen_w;
		const int wav_h = screen_h;

		if (multichannel)
		{
			for (size_t ci = 0; ci < song_channels; ++ci)
			{
				const float pc = float(ci) / float(song_channels);

				constexpr int rows = 2;
				const int cols = int(std::ceil(float(song_channels) / float(rows)));
				const int xi = int(ci) % cols;
				const int yi = int(ci) / cols;
				const int elems = std::min(cols, int(song_channels) - cols * yi);

				const int w = wav_w / elems;
				const int h = wav_h / rows;
				const int x = wav_x + xi * w;
				const int y = wav_y + yi * h;
				const olc::Pixel color = hue(pc);
				const size_t index = song_samples * ci;
				const std::span<const float> buffer{ channels.data() + index, song_samples };

				this->draw_waveform(x, y, w, h, sample_pos, buffer, loaded, color);
			}
		}
		this->draw_waveform(wav_x, wav_y, wav_w, wav_h, sample_pos, samples, loaded);
	}

	// Draw HUD
	{
		this->DrawString({ui_x+chr_w*0                , ui_y+chr_h*0}, track, olc::DARK_GREY, scale_ui);
		this->DrawString({ui_x+chr_w*int(track.size()), ui_y+chr_h*0}, label, olc::WHITE, scale_ui);
		this->DrawString({ui_x+chr_w*0                , ui_y+chr_h*1}, times, timer_color, scale_ui);
		
		if (debug)
		{
			this->DrawString({dbg_x+chr_w*0, dbg_y+chr_h*0}, "DEBUG MENU", olc::GREY, scale_ui);
			this->DrawString({dbg_x+chr_w*0, dbg_y+chr_h*1}, std::format("* Time Update: {:>10} ns", std::chrono::nanoseconds(tm_update).count()), olc::GREY, scale_dbg);
			this->DrawString({dbg_x+chr_w*0, dbg_y+chr_h*2}, std::format("* Time Render: {:>10} ns", std::chrono::nanoseconds(tm_render).count()), olc::GREY, scale_dbg);
			this->DrawString({dbg_x+chr_w*0, dbg_y+chr_h*3}, std::format("* Time Select: {:>10} ns", std::chrono::nanoseconds(tm_select).count()), olc::GREY, scale_dbg);
			this->DrawString({dbg_x+chr_w*0, dbg_y+chr_h*4}, std::format("* Time Load  : {:>10} ns", std::chrono::nanoseconds(tm_load  ).count()), olc::GREY, scale_dbg);
			this->DrawString({dbg_x+chr_w*0, dbg_y+chr_h*5}, std::format("* Channels: {}", song_channels), olc::GREY, scale_dbg);
			if (loaded_idx == song_idx)
				this->DrawString({dbg_x+chr_w*0, dbg_y+chr_h*6}, std::format("* Samples : {}", song_samples ), olc::GREY, scale_dbg);
			else
				this->DrawString({dbg_x+chr_w*0, dbg_y+chr_h*6}, std::format("* Samples : -"), olc::GREY, scale_dbg);
		}
	}

	// Draw center-text
	{
		std::string msg{};
		olc::Pixel color = olc::WHITE;

		if (loading || looping)
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

		const int length = int(msg.size());
		if (length > 0)
		{
			const int limit_x = screen_w / (fontsize * length);
			const int limit_y = screen_h / (fontsize * 1);
			const int limit = std::min(limit_x, limit_y);
			const int scale = std::clamp(limit, 1, 4);
			this->draw_text(center_x, center_y, scale, color, msg);
		}
	}
}

void MsclGUI::draw_waveform(const int pixel_x, const int pixel_y, const int pixel_w, const int pixel_h, const size_t sample_pos, const std::span<const float> sample_buffer, const bool loaded, const olc::Pixel color_wav)
{
	const olc::Pixel color_hud = color_wav / 4;

	const size_t num_samples = sample_buffer.size();
	const int half_w = pixel_w / 2;
	const int half_h = pixel_h / 2;

	this->DrawLine({pixel_x, pixel_y + half_h}, {pixel_x + pixel_w - 1, pixel_y + half_h}, color_hud);

	if (loaded)
	{
		for (int nx = 1; nx < pixel_w; ++nx)
		{
			const int px = nx - 1;
			const size_t ni = sample_pos + size_t(nx - half_w);
			const size_t pi = sample_pos + size_t(px - half_w);
			const bool nb = ni < num_samples;
			const bool pb = pi < num_samples;
			const float ns = nb ? sample_buffer[ni] : 0.0;
			const float ps = pb ? sample_buffer[pi] : 0.0;
			const int ny = half_h - static_cast<int>(float(half_h) * ns);
			const int py = half_h - static_cast<int>(float(half_h) * ps);
			const olc::vi2d nv = {pixel_x + nx, pixel_y + ny};
			const olc::vi2d pv = {pixel_x + px, pixel_y + py};

			if (pb && nb)
				this->DrawLine(pv, nv, color_wav);
			else if (pb)
				this->Draw(pv, color_wav);
			else if (nb)
				this->Draw(nv, color_wav);
		}
	}
}

void MsclGUI::draw_text(const int center_x, const int center_y, const int scale, const olc::Pixel color, const std::string& text)
{
	const int length = int(text.size());
	const int text_w = (scale * fontsize) * length;
	const int text_h = (scale * fontsize) * 1;
	const int text_x = center_x - text_w / 2;
	const int text_y = center_y - text_h / 2;
	this->DrawString({text_x, text_y}, text, color, uint32_t(scale));
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
	const Tick t1 = Clock::now();
	{
		const size_t sel_idx = size_t(imodf(intptr_t(idx), intptr_t(songs.size())));

		if (song_idx != sel_idx)
		{
			player->stop();
			song_idx = sel_idx;

			song_channels = songs[song_idx].channels.size();
			synths.resize(song_channels);

			mscl_fp max_beats = 0.0;
			for (size_t i = 0; i < song_channels; ++i)
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
	const Tick t2 = Clock::now();
	tm_select = t2 - t1;
}

void MsclGUI::load_song()
{
	const Tick t1 = Clock::now();
	{
		if (loaded_idx != song_idx)
		{
			player->stop();
			loaded_idx = song_idx;

			init_engines();
			song_samples = size_t(song_seconds * sps);
			samples.resize(song_samples);
			channels.resize(song_samples * song_channels);

			for (size_t si = 0; si < song_samples; ++si)
			{
				mscl_fp data = 0.0;
				for (size_t ci = 0; ci < song_channels; ++ci)
				{
					synths[ci].sample = mscl_advance(&synths[ci].engine, sps, songs[song_idx].bpm, synths[ci].channel.size(), synths[ci].channel.data());
					data += synths[ci].sample;
					channels[song_samples * ci + si] = float(synths[ci].sample); 
				}
				samples[si] = float(data);
			}
		}
	}
	const Tick t2 = Clock::now();
	tm_load = t2 - t1;
}

// ================================================================================================================================

namespace mscl
{
	extern int gui(const std::span<const mscl::Song> song_list, const int width, const int height, const bool fullscreen)
	{
		MsclGUI demo{ song_list };
		if (!demo.Construct(width, height, 1, 1, fullscreen, true)) return EXIT_FAILURE;

		const olc::rcode res{ demo.Start() };
		return (res == olc::OK) ? EXIT_SUCCESS : EXIT_FAILURE;
	}
}

// ================================================================================================================================
