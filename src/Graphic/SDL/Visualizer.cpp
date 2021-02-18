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
	SDL_SetRenderDrawColor(m_Renderer.get(), color.r, color.g, color.b, color.a);

	points.push_back(SDL_Point{ start.x, start.y });
	points.push_back(SDL_Point{ start.x + lineWidth - 1, start.y });

	SDL_RenderDrawLines(m_Renderer.get(), &points[0], (int)points.size());
}
