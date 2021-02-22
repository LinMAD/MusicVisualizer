#include <chrono>
#include <ctime>
#include <iostream>
#include <future>
#include "Logger.h"

using std::chrono::system_clock;

namespace MV {
	shared_ptr<Log> Log::s_Instance = nullptr;

	Log::Log()
	{
		m_IsEnabled = true;
	}

	void Log::ToggleIsEnabled()
	{
		m_IsEnabled = !m_IsEnabled;
	}

	void Log::Write(const string& message)
	{
		if (!m_IsEnabled) return;

		std::async(
			launch::async,
			[](const string& m)
			{
				string msg;

				std::time_t time = system_clock::to_time_t(system_clock::now());
				struct tm* timeStruct = std::localtime(&time);

				char timeStr[10];
				strftime(timeStr, 10, "%H:%M:%S", timeStruct);
				msg += " |" + string(timeStr) + "|";
				msg += " " + m;

				std::cout << msg << std::endl;
			},
			message
		);
	}

	shared_ptr<Log> Log::GetInstance()
	{
		if (s_Instance == nullptr)
			s_Instance = shared_ptr<Log>(new MV::Log());

		return s_Instance;
	}
}