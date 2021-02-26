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
            m_Fps(60)
	{
		LOG("Initializing SDL components...");
		
		// Video
		if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER) < 0)
		{
			LOG("SDL could not initialize!");
			throw AppException(SDL_GetError());
		}

        LOG("Preparing GL 3.0 + GLSL 130...");
        const char* glsl_version = "#version 130";
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
        SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
        SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

        auto window_flags = (SDL_WindowFlags)(SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_MOUSE_CAPTURE);
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

        // Setup Dear ImGui context
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        m_ImgGuiIo = &ImGui::GetIO();

        // Setup Dear ImGui style
        ImGui::StyleColorsDark();
        ImGui_ImplSDL2_InitForOpenGL(m_Window, m_GlContext);
        ImGui_ImplOpenGL3_Init(glsl_version);

		m_IsRunning = true;
		LOG("Initialization done...");

        const char *vertexShaderSource = R"(
            #version 330 core
            layout (location = 0) in vec3 aPos;
            void main()
            {
                gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
            }
        )";
        const char *fragmentShaderSource = R"(
            #version 330 core
            out vec4 FragColor;
            void main()
            {
                FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
            }
        )";

        // build and compile our shader program
        // ------------------------------------
        // vertex shader
        unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
        glCompileShader(vertexShader);
        // check for shader compile errors
        int success;
        char infoLog[512];
        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
            LOG("COMPILATION_FAILED");
        }
        // fragment shader
        unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
        glCompileShader(fragmentShader);
        // check for shader compile errors
        glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
            LOG("COMPILATION_FAILED");
        }
        // link shaders
        unsigned int shaderProgram = glCreateProgram();
        glAttachShader(shaderProgram, vertexShader);
        glAttachShader(shaderProgram, fragmentShader);
        glLinkProgram(shaderProgram);
        // check for linking errors
        glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
            LOG("LINKING_FAILED");
        }
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);

        // set up vertex data (and buffer(s)) and configure vertex attributes
        // ------------------------------------------------------------------
        // add a new set of vertices to form a second triangle (a total of 6 vertices); the vertex attribute configuration remains the same (still one 3-float position vector per vertex)
        float vertices[] = {
                // first triangle
                -0.9f, -0.5f, 0.0f,  // left
                -0.0f, -0.5f, 0.0f,  // right
                -0.45f, 0.5f, 0.0f,  // top
        };

        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)nullptr);
        glEnableVertexAttribArray(0);

        // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
        // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
        glBindVertexArray(0);
        //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}

	RendererWrapper::~RendererWrapper()
	{
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
        glDeleteProgram(shaderProgram);

	    delete(m_Visualizer);

        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplSDL2_Shutdown();
        ImGui::DestroyContext();

        SDL_GL_DeleteContext(m_GlContext);
		SDL_DestroyWindow(m_Window);
		SDL_Quit();
	}

    void RendererWrapper::CallPullEvents()
    {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            ImGui_ImplSDL2_ProcessEvent(&event);

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

    void RendererWrapper::CallClearScreen()
    {
        glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
    }

    void RendererWrapper::CallUpdateScreen(AudioData audioData)
    {
	    // Update window
        std::string title{ string(WINDOW_TITLE) + " FPS: " + std::to_string(m_Fps) };
        SDL_SetWindowTitle(m_Window, title.c_str());

        // GUI frame


        // Update shader for audio
//        m_Visualizer->DrawWave(audioData, SDL_Point{ 0, WINDOW_HEIGHT / 2 }, WINDOW_WIDTH, SDL_Color{ 50, 200, 50, 255 });
    }

	void RendererWrapper::CallDrawBuffer()
	{
		if (!m_StartTime)
			m_StartTime = (uint32_t) SDL_GetTicks();
		else
			m_Delta = m_EndTime - m_StartTime;

		if ((short) m_Delta < m_TimePerFrameInMilliSec)
			SDL_Delay(m_TimePerFrameInMilliSec - m_Delta);

		if ((short) m_Delta > m_TimePerFrameInMilliSec)
			m_Fps = 1000 / m_Delta;

		ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL2_NewFrame(m_Window);
        ImGui::NewFrame();
        ImGui::ShowDemoWindow(&show_demo_window);

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        // draw our first triangle
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
        glDrawArrays(GL_TRIANGLES, 0, 6); // set the count to 6 since we're drawing 6 vertices now (2 triangles); not 3!

        SDL_GL_SwapWindow(m_Window);

		m_StartTime = m_EndTime;
		m_EndTime = (uint32_t) SDL_GetTicks();
	}

	bool RendererWrapper::CallIsRunning()
	{
		return m_IsRunning;
	}
}