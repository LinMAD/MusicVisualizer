#pragma once

#include <cstdio>
#include <SDL.h>
#include <GL/glew.h>
#include <string>
#include <memory>

#include "Graphic/Renderer.h"
#include "Graphic/Gui/Screen.h"
#include "Audio/SDL/AudioData.h"

namespace MV {
	class RendererWrapper : public Renderer
	{
	public:
		RendererWrapper();
		~RendererWrapper();
	protected:
        void CallUpdateScreen(AudioData audioData) override;
		void CallClearScreen() override;
		void CallPullEvents() override;
		bool CallIsRunning() override;
	private:
        Screen* m_GuiScreen;
	private:
		SDL_Window* m_Window;
        SDL_GLContext m_GlContext;

	private:
		bool m_IsRunning;

		uint32_t m_StartTime;
		uint32_t m_EndTime;
		uint32_t m_Delta;
		short m_TimePerFrameInMilliSec;
        uint32_t m_Fps;

        const char* m_GlslVersion;
    };
}
