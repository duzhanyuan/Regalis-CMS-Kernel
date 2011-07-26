#include "exceptions.hpp"
#include <cstring>
#include <cstdlib>
using namespace std;
using namespace scms;

/* Exception */

Exception::Exception(const char* msg, int n) throw() {
	num = n;
	message = new char[strlen(msg)];
	strcpy(message, msg);
}

Exception::Exception(const string& msg, int n) throw() {
	num = n;
	message = new char[msg.length()];
	strcpy(message, msg.c_str());
}

Exception::Exception(const char* msg) throw() {
	Exception(msg, 0);
}

Exception::Exception(const string& msg) throw() {
	Exception(msg, 0);
}

const int Exception::number() const throw() {
	return num;
}

const char* Exception::what() const throw() {
	return message;
}

Exception::~Exception() {
	free(message);
}

/* KernelException */

KernelException::KernelException(const char* msg) throw() : Exception(msg, 0) {}
KernelException::KernelException(const string& msg) throw() : Exception(msg, 0) {}

/* ModuleException */

ModuleException::ModuleException(const char* msg) throw() : Exception(msg, 0) {}
ModuleException::ModuleException(const string& msg) throw() : Exception(msg, 0) {}
