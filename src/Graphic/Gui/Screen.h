#pragma once

#include <imgui.h>
#include <imgui_impl_sdl.h>
#include <imgui_impl_opengl3.h>
#include <SDL.h>
#include <GL/glew.h>
#include "Audio/SDL/AudioData.h"
#include "Graphic/Window.h"

namespace MV {
    class Screen {
    public:
        Screen(SDL_Window* window, SDL_GLContext context, const char* GlslVersion);
        ~Screen();

        static void Update(SDL_Event& event);
        void Draw(AudioData& audioData);
    protected:
        void HandleControls();
        void HandleAudioTrack();
        void HandleAudioWave(AudioData audioData);
    protected:
        const double M_PI = 3.14159265358979323846;
        const float MAX_LENGTH = 262.0f;
        const int AUDIO_WAVE_VISUAL_POWER_INDEX = 5;
        const float AUDIO_WAVE_CONSTANT_SIZE = (float) AUDIO_BUFFER_SAMPLE_FRAMES / (float) WINDOW_WIDTH;

        SDL_Window* m_Window;
        SDL_GLContext m_GlContext;

        bool m_IsPlayerWindowVisible;

        ImVec4 m_ClearColor;
        ImGuiIO* m_ImgGuiIo;

        // Audio
        double m_AudioMultiplier;
    };
}
