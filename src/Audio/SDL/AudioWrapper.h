#pragma once

#include <SDL.h>
#include <string>

namespace MV {
	class AudioWrapper
	{
	public:
		AudioWrapper();
		~AudioWrapper();

		void Execute(std::string pathToFile);
		// TODO Can be added Pause/Resume
		bool IsStopped();
	private:
		SDL_AudioSpec m_WavSpec;
		SDL_AudioSpec m_Obtained;
		SDL_AudioDeviceID m_Device;

		uint8_t* m_WavBuffer;
		uint32_t m_Wavlength;

		int m_IsPaused;
	};
}
