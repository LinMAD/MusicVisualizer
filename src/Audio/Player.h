#pragma once

#include <string>
#include <memory>
#include <vector>
#include <mutex>
#include "Audio/SDL/Calculation/AudioWrapper.h"

using namespace std;

namespace MV {
	class Player
	{
	public:
        struct Playable {
            shared_ptr<AudioData> currentAudio;
            bool isPause;
        };

		Player();
		~Player();

		void Add(const string& pathToFile);
		void Play(const string& pathToFile);
		// TODO Pause
		// TODO Resume
        shared_ptr<Playable> GetPlayable();
	private:
		AudioWrapper* FindAudio(const string& pathToFile);
	private:
        shared_ptr<Playable> m_Playable;

		vector<AudioWrapper*> m_PlayList;
		timed_mutex _mutex;
	};
}
