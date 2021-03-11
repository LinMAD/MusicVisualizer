#include "Player.h"
#include "Logger.h"

namespace MV {
	Player::Player()
	{
		m_PlayList = {};
		m_Playable = nullptr;
	}

	Player::~Player()
	{
		LOG("Cleaning audio objects from playlist...");
        for (auto item : m_PlayList) delete(item);

		m_PlayList.clear();
        m_Playable.reset();
	}

	void Player::Add(const string& pathToFile)
	{
		_mutex.lock();

		m_PlayList.push_back(new AudioWrapper(pathToFile));

		_mutex.unlock();
	}

	void Player::Play(const string& pathToFile)
	{
		AudioWrapper* needed = FindAudio(pathToFile);
		if (needed == nullptr)
		{
			LOG(pathToFile + " not found in playlist!");
			return;
		}

		if (needed->IsStopped())
        {
            needed->Execute();

            m_Playable.reset();
            m_Playable = make_shared<Player::Playable>();
            m_Playable->currentAudio = needed->GetSourceAudioData();
            m_Playable->isPause = needed->IsStopped();
        }
	}

    shared_ptr<Player::Playable> Player::GetPlayable()
	{
		return m_Playable;
	}

	AudioWrapper* Player::FindAudio(const string& pathToFile)
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
