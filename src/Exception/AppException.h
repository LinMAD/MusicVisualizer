#pragma once

#include <exception>
#include <string>

namespace MV {
	class AppException : public std::exception
	{
	public:
		explicit AppException(const char* _Message) : exception()
		{
			std::string err = _Message;
			LOG("Exception: " + err);
		};
	};
}
