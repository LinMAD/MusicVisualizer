#pragma once

#include <stdint.h>
#include <string>

namespace MV {
    constexpr int AUDIO_BUFFER_SAMPLE_FRAMES = 4096;
    constexpr int AUDIO_SAMPLING_FREQUENCY_RATE = 48000;
    constexpr int AUDIO_CHANNEL_COUNT = 2;
    constexpr int AUDIO_MAX_SOUNDS = 25;

    struct AudioData
    {
        std::string name;
        uint8_t* stream;   // Original buffer
        uint8_t* position; // Modified buffer
        uint32_t length;
        int format;
    };
}