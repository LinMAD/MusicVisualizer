#pragma once

#include <memory>
#include "Audio/AudioData.h"

namespace MV {
	class Renderer
	{
	public:
		inline static void HandleEvents()
		{
			s_RendererImpl->CallPullEvents();
		}

		inline static void Draw(std::shared_ptr<AudioData> audiodata)
		{
			s_RendererImpl->CallClearScreen();
			s_RendererImpl->CallDrawBuffer(audiodata);
		}

		inline static bool IsRunning()
		{
			return s_RendererImpl->CallIsRunning();
		}

		inline static Renderer* GetActuallRenderer()
		{
			return s_RendererImpl.get();
		}
	protected:
		virtual void CallClearScreen() = 0;
		virtual void CallDrawBuffer(std::shared_ptr<AudioData> audiodata) = 0;
		virtual void CallPullEvents() = 0;
		virtual bool CallIsRunning() = 0;
	private:
		static std::unique_ptr<Renderer> s_RendererImpl;
	};
}
