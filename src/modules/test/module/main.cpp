/* 
 *
 * Copyright (c) by Patryk Jaworski
 * Contact:
 *  -> E-mail: Patryk Jaworski <skorpion9312@gmail.com>
 *  -> XMPP/Jabber: Patryk Jaworski <skorpion9312@jabber.org>
 *
*/

#include "main.hpp"
#include "../../../kernel.hpp"
#include <iostream>
using namespace std;
using namespace rcms;

void ModuleTest::ping() {
	cout << "Hello world from test module!" << endl;
	Kernel::get().ping();
}

bool ModuleTest::init() {
	return true;
}

const char* ModuleTest::test() const {
	return "I'm OK!";
}

bool ModuleTest::preInstall() {
	return true;
}

bool ModuleTest::postInstall() {
	return true;
}

bool ModuleTest::preRemove() {
	return true;
}

bool ModuleTest::postRemove() {
	return true;
}

extern "C" {
	KernelModule* factory() {
		return new ModuleTest();
	}
}
