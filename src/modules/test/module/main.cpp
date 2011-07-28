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
