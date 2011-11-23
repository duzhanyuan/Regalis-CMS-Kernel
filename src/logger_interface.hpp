#ifndef _LOGGER_INTERFACE_HPP
#define _LOGGER_INTERFACE_HPP
#include <string>
using std::string;

namespace rcms {
	class Logger {
		public:
			enum Type {
				OK,
				WARNING,
				ERROR
			};
			virtual void msg(const string& msg) = 0;
			virtual void msg(const string& msg, Type type) = 0;
			virtual Logger& operator<<(const string& msg) = 0;
			virtual void flush() = 0;
			virtual ~Logger();
	};
}

#endif
