#pragma once

#include <SDL.h>
#include <memory>
#include "Graphic/Renderer.h"
#include "Graphic/SDL/Visualizer.h"
#include "Audio/SDL/AudioData.h"

namespace MV {
	class RendererWrapper : public Renderer
	{
	public:
		RendererWrapper();
		~RendererWrapper();
	protected:
		void CallClearScreen() override;
		void CallDrawBuffer(AudioData audioData) override;
		void CallPullEvents() override;
		bool CallIsRunning() override;
	private:
		SDL_Window* m_Window;
		SDL_Renderer* m_Renderer;
		Visualizer* m_Visualizer;
	private:
		bool m_IsRunning;

		uint32_t m_StartTime;
		uint32_t m_EndTime;
		uint32_t m_Delta;
		short m_TimePerFrameInMilliSec;
		short m_Fps;
	};
}
