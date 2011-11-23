/* 
 *
 * Copyright (c) by Patryk Jaworski
 * Contact:
 *  -> E-mail: Patryk Jaworski <skorpion9312@gmail.com>
 *  -> XMPP/Jabber: Patryk Jaworski <skorpion9312@jabber.org>
 *
*/

#include "kernel.hpp"
#include <cstdlib>
extern "C" {
#include <iniparser.h>
}
using namespace std;
using namespace rcms;

Kernel::MySQL::MySQL(Logger* logger) throw(KernelException) {
	log = logger;
	FILE* config_file = fopen("etc/mysql/mysql.conf", "r");
	if(config_file == NULL)  {
		log->msg("Unable to open MySQL configuration file (etc/mysql/mysql.conf).", Logger::ERROR);
		throw KernelException("Unable to open MySQL configuration file (etc/mysql/mysql.conf).");
	}
	fclose(config_file);
	dictionary* config = iniparser_load((char*)"etc/mysql/mysql.conf");
	const char* host = iniparser_getstring(config, (char*)"mysql:host", (char*)"localhost");
	const char* database = iniparser_getstring(config, (char*)"mysql:database", (char*)"regaliscms");
	const char* user = iniparser_getstring(config, (char*)"mysql:user", (char*)"regaliscms");
	const char* password = iniparser_getstring(config, (char*)"mysql:password", (char*)"regaliscms");
	const unsigned int port = (unsigned int)iniparser_getint(config, (char*)"mysql:port", 3306);
	try {
		connection = new mysqlpp::Connection(database, host, user, password, port);
	} catch(mysqlpp::ConnectionFailed& e) {
		string error = e.what();
		log->msg("Unable to connect to database: %s" % error, Logger::ERROR);
		throw KernelException("Unable to connect do database, check logs for details...");
	}
}

mysqlpp::Query* Kernel::MySQL::getQuery() {
	return new mysqlpp::Query(connection, false);
}
