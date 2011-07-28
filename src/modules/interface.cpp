#include "interface.hpp"
#include <iostream>
using std::string;
using std::cout;
using std::endl;
using scms::KernelTemplateModule;
using scms::KernelModule;

const string& KernelModule::getVersion() const {
	return version;
}

const string& KernelModule::getFullName() const {
	return full_name;
}

const string& KernelModule::getAuthor() const {
	return author;
}

const string& KernelModule::getDescription() const {
	return description;
}

bool KernelModule::preInstall() {
	return true;
}

bool KernelModule::postInstall() {
	return true;
}

bool KernelModule::preRemove() {
	return true;
}

bool KernelModule::postRemove() {
	return true;
}

void KernelModule::ping() {
	cout << "Default KernelTemplateModule::ping()" << endl;
}

KernelModule::~KernelModule() {}

string KernelTemplateModule::getResult() const {
	return "Default KernelTemplateModule";
}

void KernelTemplateModule::setArg(const string& name, const string& value) {
	args[name].push_back(value);
}

KernelTemplateModule::~KernelTemplateModule() {}
