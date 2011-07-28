#include "main.hpp"
#include <iostream>
using namespace std;
using namespace scms;

void InitModule::ping() {
	cout << "Ping from Init module..." << endl;
}

void InitModule::run() {
	cout << "Initializing modules..." << endl;
	Kernel::get().getModule("test")->ping();
	cout << "OK! :)" << endl;
}

extern "C" {
	KernelModule* factory() {
		return new InitModule();
	}
}
