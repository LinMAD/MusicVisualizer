#include "AudioWrapper.h"
#include "Logger.h"
#include "Exception/AppException.h"

namespace MV {
	AudioWrapper::AudioWrapper(const std::string& pathToFile)
	{
		m_IsPlaying = false;
		m_PathToFile = pathToFile;
	}

	void AudioWrapper::Execute()
	{
		std::string execMsg{ "Loading given audio file: " + m_PathToFile };
		LOGGER_DEBUG(execMsg);

		if (SDL_LoadWAV(m_PathToFile.c_str(), &m_WavSpec, &m_WavStartBuffer, &m_WavLength) == NULL)
		{
			LOGGER_DEBUG("Impossible to load audio file!");
			throw AppException(SDL_GetError());
		}

		m_AudioData = std::make_shared<AudioData>();
		m_AudioData->name = m_PathToFile; // TODO Replace by base name or get info from file
		m_AudioData->position = m_WavStartBuffer;
		m_AudioData->length = m_WavLength;
		m_AudioData->format = AUDIO_S16;

		m_WavSpec.freq = AUDIO_SAMPLING_FREQUENCY_RATE;
		m_WavSpec.channels = AUDIO_CHANNEL_COUNT;
		m_WavSpec.samples = AUDIO_BUFFER_SAMPLE_FRAMES;
		m_WavSpec.callback = ForwardCallback;
		m_WavSpec.userdata = m_AudioData.get();
		m_WavSpec.format = m_AudioData->format;

		m_Device = SDL_OpenAudioDevice(
			NULL,
			0,
			&m_WavSpec,
			&m_Obtained,
			NULL
		);
		if (m_Device == 0)
		{
			LOGGER_DEBUG("Error with audio device!");
			throw AppException(SDL_GetError());
		}

		execMsg = { "Playing audio from: " + m_PathToFile };
		LOGGER_DEBUG(execMsg);

		m_IsPlaying = true;

		SDL_PauseAudioDevice(m_Device, SDL_FALSE);
	}

	AudioData* AudioWrapper::GetSourceAudioData()
	{
		return m_AudioData.get();
	}

	const std::string& AudioWrapper::GetFilePath()
	{
		return m_PathToFile;
	}

	bool AudioWrapper::IsStopped()
	{
		if (m_IsPlaying && m_AudioData->length == 0)
		{
			m_IsPlaying = false;
			ClearResources();
		}

		return !m_IsPlaying;
	}

	void AudioWrapper::ForwardCallback(void* userData, Uint8* stream, int steamLenght)
	{
		struct AudioData* audio = (struct AudioData*) userData;

		if (audio->length == 0)
		{
			SDL_FreeWAV(audio->stream);
			return;
		}

		// TODO Exec thread?
		audio->stream = stream;

		uint32_t length = (uint32_t) steamLenght;
		length = (length > audio->length ? audio->length : length);

		SDL_memcpy(audio->stream, audio->position, length);

		audio->position += length;
		audio->length -= length;
	}

	void AudioWrapper::ClearResources()
	{
		SDL_CloseAudioDevice(m_Device);
	}
}
