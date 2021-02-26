#include "AudioWrapper.h"
#include "Logger.h"
#include "Exception/AppException.h"

namespace MV {
	AudioWrapper::AudioWrapper(const std::string& pathToFile) : m_IsPlaying(false)
	{
		m_PathToFile = pathToFile;
	}

	void AudioWrapper::Execute()
	{
		std::string execMsg{ "Loading given audio file: " + m_PathToFile };
		LOG(execMsg);

		if (SDL_LoadWAV(m_PathToFile.c_str(), &m_WavSpec, &m_WavStartBuffer, &m_WavLength) == NULL)
		{
			LOG("Impossible to load audio file!");
			throw AppException(SDL_GetError());
		}

		m_AudioData = std::make_shared<AudioData>();
		m_AudioData->name = m_PathToFile; // TODO Replace by base name or get info from file
		m_AudioData->length = m_WavLength;
		m_AudioData->format = AUDIO_S16;
		m_AudioData->position = m_WavStartBuffer;
		m_AudioData->stream = m_WavStartBuffer;
        m_AudioData->in = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * AUDIO_BUFFER_SAMPLE_FRAMES);
        m_AudioData->out = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * AUDIO_BUFFER_SAMPLE_FRAMES);
        m_AudioData->plan = fftw_plan_dft_1d(AUDIO_BUFFER_SAMPLE_FRAMES, m_AudioData->in, m_AudioData->out, FFTW_FORWARD, FFTW_MEASURE);

		m_WavSpec.freq = AUDIO_SAMPLING_FREQUENCY_RATE;
		m_WavSpec.channels = AUDIO_CHANNEL_COUNT;
		m_WavSpec.samples = AUDIO_BUFFER_SAMPLE_FRAMES;
		m_WavSpec.callback = ForwardCallback;
		m_WavSpec.userdata = m_AudioData.get();
		m_WavSpec.format = m_AudioData->format;

		m_Device = SDL_OpenAudioDevice(nullptr, 0, &m_WavSpec, &m_Obtained, 0);
		if (m_Device == 0)
		{
			LOG("Error with audio device!");
			throw AppException(SDL_GetError());
		}

		execMsg = { "Playing audio from: " + m_PathToFile };
		LOG(execMsg);

		SDL_LockAudioDevice(m_Device);
		m_IsPlaying = true;

		SDL_PauseAudioDevice(m_Device, SDL_FALSE);
		SDL_UnlockAudioDevice(m_Device);
	}

	std::shared_ptr<AudioData> AudioWrapper::GetSourceAudioData()
	{
		return m_AudioData;
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

	void AudioWrapper::ForwardCallback(void* userData, Uint8* stream, int streamLength)
	{
		auto* audio = (struct AudioData*) userData;
        SDL_memset(stream, 0, streamLength);

		if (audio->length <= 0)
		{
			free(audio->stream);
			free(audio->position);
			return;
		}

        audio->stream = stream;

		auto tempLength = (uint32_t) streamLength;
		tempLength = (tempLength > audio->length ? audio->length : tempLength);

		SDL_MixAudioFormat(stream, audio->position, audio->format, tempLength, AUDIO_MAX_SOUNDS);

		audio->position += tempLength;
		audio->length -= tempLength;
	}

	void AudioWrapper::ClearResources() const
	{
        //SDL_FreeWAV(m_WavStartBuffer);
        SDL_CloseAudioDevice(m_Device);
	}
}
