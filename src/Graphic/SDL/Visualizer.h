 #pragma once

#include <SDL.h>
#include <memory>
#include "Audio/AudioData.h"

namespace MV {
	class Visualizer
	{
	public:
		Visualizer(std::shared_ptr<SDL_Renderer> renderer);

		void DrawWave(const AudioData* audiodata, const SDL_Point& start, int lineWidth, int lineHeight, const SDL_Color& color);
	private:
		std::shared_ptr<SDL_Renderer> m_Renderer;
	};
}

