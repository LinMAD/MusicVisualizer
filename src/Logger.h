#pragma once

#include <memory>
#include <string>

using namespace std;

namespace MV {
	class Log {
	public:
		void ToggleIsEnabled();
		void Write(string message);
		static shared_ptr<Log> GetInstance();
	protected:
		Log();
	private:
		static shared_ptr<Log> s_Instance;
		bool m_IsEnabled;
	};
}

#define LOGGER_DEBUG(...)::MV::Log::GetInstance()->Write(__VA_ARGS__);
