#include <vector>
#include "Visualizer.h"
#include "Graphic/Window.h"
#include "Logger.h"

MV::Visualizer::Visualizer(std::shared_ptr<SDL_Renderer> renderer)
{
	m_Renderer = renderer;
}

void MV::Visualizer::DrawWave(const AudioData* audioData, const SDL_Point& start, int lineWidth, int lineHeight, const SDL_Color& color)
{
	std::vector<SDL_Point> points;

    if (audioData->length != 0) {
        // use smallest possible step so soundwave fills window
        int step = (int)ceil((double) lineWidth / (double) audioData->length);
        auto amplitude = audioData->position;
        for (int i = 0; i < lineWidth; i += step) {
            points.push_back(SDL_Point{ start.x + i, (int)(start.y + *amplitude) });
            ++amplitude;
            //std::string audioPath = { "Wave Axix => X: " + std::to_string(start.x + i) + " Y: " + std::to_string(start.y) + std::to_string(*amplitude) };
            //LOGGER_DEBUG(audioPath);
        }
    }
    else { // silence
        points.push_back(SDL_Point{ start.x, start.y });
        points.push_back(SDL_Point{ start.x + lineWidth, start.y });

    }

    SDL_SetRenderDrawColor(m_Renderer.get(), color.r, color.g, color.b, color.a);
	SDL_RenderDrawLines(m_Renderer.get(), &points[0], (int)points.size());
}
