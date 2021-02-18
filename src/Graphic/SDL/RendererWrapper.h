#pragma once

#include <SDL.h>
#include <memory>
#include "Graphic/Renderer.h"
#include "Graphic/SDL/Visualizer.h"
#include "Audio/AudioData.h"

namespace MV {
	class RendererWrapper : public Renderer
	{
	public:
		RendererWrapper();
		~RendererWrapper();
	protected:
		virtual void CallClearScreen() override;
		virtual void CallDrawBuffer(const AudioData* audiodata) override;
		virtual void CallPullEvents() override;
		virtual bool CallIsRunning() override;
	private:
		SDL_Window* m_Window;
		std::shared_ptr<SDL_Renderer> m_Renderer;
		Visualizer* m_Visualizer;
	private:
		bool m_IsRunning;

		uint32_t m_StartTime;
		uint32_t m_EndTime;
		uint32_t m_Delta;
		short m_TimePerFrameinMilliSec;
		short m_Fps;
	};
}
