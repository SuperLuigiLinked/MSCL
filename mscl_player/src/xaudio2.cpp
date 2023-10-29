/**
 * @file mscl_player/xaudio2.cpp
 */

#include <memory>

#include <Windows.h>
#include <xaudio2.h>
#include <wrl/client.h>
using Microsoft::WRL::ComPtr;

#include <mscl.h>
#include "mscl_player.hpp"
#include "utils.hpp"

// ================================================================================================================================

class PlayerXAudio2 final : public mscl::Player
{
private:

    ComPtr<IXAudio2> xaudio2;
    IXAudio2MasteringVoice* mvoice;
    IXAudio2SourceVoice* svoice;

public:

    PlayerXAudio2()
        : xaudio2{}, mvoice{}, svoice{}
    {
        const HRESULT res_coinit = CoInitializeEx(nullptr, COINIT_MULTITHREADED);
        ASSERT(SUCCEEDED(res_coinit));

        const HRESULT res_xa2 = XAudio2Create(&xaudio2, 0, XAUDIO2_USE_DEFAULT_PROCESSOR);
        ASSERT(SUCCEEDED(res_xa2));
        ASSERT(xaudio2 != nullptr);

        const HRESULT res_mv = xaudio2->CreateMasteringVoice(&mvoice, XAUDIO2_DEFAULT_CHANNELS, XAUDIO2_DEFAULT_SAMPLERATE, 0, nullptr, nullptr, AudioCategory_GameEffects);
        ASSERT(SUCCEEDED(res_mv));
        ASSERT(mvoice != nullptr);
    }

    ~PlayerXAudio2() final
    {
        if (svoice) svoice->DestroyVoice();
        if (mvoice) mvoice->DestroyVoice();
    }

    void submit(const size_t num_samples, const float* const samples, const mscl_fp sps) final
    {
        if (num_samples == 0) return;
        ASSERT(samples != nullptr);

        constexpr WORD wave_format = WAVE_FORMAT_IEEE_FLOAT;
        constexpr WORD sample_bits = sizeof(float) * CHAR_BIT;
        constexpr WORD channel_count = 1;
        constexpr WORD block_align = channel_count * sample_bits / CHAR_BIT;
        
        const DWORD samples_psec = static_cast<DWORD>(sps);
        const DWORD bytes_psec = sample_bits / CHAR_BIT * samples_psec;
        
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

        this->stop();
        const HRESULT res_sv = xaudio2->CreateSourceVoice(&svoice, &wavefmt, 0, XAUDIO2_MAX_FREQ_RATIO, nullptr, nullptr, nullptr);
        ASSERT(SUCCEEDED(res_sv));
        ASSERT(svoice != nullptr);

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

        const HRESULT res_submit = svoice->SubmitSourceBuffer(&buffer, nullptr);
        ASSERT(SUCCEEDED(res_submit));
    }

    void play() final
    {
        if (svoice)
        {
            const HRESULT res = svoice->Start(0, XAUDIO2_COMMIT_NOW);
            ASSERT(SUCCEEDED(res));
        }
    }

    void pause() final
    {
        if (svoice)
        {
            const HRESULT res = svoice->Stop(0, XAUDIO2_COMMIT_NOW);
            ASSERT(SUCCEEDED(res));
        }
    }

    void stop() final
    {
        if (svoice)
        {
            svoice->DestroyVoice();
            svoice = nullptr;
        }
    }

    bool playing() final
    {
        if (!svoice) return false;

        XAUDIO2_VOICE_STATE state = {};
        svoice->GetState(&state, XAUDIO2_VOICE_NOSAMPLESPLAYED);

        return state.BuffersQueued > 0;
    }

    size_t pos() final
    {
        if (!svoice) return 0;

        XAUDIO2_VOICE_STATE state = {};
        svoice->GetState(&state);

        return size_t(state.SamplesPlayed);
    }
};

extern mscl::Player* mscl::Player::xaudio2()
{
    return new PlayerXAudio2();
}

// ================================================================================================================================
