#include "main.hpp"
#include "../../test/module/main.hpp"
#include <iostream>
using namespace std;
using namespace rcms;

bool InitModule::init() {
	*log << "Initializing modules...";
	Kernel::get().getModule("test")->ping();
	*log << "OK! :)";
	ModuleTest* module = dynamic_cast<ModuleTest*>(Kernel::get().getModule("test"));
	*log << "Message from module test:" << module->test();
	return true;
}

extern "C" {
	KernelModule* factory() {
		return new InitModule();
	}
}
