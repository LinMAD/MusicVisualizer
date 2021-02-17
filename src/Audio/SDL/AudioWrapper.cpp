#include "AudioWrapper.h"
#include "Logger.h"
#include "Exception/AppException.h"

MV::AudioWrapper::AudioWrapper()
{
	m_IsPaused = 1;
}

MV::AudioWrapper::~AudioWrapper()
{
	SDL_CloseAudioDevice(m_Device);
	SDL_FreeWAV(m_WavBuffer);
}

void MV::AudioWrapper::Execute(std::string pathToFile)
{
	std::string execMsg{ "Loading given audio file: " + pathToFile };
	LOGGER_DEBUG(execMsg);

	if (SDL_LoadWAV(pathToFile.c_str(), &m_WavSpec, &m_WavBuffer, &m_Wavlength) == NULL)
	{
		LOGGER_DEBUG("Impossible to load audio file!");
		throw AppException(SDL_GetError());
	}

	m_Device = SDL_OpenAudioDevice(NULL, 0, &m_WavSpec, NULL, 0);
	if (m_Device == 0)
	{
		LOGGER_DEBUG("Error with audio device!");
		throw AppException(SDL_GetError());
	}

	if (SDL_QueueAudio(m_Device, m_WavBuffer, m_Wavlength) < 0)
	{
		LOGGER_DEBUG("Cannot add to queue audio...");
		throw AppException(SDL_GetError());
	}

	execMsg = { "Playing new audio from: " + pathToFile };
	LOGGER_DEBUG(execMsg);

	SDL_PauseAudioDevice(m_Device, 0);
}

bool MV::AudioWrapper::IsStopped()
{
	auto queuedAudio = SDL_GetQueuedAudioSize(m_Device);
	auto diviceState = SDL_GetAudioDeviceStatus(m_Device);
	bool isStoped = diviceState == SDL_AUDIO_STOPPED || queuedAudio <= 0;
	if (isStoped) m_IsPaused = 1;

	return isStoped;
}
