#include "kernel.hpp"
#include "time.hpp"
#include "sformatter.hpp"
#include "exceptions.hpp"
using namespace scms;

Kernel::Logger::Logger(const string& name) {
	string file = "var/log/%s.log" % name;
	out.open(file.c_str(), ios_base::app);
	if(!out.is_open())
		throw KernelException("Unable to open log file for writing (%s)" % file);
}

Kernel::Logger::Logger() {
	Logger("kernel");
}

Kernel::Logger* Kernel::Logger::get(const string& name) {
	Logger* logger = new Logger(name);
	return logger;
}

void Kernel::Logger::msg(const string& msg, Type type) {
	string h;
	switch(type) {
		case OK:
			h = "I";
			break;
		case WARNING:
			h = "W";
			break;
		case ERROR:
			h = "E";
			break;
		default:
			h = "?";
			break;
	}
	out << "[" << h << "] " << "[" << Time::format() << "]: " << msg << endl;
}

void Kernel::Logger::msg(const string& message) {
	msg(message, OK);
}

void Kernel::Logger::flush() {
	out.flush();
}

Kernel::Logger& Kernel::Logger::operator<<(const string& message) {
	msg(message);
	return *this;
}

Kernel::Logger::~Logger() {
	flush();
}
