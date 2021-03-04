#include "Graphic/SDL/RendererWrapper.h"
#include "Graphic/Window.h"
#include "Logger.h"
#include "Exception/AppException.h"

namespace MV {
	RendererWrapper::RendererWrapper() :
            m_StartTime(0),
            m_EndTime(0),
            m_Delta(0),
            m_TimePerFrameInMilliSec(15),
            m_Fps(60),
            m_GlslVersion("#version 130"),
            m_GuiScreen(nullptr)
	{
		LOG("Initializing SDL components...");
		
		// Video
		if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER) < 0)
		{
			LOG("SDL could not initialize!");
			throw AppException(SDL_GetError());
		}

        LOG("Preparing GL 3.0 + GLSL 130...");
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
        SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
        SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

        auto window_flags = (SDL_WindowFlags)(
            SDL_WINDOW_OPENGL | SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_MOUSE_CAPTURE
        );
        m_Window = SDL_CreateWindow(
			WINDOW_TITLE,
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			WINDOW_WIDTH,
			WINDOW_HEIGHT,
            window_flags
		);
		if (m_Window == nullptr) 
		{
			LOG("Window could not be created!");
			throw AppException(SDL_GetError());
		}

        m_GlContext = SDL_GL_CreateContext(m_Window);
        SDL_GL_MakeCurrent(m_Window, m_GlContext);
        SDL_GL_SetSwapInterval(1); // Enable vsync

        LOG("Loading OpenGL...");
        bool err = glewInit() != GLEW_OK;
        if (err)
        {
            LOG("Failed to initialize OpenGL loader!");
            throw AppException(reinterpret_cast<const char *>(glewGetErrorString(err)));
        }

        m_GuiScreen = new Screen(m_Window, m_GlContext, m_GlslVersion);

        m_IsRunning = true;
        LOG("Initialization done...");
    }

	RendererWrapper::~RendererWrapper()
	{
	    delete(m_GuiScreen);

        SDL_GL_DeleteContext(m_GlContext);
		SDL_DestroyWindow(m_Window);
		SDL_Quit();
	}

    void RendererWrapper::CallPullEvents()
    {
        SDL_Event event;

        while (SDL_PollEvent(&event)) {
            MV::Screen::Update(event);

            if (!m_IsRunning || event.type == SDL_QUIT)
            {
                m_IsRunning = false;
                break;
            }

            switch (event.type) {
                case SDL_WINDOWEVENT:
                    if (event.window.event == SDL_WINDOWEVENT_CLOSE && event.window.windowID == SDL_GetWindowID(m_Window))
                        m_IsRunning = false;
                    break;
                default:
                    break;
            }
        }
    }

    void RendererWrapper::CallClearScreen()
    {
        glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
        glClearColor(0, 0, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT);
    }

    void RendererWrapper::CallUpdateScreen(AudioData audioData)
    {
	    // Update window
        std::string title{ string(WINDOW_TITLE) + " FPS: " + std::to_string(m_Fps) };
        SDL_SetWindowTitle(m_Window, title.c_str());

        if (!m_StartTime)
            m_StartTime = (uint32_t) SDL_GetTicks();
        else
            m_Delta = m_EndTime - m_StartTime;

        if ((short) m_Delta < m_TimePerFrameInMilliSec)
            SDL_Delay(m_TimePerFrameInMilliSec - m_Delta);

        if ((short) m_Delta > m_TimePerFrameInMilliSec)
            m_Fps = 1000 / m_Delta;

        m_GuiScreen->Draw(audioData);

        SDL_GL_SwapWindow(m_Window);

        m_StartTime = m_EndTime;
        m_EndTime = (uint32_t) SDL_GetTicks();
    }

	bool RendererWrapper::CallIsRunning()
	{
		return m_IsRunning;
	}
}