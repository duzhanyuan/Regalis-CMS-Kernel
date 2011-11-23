/* 
 *
 * Copyright (c) by Patryk Jaworski
 * Contact:
 *  -> E-mail: Patryk Jaworski <skorpion9312@gmail.com>
 *  -> XMPP/Jabber: Patryk Jaworski <skorpion9312@jabber.org>
 *
*/

#include "installer.hpp"
#include "../kernel.hpp"
#include <fstream>
#include <iostream>
#include <mysql++.h>
using namespace rcms;
using namespace std;

Installer::Installer(Logger* logger, Installable* i, const string& n) : log(logger), installable(i), name(n) {}

bool Installer::install() {
	log->msg("[Installer] Installing %s" % name);
	string sql = "etc/modules/install/%s.sql" % name;
	ifstream sql_file(sql.c_str());	
	if(!sql_file.is_open()) {
		log->msg("[Installer] File %s not found, runing soft-install..." % sql);
		try {
			preInstall();
			postInstall();
			return true;
		} catch(string& e) {
			log->msg("Unable to install %s. %s" % name % e);
			return false;
		}
	} else {
		log->msg("[Iinstaller] Running MySQL install...");
		string sql;
		string line;
		while(sql_file.good()) {
			getline(sql_file, line);
			if(line != "\n")
				sql += line + "\n";
		}
		mysqlpp::Query* query = Kernel::get().getQuery();
		log->msg("[Installer] Executing query: \n\n%s\n# END OF QUERY" % sql);
		if(query->exec(sql)) {
			log->msg("[Installer] Query execution: OK");
			return true;
		} else {
			log->msg("[Installer] Query execution: FAILED");
		}
		return false;
	}
}

void Installer::preInstall() throw(string) {
	if(!installable->preInstall())
		throw "preInstall failed!";
}

void Installer::postInstall() throw(string) {
	if(!installable->postInstall())
		throw "postInstall failed!";
}
