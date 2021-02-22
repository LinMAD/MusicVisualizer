 #pragma once

#include <SDL.h>
#include <memory>
#include "Audio/AudioData.h"

namespace MV {
	class Visualizer
	{
	public:
		Visualizer(SDL_Renderer* renderer);

		void DrawWave(const AudioData* audioData, const SDL_Point& start, int lineWidth, const SDL_Color& color);
	private:
		SDL_Renderer* m_Renderer;
	};
}

