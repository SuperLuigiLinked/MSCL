/**
 * @file mscl_demo/main.cpp
 *
 * @brief Demo Program for MSCL library.
 */

#include <mscl_gui.hpp>
#include "songs.hpp"

#ifdef _WIN32
#   include <Windows.h>
int WINAPI wWinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPWSTR, _In_ int)
#else
int main(void)
#endif
{
	return mscl::gui(song_list, 1280, 720);
}
