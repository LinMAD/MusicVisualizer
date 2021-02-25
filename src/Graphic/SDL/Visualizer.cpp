#include <vector>
#include "Visualizer.h"
#include "Graphic/Window.h"
#include "Logger.h"

MV::Visualizer::Visualizer(SDL_Renderer* renderer) : m_Multiplier(0)
{
	m_Renderer = renderer;
}

void MV::Visualizer::DrawWave(AudioData audioData, SDL_Point start, int lineWidth, const SDL_Color& color)
{
    const auto VISUAL_POWER_INDEX = 0.5;
    const auto CONSTANT_SIZE = (float) AUDIO_BUFFER_SAMPLE_FRAMES / (float) lineWidth;
    auto* timePoints = new SDL_Point[AUDIO_BUFFER_SAMPLE_FRAMES];

    // Sampling audio from stream
    for(int i=0; i < AUDIO_BUFFER_SAMPLE_FRAMES; i++)
    {
        m_Multiplier = VISUAL_POWER_INDEX * (1 - cos(2 * M_PI * i / AUDIO_BUFFER_SAMPLE_FRAMES));

        audioData.in[i][0] = MV::AudioData::Get16bitAudioSample(audioData.position, audioData.format) * m_Multiplier;
        audioData.in[i][1] = 0.0;

        audioData.position += 2;
    }

    // Create visual points
    if (audioData.length != 0) {
        for(int i=0; i < AUDIO_BUFFER_SAMPLE_FRAMES; i++)
        {
            timePoints[i].x = start.x + static_cast<int> ((float) i / CONSTANT_SIZE);
            timePoints[i].y = static_cast<int>(start.y - audioData.in[i][0] * 70);
        }
    }

    SDL_SetRenderDrawColor(m_Renderer, color.r, color.g, color.b, color.a);
    SDL_RenderDrawLines(m_Renderer, timePoints, AUDIO_BUFFER_SAMPLE_FRAMES);
}
