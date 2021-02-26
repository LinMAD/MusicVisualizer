#pragma once

#include <memory>
#include <utility>
#include "Audio/SDL/AudioData.h"

namespace MV {
	class Renderer
	{
	public:
        inline static void Update(AudioData audioData)
        {
            s_RendererImpl->CallPullEvents();
            s_RendererImpl->CallUpdateScreen(std::move(audioData));
        }

		inline static void Draw()
		{
			s_RendererImpl->CallClearScreen();
			s_RendererImpl->CallDrawBuffer();
		}

		inline static bool IsRunning()
		{
			return s_RendererImpl->CallIsRunning();
		}

		inline static Renderer* GetActualRenderer()
		{
			return s_RendererImpl.get();
		}
	protected:
		virtual void CallClearScreen() = 0;
		virtual void CallUpdateScreen(AudioData audioData) = 0;
		virtual void CallDrawBuffer() = 0;
		virtual void CallPullEvents() = 0;
		virtual bool CallIsRunning() = 0;
	private:
		static std::unique_ptr<Renderer> s_RendererImpl;
	};
}
