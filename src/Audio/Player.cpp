#include "Player.h"
#include "Logger.h"

MV::Player::Player()
{
	isPlaying = 0;
}

void MV::Player::Play(std::string pathToFile)
{
	if (isPlaying == 1)
	{
		if (m_Audio->IsStopped())
		{
			std::string execMsg{ "Cleaning buffer from audio for file: " + pathToFile };
			LOGGER_DEBUG(execMsg);
			
			m_Audio->~AudioWrapper();
			isPlaying = 0;
		}

		return;
	}

	// TODO Use abstract class of audio
	m_Audio = new AudioWrapper();
	m_Audio->Execute(pathToFile);
	isPlaying = 1;
}
