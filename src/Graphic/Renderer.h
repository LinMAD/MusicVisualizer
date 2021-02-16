#pragma once

#include <memory>

namespace MV {
	class Renderer
	{
	public:
		inline static void Clear()
		{
			s_RendererImpl->CallClearScreen();
		}

		inline static void Draw()
		{
			s_RendererImpl->CallDrawBuffer();
		}

		inline static Renderer* GetActuallRenderer()
		{
			return s_RendererImpl.get();
		}
	protected:
		virtual void CallClearScreen() = 0;
		virtual void CallDrawBuffer() = 0;
	private:
		static std::unique_ptr<Renderer> s_RendererImpl;
	};
}
