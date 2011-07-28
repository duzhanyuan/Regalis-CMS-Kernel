/* 
 *
 * Copyright (c) by Patryk Jaworski
 * Contact:
 *  -> E-mail: Patryk Jaworski <skorpion9312@gmail.com>
 *  -> XMPP/Jabber: Patryk Jaworski <skorpion9312@jabber.org>
 *
*/

#include "kernel.hpp"
#include "time.hpp"
#include "sformatter.hpp"
#include "exceptions.hpp"
using namespace rcms;

Kernel::KLogger::KLogger(const string& name) {
	string file = "var/log/%s.log" % name;
	out.open(file.c_str(), ios_base::app);
	if(!out.is_open())
		throw KernelException("Unable to open log file for writing (%s)" % file);
}

Kernel::KLogger::KLogger() {
	KLogger("kernel");
}

Logger* Kernel::KLogger::get(const string& name) {
	Logger* logger = new KLogger(name);
	return logger;
}

void Kernel::KLogger::msg(const string& msg, Logger::Type type) {
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

void Kernel::KLogger::msg(const string& message) {
	msg(message, OK);
}

void Kernel::KLogger::flush() {
	out.flush();
}

Logger& Kernel::KLogger::operator<<(const string& message) {
	msg(message);
	return *this;
}

Kernel::KLogger::~KLogger() {
	flush();
}
