#include <string>
#include "Graphic/SDL/RendererWrapper.h"
#include "Graphic/Window.h"
#include "Logger.h"
#include "Exception/AppException.h"

namespace MV {
	RendererWrapper::RendererWrapper() : 
		m_StartTime(0), 
		m_EndTime(0), 
		m_Delta(0),
		m_TimePerFrameinMilliSec(15),
		m_Fps(60)
	{
		LOG("Initializing SDL components...");
		
		// Video
		if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
		{
			LOG("SDL could not initialize!");
			throw AppException(SDL_GetError());
		}

		m_Window = SDL_CreateWindow(
			WINDOW_TITLE,
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			WINDOW_WIDTH,
			WINDOW_HEIGHT,
			SDL_WINDOW_OPENGL | SDL_WINDOW_MOUSE_CAPTURE | SDL_WINDOW_RESIZABLE
		);

		if (m_Window == nullptr) 
		{
			LOG("Window could not be created!");
			throw AppException(SDL_GetError());
		}

		m_Renderer = SDL_CreateRenderer(m_Window, -1, SDL_RENDERER_ACCELERATED);
		if (m_Renderer == nullptr)
		{
			LOG("Renderer could not be created!");
			throw AppException(SDL_GetError());	
		}

		m_Visualizer = new Visualizer(m_Renderer);
		m_IsRunning = true;
		LOG("Initialization of SDL components, done...");
	}

	RendererWrapper::~RendererWrapper()
	{
		SDL_DestroyRenderer(m_Renderer);
		SDL_DestroyWindow(m_Window);
		SDL_Quit();
	}

	void RendererWrapper::CallClearScreen()
	{
		SDL_SetRenderDrawColor(m_Renderer, 0, 0, 0, 255);
		SDL_RenderClear(m_Renderer);
	}

	void RendererWrapper::CallDrawBuffer(const AudioData* audioData)
	{
		if (!m_StartTime)
			m_StartTime = (uint32_t) SDL_GetTicks();
		else
			m_Delta = m_EndTime - m_StartTime;

		if ((short) m_Delta < m_TimePerFrameinMilliSec)
			SDL_Delay(m_TimePerFrameinMilliSec - m_Delta);

		if ((short) m_Delta > m_TimePerFrameinMilliSec)
			m_Fps = 1000 / m_Delta;

		/*
		* Render on screen
		*/

		std::string title{ string(WINDOW_TITLE) + " FPS: " + std::to_string(m_Fps) };
		SDL_SetWindowTitle(m_Window, title.c_str());

		// Render sound wave
		m_Visualizer->DrawWave(audioData, SDL_Point{ 0, WINDOW_HEIGHT / 2 }, WINDOW_WIDTH, SDL_Color{ 50, 200, 50, 255 });

		SDL_RenderPresent(m_Renderer);

		m_StartTime = m_EndTime;
		m_EndTime = (uint32_t) SDL_GetTicks();
	}

	void RendererWrapper::CallPullEvents()
	{
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			if (!m_IsRunning || event.type == SDL_QUIT)
			{
				m_IsRunning = false;
				break;
			}

			switch (event.type) {
			case SDL_WINDOWEVENT:
				if (event.window.event == SDL_WINDOWEVENT_CLOSE) m_IsRunning = false;
				break;
			default:
				break;
			}
		}
	}
	bool RendererWrapper::CallIsRunning()
	{
		return m_IsRunning;
	}
}