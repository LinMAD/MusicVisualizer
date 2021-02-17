#pragma once

#include <string>
#include "Audio/SDL/AudioWrapper.h"

namespace MV {
	class Player
	{
	public:
		Player();

		void Play(std::string pathToFile);
	private:
		int isPlaying;

		// TODO Can be added to the list to have playlist
		AudioWrapper* m_Audio;
	};
}
