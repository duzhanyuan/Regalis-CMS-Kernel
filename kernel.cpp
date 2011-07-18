#include "kernel.hpp"
#include "modules/all.hpp"
#include <iostream>
#include <exception>
#include <cstdlib>
#include <execinfo.h>
#include <typeinfo>
using namespace std;
using namespace SCMS;

Kernel::Kernel() {
	void (*old_terminate)() = set_terminate(Kernel::terminator);	
	addHeader("Content-type", "text/html; charset=utf-8");
	modules = new ModulesRegistry();
	#include "modules/register.hpp"
}

void Kernel::printHeaders() {
	for(int i = 0; i < headers.size(); ++i) {
		cout << headers[i] << "\r\n";
	}
	cout << endl;
	cout.flush();
}

void Kernel::addHeader(const string& name, const string& value) {
	string header = name + ": " + value;
	headers.push_back(header);
}

void Kernel::terminator() {
	// TODO: Print class names...
	cout << "Content-Type: text/html; charset=utf-8\r\n" << endl;
	cout.flush();
	cout << "<h1>Unhandled exception</h1>" << endl;
	void* stack[100];
	int stackSize = backtrace(stack, 100);
	char** symbols = backtrace_symbols(stack, stackSize);
	cout << "<p>Backtrace:</p>" << endl;
	cout << "<ul>" << endl;
	for (int i = 0; i < stackSize; ++i)
		cout << "<li>" << symbols[i] << "</li>" << endl;
	cout << "</ul>" << endl;
	free(symbols);
	exit(0);
}

Kernel& Kernel::get() {
	static Kernel k;
	return k;
}

void Kernel::pingModule(const string& name) {
	KernelModule* mod = modules->get(name);
	mod->ping();
}

ModulesRegistry* Kernel::getModulesRegistry() {
	return modules;
}

void Kernel::ping() {
	cout << "Kernel::ping()" << endl;
}
