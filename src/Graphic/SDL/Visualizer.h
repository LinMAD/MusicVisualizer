 #pragma once

#include <SDL.h>
#include <memory>
#include "Audio/SDL/AudioData.h"

namespace MV {
	class Visualizer
	{
	public:
		explicit Visualizer(SDL_Renderer* renderer);

		void DrawWave(AudioData audioData, SDL_Point start, int lineWidth, const SDL_Color& color);
	private:
	    const double M_PI = 3.14159265358979323846;
        SDL_Renderer* m_Renderer;

		// Visual sound data
        double m_Multiplier;
	};
}

