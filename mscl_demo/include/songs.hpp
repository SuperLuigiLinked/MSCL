/**
 * @file mscl_demo/songs.hpp
 *
 * @brief List of Songs used in the Demo Program.
 */

#pragma once

#include <mscl_gui.hpp>
#include "songs/Demo1.hpp"
#include "songs/Demo2b.hpp"
#include "songs/HappySynth.hpp"
#include "songs/Menuet.hpp"
#include "songs/Ghosts.hpp"
#include "songs/DemoFM.hpp"

inline static constexpr mscl::Song song_list[] = {
	songs::Demo1::song,
	songs::Demo2::song,
	songs::HappySynth::song,
	songs::Menuet::song,
	songs::Ghosts::song,
	songs::DemoFM::song,
};
