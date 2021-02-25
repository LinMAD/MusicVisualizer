#pragma once

#include <SDL.h>
#include <memory>
#include <string>
#include "Audio/SDL/AudioData.h"

namespace MV {
	class AudioWrapper
	{
	public:
		explicit AudioWrapper(const std::string& pathToFile);

		void Execute();

		std::shared_ptr<AudioData> GetSourceAudioData();
		const std::string& GetFilePath();

		bool IsStopped();

		// SDL_AudioCallback
		static void ForwardCallback(void* userData, Uint8* stream, int streamLength);
	private:
		void ClearResources() const;
	private:
		bool m_IsPlaying;
		std::string m_PathToFile;

		SDL_AudioSpec m_WavSpec{};
		SDL_AudioSpec m_Obtained{};
		SDL_AudioDeviceID m_Device{};

		Uint8* m_WavStartBuffer{};
		Uint32 m_WavLength{};

		std::shared_ptr<AudioData> m_AudioData;
	};
}
