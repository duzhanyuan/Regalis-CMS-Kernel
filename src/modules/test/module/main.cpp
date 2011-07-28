#include "main.hpp"
#include "../../../kernel.hpp"
#include <iostream>
using namespace std;
using namespace scms;

string ModuleTest::getResult() const {
	return "ModuleTest";
}

void ModuleTest::ping() {
	cout << "Hello world from test module!" << endl;
	Kernel::get().ping();
}

void ModuleTest::run() {
	cout << "Hello!" << endl;
}

extern "C" {
	KernelModule* factory() {
		return new ModuleTest();
	}
}
