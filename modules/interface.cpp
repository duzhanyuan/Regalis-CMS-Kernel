#include "interface.hpp"
#include <iostream>
using std::string;
using SCMS::KernelModule;
using std::cout;
using std::endl;

string KernelModule::getResult() const {
	return "Hello world from KernelModule!";
}

void KernelModule::setArg(const string& name, const string& value) {
	args[name].push_back(value);
}

void KernelModule::ping() {
	cout << "Ping from KernelModule!" << endl;
}
