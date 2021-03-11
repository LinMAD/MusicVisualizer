#pragma once

#include <memory>
#include <utility>
#include "Audio/Player.h"

namespace MV {
	class Renderer
	{
	public:
        inline static void Update(shared_ptr<Player::Playable> playable)
        {
            s_RendererImpl->CallPullEvents();
            s_RendererImpl->CallClearScreen();
            s_RendererImpl->CallUpdateScreen(std::move(playable));
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
		virtual void CallUpdateScreen(shared_ptr<Player::Playable> playable) = 0;
		virtual void CallPullEvents() = 0;
		virtual bool CallIsRunning() = 0;
	private:
		static std::unique_ptr<Renderer> s_RendererImpl;
	};
}
