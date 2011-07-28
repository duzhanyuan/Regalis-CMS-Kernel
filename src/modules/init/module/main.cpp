#include "main.hpp"
#include <iostream>
using namespace std;
using namespace rcms;

bool InitModule::init() throw(ModuleException) {
	*log << "Initializing modules...";
	Kernel::get().getModule("test")->ping();
	*log << "OK! :)";
}

extern "C" {
	KernelModule* factory() {
		return new InitModule();
	}
}
