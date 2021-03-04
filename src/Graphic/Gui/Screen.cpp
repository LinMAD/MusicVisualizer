#include "Screen.h"
#include "Logger.h"

namespace MV {
    Screen::Screen(SDL_Window* window, SDL_GLContext context, const char* GlslVersion)
        : m_ClearColor(ImVec4(0.0f, 0.0f, 0.0f, 1.00f)),
        m_IsPlayerWindowVisible(true),
        m_ImgGuiIo(nullptr)
    {
        m_Window = window;
        m_GlContext = context;

        // Setup Dear ImGui context
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        m_ImgGuiIo = &ImGui::GetIO();

        // Setup Dear ImGui style
        ImGui::StyleColorsDark();
        ImGui_ImplSDL2_InitForOpenGL(m_Window, m_GlContext);
        ImGui_ImplOpenGL3_Init(GlslVersion);
    }

    Screen::~Screen()
    {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplSDL2_Shutdown();
        ImGui::DestroyContext();
    }

    void Screen::Draw(AudioData& audioData)
    {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL2_NewFrame(m_Window);
        ImGui::NewFrame();

        static ImVec2 screenSize = ImVec2(500, 500);
        static ImVec2 screenPos = ImVec2(0, 0);
        auto screenFlags = (
            ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse
            | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoDecoration
        );

        ImGui::Begin("Player screen", &m_IsPlayerWindowVisible, screenFlags); // TODO Add track name
        ImGui::SetWindowSize(screenSize);
        ImGui::SetWindowPos(screenPos);
        ImGui::GetStyle().WindowRounding = 0.0f;

        HandleAudioTrack();
        HandleAudioWave(audioData);
        HandleControls();

        ImGui::End();

        ImGui::Render();
        glViewport(0, 0, (int) m_ImgGuiIo->DisplaySize.x, (int) m_ImgGuiIo->DisplaySize.y);
        glClearColor(m_ClearColor.x * m_ClearColor.w, m_ClearColor.y * m_ClearColor.w, m_ClearColor.z * m_ClearColor.w, m_ClearColor.w);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

    void Screen::Update(SDL_Event &event)
    {
        ImGui_ImplSDL2_ProcessEvent(&event);
    }

    void Screen::HandleControls()
    {
        // TODO Add handlers to buttons
        ImGui::Button("Previous");
        ImGui::SameLine();
        ImGui::Button("Play");
        ImGui::SameLine();
        ImGui::Button("Stop");
        ImGui::SameLine();
        ImGui::Button("Next");
        ImGui::SameLine();
        ImGui::Button("Shuffle");
        ImGui::SameLine();
    }

    void Screen::HandleAudioWave(AudioData audioData)
    {
        // Sampling audio from stream
        for(int i=0; i < AUDIO_BUFFER_SAMPLE_FRAMES; i++)
        {
            m_AudioMultiplier = 0.5 * (1 - cos(2 * M_PI * i / AUDIO_BUFFER_SAMPLE_FRAMES));
            audioData.in[i][0] = MV::AudioData::Get16bitAudioSample(audioData.position, audioData.format) * m_AudioMultiplier;
            audioData.in[i][1] = 0.0;
            audioData.position += 2;
        }

        static float audioProcess[90] = {};
        static double refreshTime = 0.0;
        static int processOffset = 0;

        // Animate sound wave
        if (audioData.length != 0)
        {
            if (refreshTime == 0.0) refreshTime = ImGui::GetTime();

            while (refreshTime < ImGui::GetTime())
            {
                for(int i=0; i < AUDIO_BUFFER_SAMPLE_FRAMES; i++)
                {
                    audioProcess[processOffset] = static_cast<float>(audioData.in[i][0] * AUDIO_WAVE_VISUAL_POWER_INDEX);
                    processOffset = (int) ((float)i / AUDIO_WAVE_CONSTANT_SIZE) % IM_ARRAYSIZE(audioProcess);
                }

                refreshTime += 1.0f / 60.0f; // fixed 60 Hz rate
            }
        }

        ImGui::PlotLines(
            "",
            audioProcess,
            IM_ARRAYSIZE(audioProcess),
            processOffset,
            nullptr,
            -1.0f,
            1.0f,
            ImVec2(MAX_LENGTH, 80.0f)
        );
    }

    void Screen::HandleAudioTrack()
    {
        static float track = 0.0f, audioTrackDir = 1.0f;

        // Animate a simple progress bar
        track += audioTrackDir * 0.4f * ImGui::GetIO().DeltaTime;
        if (track >= +1.1f)
        {
            track = +1.1f;
            audioTrackDir *= -1.0f;
        }

        if (track <= -0.1f)
        {
            track = -0.1f;
            audioTrackDir *= -1.0f;
        }

        ImGui::Text("Track: Foo bar");
        ImGui::ProgressBar(track, ImVec2(MAX_LENGTH, 0.0f));
    }
}
