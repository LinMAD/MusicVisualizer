#pragma once

#include <exception>
#include <string>

namespace MV {
	class AppException : public std::exception
	{
	public:
		explicit AppException(char const* const _Message) : exception(_Message)
		{
			LOGGER_DEBUG(strcat("Exception: ", _Message));
		};
	};
}
