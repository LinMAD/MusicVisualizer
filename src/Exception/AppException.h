#pragma once

#include <exception>
#include <string>
#include "Logger.h"

namespace MV {
	class AppException : public std::exception
	{
	public:
		explicit AppException(const char* _Message) : exception()
		{
			LOG("Application runtime exception: " + GetErrorMessage(_Message));
		};
	protected:
		const std::string GetErrorMessage(const char* _Message)
		{
			return std::string (_Message);
		}
	};
}
