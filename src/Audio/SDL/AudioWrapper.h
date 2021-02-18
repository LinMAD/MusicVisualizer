#pragma once

#include <SDL.h>
#include <memory>
#include <string>
#include "Audio/AudioData.h"

namespace MV {
	class AudioWrapper
	{
	public:
		AudioWrapper(const std::string& pathToFile);

		void Execute();

		AudioData* GetSourceAudioData();
		const std::string& GetFilePath();

		bool IsStopped();

		// SDL_AudioCallback
		static void ForwardCallback(void* userData, Uint8* stream, int steamLenght);
	private:
		void ClearResources();
	private:
		bool m_IsPlaying;
		std::string m_PathToFile;

		SDL_AudioSpec m_WavSpec;
		SDL_AudioSpec m_Obtained;
		SDL_AudioDeviceID m_Device;

		uint8_t* m_WavStartBuffer;
		uint32_t m_WavLength;

		std::shared_ptr<AudioData> m_AudioData;
	};
}
