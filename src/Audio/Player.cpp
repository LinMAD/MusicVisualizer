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
		m_PlayList.push_back(new AudioWrapper(pathToFile));
	}

	void Player::Play(string pathToFile)
	{
		AudioWrapper* needed = FindAudio(pathToFile);
		if (needed == nullptr)
		{
			LOGGER_DEBUG(pathToFile + " not found in playlist!");
			return;
		}

		// Controll loop of audio play
		if (needed->IsStopped()) needed->Execute();
	}

	const AudioData* Player::GetAudioData(string pathToFile)
	{
		auto needed = FindAudio(pathToFile);
		if (needed != nullptr) 
			return new AudioData(); // stab

		return nullptr;
	}

	AudioWrapper* Player::FindAudio(string pathToFile)
	{
		for (auto audio : m_PlayList)
			if (audio->GetFilePath() == pathToFile)
				return audio;

		return nullptr;
	}
}
