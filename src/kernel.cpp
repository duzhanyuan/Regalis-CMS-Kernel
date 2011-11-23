/* 
 *
 * Copyright (c) by Patryk Jaworski
 * Contact:
 *  -> E-mail: Patryk Jaworski <skorpion9312@gmail.com>
 *  -> XMPP/Jabber: Patryk Jaworski <skorpion9312@jabber.org>
 *
*/

#include <iostream>
#include <stack>
#include <vector>
#include <queue>
#include <cstdlib>
#include <execinfo.h>
#include <typeinfo>
#include <dlfcn.h>
#include <libintl.h>
#include <unistd.h>
#include "kernel.hpp"
#include "config.hpp"
using namespace std;
using namespace rcms;

Kernel::Kernel() {
	log = KLogger::get("kernel");	
	set_terminate(Kernel::terminator);	
	setContentType("text/html; charset=utf-8");	
	setenv("LANG", "pl_PL.UTF-8", 1);
	setenv("LANGUAGE", DEFAULT_LANGUAGE, 1);
	setlocale(LC_ALL, "");
}

void Kernel::operate() {
	try {
		mysql = new MySQL(KLogger::get("mysql"));	
		checkInstallation();
		getModule("init");
	} catch(KernelException& e) {
		abort("KernelException", &e);
	} catch(ModuleException& e) {
		abort("ModuleException", &e);
	} catch(Exception& e) {
		abort("RCMS Exception", &e);
	}
}

void Kernel::abort(const string& name, Exception* e) {
	cout << "Content-type: text/html; charset=utf-8\r\n" << endl;
	cout.flush();
	cout << "<h1>" << "Error: " << name << "</h1>" << endl; 
	cout << "<p>" << "Message: " << e->what() << endl;
	printBacktrace(); 
	copyright();
	exit(0);
}

mysqlpp::Query* Kernel::getQuery() {
	return mysql->getQuery();
}

void Kernel::checkInstallation() throw(KernelException) {
	mysqlpp::Query* query = mysql->getQuery();	
	if(!query->use("show tables"))
		throw KernelException("Unable to list database tables...");
	mysqlpp::StoreQueryResult result = query->store();
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
	cout << "Content-Type: text/html; charset=utf-8\r\n" << endl;
	cout.flush();
	cout << "<h1>" << "Unexpected error" << "</h1>" << endl;
	printBacktrace();
	copyright();
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

void Kernel::copyright() {
	cout << "<p>Copyright &copy; by <a href=\"mailto:skorpion9312@gmail.com\" title=\"" << "Regalis CMS author" << "\">Patryk Jaworski</a></p>" << endl;
}

void Kernel::getModuleDependencies(const string& name, vector<string>& deps) {
	string f = "etc/modules/%s.dep" % name;
	ifstream file(f.c_str());
	if(!file.is_open())
		return;
	while(file.good()) {
		string dependency;
		file >> dependency;
		if(dependency.length() == 0)
			continue;
		deps.push_back(dependency);
	}
}

KernelModule* Kernel::getModule(const string& name) {
	if(!modules.exists(name))
		loadModule(name);
	return modules.get(name);
}

KernelModule* Kernel::operator[](const string& name) {
	return getModule(name);
}

void* Kernel::loadSymbol(const string& path, const string& name) {
	void* lib = dlopen(path.c_str(), RTLD_GLOBAL | RTLD_NOW);
	if(lib == NULL)
		throw KernelException("Unable to load library: %s (%s)" % path % dlerror());
	void* symbol = dlsym(lib, "factory");
	if(symbol == NULL)
		throw KernelException("Unable to find symbol %s in library %s (%s)" %name % path % dlerror());
	return symbol;
}

void Kernel::loadModule(const string& name) {
	vector<string> dependencies;
	getModuleDependencies(name, dependencies);
	for(unsigned int i = 0; i < dependencies.size(); ++i) {
		try {
			if(!modules.exists(dependencies[i]))
				loadModule(dependencies[i]);
		} catch(KernelException& e) {
			string msg = e.what();
			throw KernelException("Unable to resolv dependencies (%s need %s, but unable to load %s. %s" % name % dependencies[i] % dependencies[i] % msg);
		}
	}
	void* factory_s = loadSymbol("lib/modules/lib%s.so" % name, "factory");
	factory_t* factory = (factory_t*)factory_s;
	modules.add(name, factory());
	modules.get(name)->setLogger(KLogger::get(name));
	Installable* inst = dynamic_cast<Installable*>(modules.get(name));
	if(inst != NULL && name == "test") {
		Installer installer(log, inst, name);
		if(installer.install()) {
			*log << "Module %s installed." % name;
		}
	}
	if(!modules.get(name)->init()) {
		throw ModuleException("Unable to initialize module %s. Check logs for details" % name);
	}
}
