#pragma once

#include <stdint.h>
#include <string>

namespace MV {
    constexpr int AUDIO_BUFFER_SAMPLE_FRAMES = 2048;
    constexpr int AUDIO_SAMPLING_FREQUENCY_RATE = 48000;
    constexpr int AUDIO_CHANNEL_COUNT = 2;

    struct AudioData
    {
        std::string name;
        uint8_t* stream;
        uint8_t* position;
        uint32_t length;
        int format;
    };
}