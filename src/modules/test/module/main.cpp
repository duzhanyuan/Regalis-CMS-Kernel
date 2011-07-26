#include "main.hpp"
#include "../../../kernel.hpp"
#include <iostream>
using namespace std;
using namespace scms;

void ModuleTest::setArg(const string& name, const string& arg) {
	cout << "ModuleTest::setting new arg: " << name << " with value: " << arg << endl;
}

string ModuleTest::getResult() const {
	return "ModuleTest";
}

void ModuleTest::ping() {
	cout << "Hello world from test module!" << endl;
	Kernel::get().ping();
}

KernelModule* factory() {
	return new ModuleTest();
}
