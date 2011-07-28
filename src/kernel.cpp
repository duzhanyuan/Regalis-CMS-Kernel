/* 
 *
 * Copyright (c) by Patryk Jaworski
 * Contact:
 *  -> E-mail: Patryk Jaworski <skorpion9312@gmail.com>
 *  -> XMPP/Jabber: Patryk Jaworski <skorpion9312@jabber.org>
 *
*/

#include <iostream>
#include <cstdlib>
#include <execinfo.h>
#include <typeinfo>
#include <dlfcn.h>
#include <libintl.h>
#include "kernel.hpp"
using namespace std;
using namespace rcms;

Kernel::Kernel() {
	set_terminate(Kernel::terminator);	
	setContentType("text/html; charset=utf-8");	
}

void Kernel::operate() {
	try {
		log = KLogger::get("kernel");	
		log->msg("Getting module init...");
		getModule("init");
	} catch(KernelException& e) {
		abort("KernelException", &e);
	} catch(ModuleException& e) {
		abort("ModuleException", &e);
	} catch(Exception& e) {
		abort("SCMS Exception", &e);
	}
}

void Kernel::abort(const string& name, Exception* e) {
	cout << "Content-type: text/html; charset=utf-8\r\n" << endl;
	cout.flush();
	cout << "<h1>Błąd " << name << "</h1>" << endl; 
	cout << "<p>Komunikat: " << e->what() << endl;
	printBacktrace(); 
	exit(0);
}

void Kernel::printHeaders() const {
	for(unsigned int i = 0; i < headers.size(); ++i) {
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
	cout << "<h1>Nieoczekiwany błąd</h1>" << endl;
	printBacktrace();
	exit(0);
}

void Kernel::printBacktrace() {
	void* stack[100];
	int stackSize = backtrace(stack, 100);
	char** symbols = backtrace_symbols(stack, stackSize);
	cout << "<p>Backtrace:</p>" << endl;
	cout << "<ul>" << endl;
	for (int i = 0; i < stackSize; ++i)
		cout << "<li>" << symbols[i] << "</li>" << endl;
	cout << "</ul>" << endl;
	free(symbols);
}

Kernel& Kernel::get() {
	static Kernel* k = new Kernel();
	return *k;
}

void Kernel::pingModule(const string& name) {
	KernelModule* mod = modules.get(name);
	mod->ping();
}

void Kernel::setContentType(const string& ct) {
	contentType = ct;
}

void Kernel::ping() const {
	cout << "Kernel::ping()" << endl;
}

void Kernel::flush() const {
	cout << "Content-type: " << contentType << "\r\n";
	printHeaders();
}

KernelModule* Kernel::getModule(const string& name) {
	if(!modules.exists(name))
		loadModule(name);
	return modules.get(name);
}

KernelModule* Kernel::operator[](const string& name) {
	return getModule(name);
}

void Kernel::loadModule(const string& name) {
	string path = "lib/modules/lib%s.so" % name;
	void* lib = dlopen(path.c_str(), RTLD_GLOBAL | RTLD_NOW);
	if(lib == NULL)
		throw KernelException(dlerror());
	void* factory_s = dlsym(lib, "factory");
	if(factory_s == NULL)
		throw KernelException("Unable to find factory in module " + name + "(" + dlerror() + ")");
	factory_t* factory = (factory_t*)factory_s;
	modules.add(name, factory());
	modules.get(name)->setLogger(KLogger::get(name));
	if(!modules.get(name)->init()) {
		throw ModuleException("Unable to initialize module %s. Check logs for details..." % name);
	}
	// TODO: Installation...
}
