/**
 * @file demo/player_xaudio2.cpp
 */

#include <mscl.h>
#include "player.hpp"
#include "utils.h"

#include <Windows.h>
#include <xaudio2.h>
#include <wrl/client.h>

using Microsoft::WRL::ComPtr;

class PlayerXAudio2 final : public Player
{
private:

    ComPtr<IXAudio2> xaudio2;
    IXAudio2MasteringVoice* mvoice;

public:

    PlayerXAudio2()
        : xaudio2{}, mvoice{}
    {
        const HRESULT res_coinit = CoInitializeEx(nullptr, COINIT_MULTITHREADED);
        ASSERT(SUCCEEDED(res_coinit));

        const HRESULT res_xa2 = XAudio2Create(&xaudio2, 0, XAUDIO2_USE_DEFAULT_PROCESSOR);
        ASSERT(SUCCEEDED(res_xa2));
        ASSERT(xaudio2 != NULL);

        const HRESULT res_mv = xaudio2->CreateMasteringVoice(&mvoice, XAUDIO2_DEFAULT_CHANNELS, XAUDIO2_DEFAULT_SAMPLERATE, 0, nullptr, nullptr, AudioCategory_GameEffects);
        ASSERT(SUCCEEDED(res_mv));
        ASSERT(mvoice != NULL);
    }

    virtual void play(const size_t num_samples, const float* const samples) final
    {
        ASSERT(samples != nullptr);

        constexpr WORD wave_format = WAVE_FORMAT_IEEE_FLOAT;
        constexpr WORD sample_bits = sizeof(float) * CHAR_BIT;
        constexpr WORD channel_count = 1;
        constexpr DWORD samples_psec = 44'100;
        constexpr DWORD bytes_psec = sample_bits / CHAR_BIT * samples_psec;
        constexpr WORD block_align = channel_count * sample_bits / CHAR_BIT;
        
        const DWORD num_bytes = static_cast<DWORD>(num_samples * sizeof(float));
        const BYTE* const bytes = reinterpret_cast<const BYTE*>(samples);

        const WAVEFORMATEX wavefmt = {
            .wFormatTag = wave_format,
            .nChannels = channel_count,
            .nSamplesPerSec = samples_psec,
            .nAvgBytesPerSec = bytes_psec,
            .nBlockAlign = block_align,
            .wBitsPerSample = sample_bits,
            .cbSize = 0,
        };

        const XAUDIO2_BUFFER buffer = {
            .Flags = XAUDIO2_END_OF_STREAM,
            .AudioBytes = num_bytes,
            .pAudioData = bytes,
            .PlayBegin = 0,
            .PlayLength = 0,
            .LoopBegin = 0,
            .LoopLength = 0,
            .LoopCount = 0,
            .pContext = nullptr,
        };

        IXAudio2SourceVoice* svoice;
        const HRESULT res_sv = xaudio2->CreateSourceVoice(&svoice, &wavefmt, 0, XAUDIO2_MAX_FREQ_RATIO, nullptr, nullptr, nullptr);
        ASSERT(SUCCEEDED(res_sv));

        const HRESULT res_submit = svoice->SubmitSourceBuffer(&buffer, nullptr);
        ASSERT(SUCCEEDED(res_submit));

        const HRESULT res_start = svoice->Start(0, XAUDIO2_COMMIT_NOW);
        ASSERT(SUCCEEDED(res_start));
    }
};

extern Player* player_xaudio2()
{
    return new PlayerXAudio2();
}
