#pragma once

#include <SDL.h>
#include <fftw3.h>
#include <cstdint>
#include <string>

namespace MV {
    constexpr int AUDIO_BUFFER_SAMPLE_FRAMES = 4096;
    constexpr int AUDIO_SAMPLING_FREQUENCY_RATE = 48000;
    constexpr int AUDIO_CHANNEL_COUNT = 2;
    constexpr int AUDIO_MAX_SOUNDS = 25;

    struct AudioData
    {
        std::string name;
        SDL_AudioFormat format;

        // Audio buffer buffer
        uint8_t* audioStream;   // Original buffer
        uint8_t* currentAudioPosition;
        uint32_t remainingAudioLength;
        uint32_t initialAudioLength;

        // Audio analysis
        fftw_plan plan;
        fftw_complex *in;
        fftw_complex *out;

        static double Get16bitAudioSample(const uint8_t* byteBuffer, SDL_AudioFormat format)
        {
            uint16_t val = 0x0;

            // TODO fix bug for some files -> byteBuffer buffer can be => ""
            if(SDL_AUDIO_ISLITTLEENDIAN(format))
                val=(uint16_t) byteBuffer[0] | ((uint16_t) byteBuffer[1] << 8);
            else
                val=((uint16_t) byteBuffer[0] << 8) | (uint16_t) byteBuffer[1];

            if(SDL_AUDIO_ISSIGNED(format))
                return ((int16_t) val) / 32768.0;

            return val / 65535.0;
        }
    };
}