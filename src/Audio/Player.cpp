#include "Player.h"
#include "Logger.h"

namespace MV {
	Player::Player()
	{
		m_PlayList = {};
	}

	Player::~Player()
	{
		LOGGER_DEBUG("Cleaning audio objects from playlist...");
		m_PlayList.clear();
	}

	void Player::Add(string pathToFile)
	{
		_mutex.lock();

		m_PlayList.push_back(new AudioWrapper(pathToFile));

		_mutex.unlock();
	}

	void Player::Play(string pathToFile)
	{
		AudioWrapper* needed = FindAudio(pathToFile);
		if (needed == nullptr)
		{
			LOGGER_DEBUG(pathToFile + " not found in playlist!");
			return;
		}

		// TODO Can be executed next audio file if current is done
		// Controll loop of audio play
		if (needed->IsStopped()) needed->Execute();
	}

	const AudioData* Player::GetAudioData(string pathToFile)
	{
		auto needed = FindAudio(pathToFile);
		if (needed != nullptr)
			return needed->GetSourceAudioData();

		return nullptr;
	}

	AudioWrapper* Player::FindAudio(string pathToFile)
	{
		AudioWrapper* needed = nullptr;
		
		_mutex.lock();

		for (auto audio : m_PlayList)
			if (audio->GetFilePath() == pathToFile)
			{
				needed = audio;
				break;
			}

		_mutex.unlock();

		return needed;
	}
}
