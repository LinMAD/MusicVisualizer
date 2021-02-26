#pragma once


#include "imgui.h"
#include "imgui_impl_sdl.h"
#include "imgui_impl_opengl3.h"
#include <cstdio>
#include <SDL.h>
#include <GL/glew.h>

#include <string>
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
        void CallUpdateScreen(AudioData audioData) override;
        void CallDrawBuffer() override;
		void CallClearScreen() override;
		void CallPullEvents() override;
		bool CallIsRunning() override;
	private:
		SDL_Window* m_Window;
		Visualizer* m_Visualizer;
	private:
		bool m_IsRunning;

		uint32_t m_StartTime;
		uint32_t m_EndTime;
		uint32_t m_Delta;
		short m_TimePerFrameInMilliSec;
		short m_Fps;

        // Our state
        bool show_demo_window = true;
        ImVec4 m_ClearColor = ImVec4(0.0f, 0.0f, 0.0f, 1.00f);
        ImGuiIO* m_ImgGuiIo;
        SDL_GLContext m_GlContext;


        unsigned int shaderProgram;
        unsigned int VBO, VAO;
	};
}
