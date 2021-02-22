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

		void Add(const string& pathToFile);
		void Play(const string& pathToFile);
		std::shared_ptr<AudioData> GetAudioData(const string& pathToFile);
	private:
		AudioWrapper* FindAudio(const string& pathToFile);
	private:
		bool m_IsPlaying;

		vector<AudioWrapper*> m_PlayList;
		timed_mutex _mutex;
	};
}
