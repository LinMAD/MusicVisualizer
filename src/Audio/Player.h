#pragma once

#include <string>
#include <memory>
#include <vector>
#include <mutex>
#include "Audio/SDL/AudioWrapper.h"

using namespace std;

namespace MV {
	class Player
	{
	public:
		Player();
		~Player();

		void Add(string pathToFile);
		void Play(string pathToFile);
		const AudioData* GetAudioData(string pathToFile);
	private:
		AudioWrapper* FindAudio(string pathToFile);
	private:
		bool m_IsPlaying;

		vector<AudioWrapper*> m_PlayList;
		timed_mutex _mutex;
	};
}
