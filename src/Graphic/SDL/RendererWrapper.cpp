#include <string> 

#include "Graphic/SDL/RendererWrapper.h"
#include "Graphic/Window.h"
#include "Logger.h"
#include "Exception/AppException.h"

namespace MV {
	RendererWrapper::RendererWrapper()
	{
		LOGGER_DEBUG("Creating SDL Window...");

		m_StartTime = 0;
		m_EndTime = 0;
		m_Delta = 0;
		m_TimePerFrameinMilliSec = 15;
		m_Fps = 60;

		if (SDL_Init(SDL_INIT_VIDEO) < 0) 
		{
			LOGGER_DEBUG("SDL could not initialize!");
			throw AppException(SDL_GetError());
		}

		m_Window = SDL_CreateWindow(
			WINDOW_TITLE,
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			WINDOW_WIDTH,
			WINDOW_HEIGHT,
			SDL_WINDOW_OPENGL
		);

		if (m_Window == nullptr) 
		{
			LOGGER_DEBUG("Window could not be created!");
			throw AppException(SDL_GetError());
		}

		m_Renderer = SDL_CreateRenderer(m_Window, -1, SDL_RENDERER_ACCELERATED);
		if (m_Renderer == nullptr)
		{
			LOGGER_DEBUG("Renderer could not be created!");
			throw AppException(SDL_GetError());
		}
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

	void RendererWrapper::CallDrawBuffer()
	{
		if (!m_StartTime)
			m_StartTime = (uint32_t) SDL_GetTicks();
		else
			m_Delta = m_EndTime - m_StartTime;

		if (m_Delta < m_TimePerFrameinMilliSec)
			SDL_Delay(m_TimePerFrameinMilliSec - m_Delta);

		if (m_Delta > m_TimePerFrameinMilliSec)
			m_Fps = 1000 / m_Delta;

		/*
		* Render on screen
		*/

		std::string title{ string(WINDOW_TITLE) + " FPS: " + std::to_string(m_Fps) };
		SDL_SetWindowTitle(m_Window, title.c_str());

		// Square
		SDL_Rect square{ 50, 50, 50, 50};

		SDL_SetRenderDrawColor(m_Renderer, 0, 0, 255, 255);
		SDL_RenderFillRect(m_Renderer, &square);
		SDL_RenderPresent(m_Renderer);
		// End of square

		m_StartTime = m_EndTime;
		m_EndTime = (uint32_t) SDL_GetTicks();
	}
}