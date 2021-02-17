#pragma once

#include <memory>

namespace MV {
	class Renderer
	{
	public:
		inline static void Update()
		{
			s_RendererImpl->CallPullEvents();
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

		inline static Renderer* GetActuallRenderer()
		{
			return s_RendererImpl.get();
		}
	protected:
		virtual void CallClearScreen() = 0;
		virtual void CallDrawBuffer() = 0;
		virtual void CallPullEvents() = 0;
		virtual bool CallIsRunning() = 0;
	private:
		static std::unique_ptr<Renderer> s_RendererImpl;
	};
}
