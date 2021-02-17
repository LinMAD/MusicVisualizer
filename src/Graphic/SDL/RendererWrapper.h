#pragma once

#include <SDL.h>
#include "Graphic/Renderer.h"

namespace MV {
	class RendererWrapper : public Renderer
	{
	public:
		RendererWrapper();
		~RendererWrapper();
	protected:
		virtual void CallClearScreen() override;
		virtual void CallDrawBuffer() override;
		virtual void CallPullEvents() override;
		virtual bool CallIsRunning() override;
	private:
		SDL_Window* m_Window;
		SDL_Renderer* m_Renderer;
	private:
		bool m_IsRunning;

		uint32_t m_StartTime;
		uint32_t m_EndTime;
		uint32_t m_Delta;
		short m_TimePerFrameinMilliSec;
		short m_Fps;
	};
}
